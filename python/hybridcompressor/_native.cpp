#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // برای تبدیل std::string به str پایتون

#include "hybridcompressor/HybridCompressor.h"

namespace py = pybind11;
using namespace hc;

PYBIND11_MODULE(_core, m) {
    m.doc() = "C++ core module for HybridCompressor (via pybind11)";

    py::class_<HybridCompressor>(m, "HybridCompressor")
            .def(py::init<>())
            .def("compress", &HybridCompressor::compress,
                 "Compresses the input HTML string and returns the minified string.");
}
