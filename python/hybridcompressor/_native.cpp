#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // برای تبدیل std::string به str پایتون

#include "hybridcompressor/HybridCompressor.h"

namespace py = pybind11;
using namespace hc;

PYBIND11_MODULE(_core, m) {
    m.doc() = "C++ core module for HybridCompressor (via pybind11)";

    py::class_<HybridCompressor>(m, "HybridCompressor").def(py::init<>()).def(
        "compress", &HybridCompressor::compress, "Compresses the input HTML string and returns the minified string.");

    py::enum_<hc::TokenType>(m, "TokenType")
            .value("START_TAG", hc::TokenType::START_TAG)
            .value("END_TAG", hc::TokenType::END_TAG)
            .value("TEXT", hc::TokenType::TEXT)
            .value("COMMENT", hc::TokenType::COMMENT)
            // .value("ATTRIBUTE", hc::TokenType::ATTRIBUTE)
            .value("ATTRIBUTE_NAME", hc::TokenType::ATTRIBUTE_NAME)
            .value("ATTRIBUTE_VALUE", hc::TokenType::ATTRIBUTE_VALUE)
            .value("SELF_CLOSING_TAG", hc::TokenType::SELF_CLOSING_TAG)
            .value("END_OF_FILE", hc::TokenType::END_OF_FILE)
            .value("UNKNOWN", hc::TokenType::UNKNOWN)
            .export_values();


    py::class_<hc::Token>(m, "Token")
            .def(py::init<>())
            .def_readwrite("type", &hc::Token::type)
            .def_readwrite("value", &hc::Token::value)
            .def("__repr__",[](const hc::Token &t) {
                     return "<Token type: " + std::to_string(static_cast<int>(t.type)) + " value: '" + t.value + "'>";
                 });


    py::class_<hc::Lexer>(m, "Lexer").def(py::init<std::string>()).def("get_next_token", &hc::Lexer::getNextToken);
}
