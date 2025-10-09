#include <iostream>
#include <pybind11/pybind11.h>


int add(int a, int b) {
    return a + b;
}

namespace py = pybind11;

PYBIND11_MODULE(hybridcompressor, m) {
    m.doc() = "Test module for C++ <-> Python";
    m.def("add", &add, "A function that adds two numbers");
}
