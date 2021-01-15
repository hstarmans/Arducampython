#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "arducam_mipicamera.h"

#include "ndarray_converter.h"

#include "camera.h"

namespace py = pybind11;

PYBIND11_MODULE(camera, m) {
    NDArrayConverter::init_numpy();
    m.doc() = "Python camera wrapper for Arducam";
    py::class_<Camera>(m, "Cam")
        .def(py::init<>())
        .def("init", &Camera::init)
        .def("close", &Camera::close)
        .def("set_auto_white_balance", &Camera::set_auto_white_balance, py::arg("enable"))
        .def("get_exposure", &Camera::get_exposure)
        .def("set_exposure", &Camera::set_exposure, py::arg("exposuretime"))
        .def("set_resolution", &Camera::set_resolution, "Set resolution of camera", py::arg("width"), py::arg("height"))
        .def("live_view", &Camera::live_view, "Capture image with given exposure time and return buffer", py::arg("scale")=1.0)
        .def("capture", &Camera::capture, "Capture image with given exposure time and return buffer")
        .def("set_mode", &Camera::set_mode, "Set the camera mode", py::arg("mode"));
}
