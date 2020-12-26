#include <pybind11/pybind11.h>
#include "arducam_mipicamera.h"
#include "camera.h"

namespace py = pybind11;

PYBIND11_MODULE(camera, m) {
    m.doc() = "Python camera wrapper for Arducam";
    py::class_<Camera>(m, "Camera")
        .def("init", &Camera::init)
        .def("close", &Camera::close)
        .def("capture", &Camera::capture, "Capture image with given exposure time and return buffer", py::arg("exptime"))
        .def("set_mode", &Camera::set_mode, "Set the camera mode", py::arg("mode"));
}