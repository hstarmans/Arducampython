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
        .def("live_view", &Camera::live_view, "Capture image with given exposure time and return buffer", py::arg("exptime"))
        .def("capture", &Camera::pythoncapture,
		 py::return_value_policy::copy, 
			"Capture image with given exposure time and return buffer", py::arg("exptime"))
        .def("set_mode", &Camera::set_mode, "Set the camera mode", py::arg("mode"));
}
