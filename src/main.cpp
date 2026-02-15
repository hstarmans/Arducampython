#include <pybind11/pybind11.h>
#include <pybind11/numpy.h> // Native NumPy support
#include <pybind11/stl.h>

#include "arducam_mipicamera.h"
#include "camera.h"

// Note: We removed ndarray_converter.h

namespace py = pybind11;

// Helper function to convert cv::Mat to numpy array
py::array_t<uint8_t> mat_to_array(const cv::Mat& mat) {
    if (mat.empty()) {
        return py::array_t<uint8_t>();
    }

    // Define the shape (Rows, Cols, Channels)
    std::vector<ssize_t> shape = { mat.rows, mat.cols, mat.channels() };
    
    // Define the strides (Bytes per row, Bytes per pixel, Bytes per channel)
    std::vector<ssize_t> strides = { 
        (ssize_t)mat.step[0], 
        (ssize_t)mat.step[1], 
        (ssize_t)mat.elemSize1() 
    };

    // Create the array. 
    // We force a copy here to be safe because cv::Mat memory management 
    // is tricky to transfer ownership of to Python.
    return py::array_t<uint8_t>(shape, strides, mat.data);
}

PYBIND11_MODULE(camera, m) {
    m.doc() = "Python camera wrapper for Arducam UC-621 (NumPy 2.0 Compatible)";

    py::class_<Camera>(m, "Cam")
        .def(py::init<>())
        .def("init", &Camera::init, "Initialize the camera connection")
        .def("close", &Camera::close, "Close the camera connection")
        .def("set_auto_white_balance", &Camera::set_auto_white_balance, py::arg("enable"))
        .def("get_exposure", &Camera::get_exposure)
        .def("set_exposure", &Camera::set_exposure, py::arg("exposuretime"))
        .def("set_resolution", &Camera::set_resolution, py::arg("width"), py::arg("height"))
        .def("live_view", &Camera::live_view, py::arg("scale") = 1.0)
        
        // --- CHANGED: Use a lambda to handle the conversion ---
        .def("capture", [](Camera& self) {
            cv::Mat frame = self.capture();
            return mat_to_array(frame);
        }, "Capture a single frame and return it as a NumPy array (BGR)")
        // ------------------------------------------------------

        .def("set_mode", &Camera::set_mode, py::arg("mode"));
}