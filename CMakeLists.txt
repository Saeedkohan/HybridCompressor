cmake_minimum_required(VERSION 3.15)
project(HybridCompressor VERSION 1.0.0 LANGUAGES CXX)

# ---- C++ Standard ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: enable IPO/LTO in Release builds (safe default)
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_ERROR)
if(IPO_SUPPORTED)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()

# ---- Dependencies ----
add_subdirectory(pybind11)

# ---- Core library (shared by executables + python module) ----
add_library(hc_core STATIC
        src/Lexer.cpp
        src/Parser.cpp
        src/HybridCompressor.cpp
)

target_include_directories(hc_core PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# If you ever need platform-specific definitions:
# target_compile_definitions(hc_core PUBLIC ...)

# ---- Python bindings (_core.pyd / .so) ----
set(PYTHON_BINDINGS_SOURCE python/hybridcompressor/_native.cpp)

pybind11_add_module(_core MODULE
        ${PYTHON_BINDINGS_SOURCE}
)

target_link_libraries(_core PRIVATE hc_core)

# Copy built module into python package folder after build
add_custom_command(
        TARGET _core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/python/hybridcompressor"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:_core>
        "${CMAKE_CURRENT_SOURCE_DIR}/python/hybridcompressor/$<TARGET_FILE_NAME:_core>"
        COMMENT "✅ Copying compiled module to python package directory..."
)

# ---- Smoke test executable ----
add_executable(HybridCompressor_Test
        src/main.cpp
)

target_link_libraries(HybridCompressor_Test PRIVATE hc_core)

# ---- Lexer regression tests executable ----
add_executable(Lexer_Tests
        tests/lexer_tests.cpp
        tests/ast_tests.cpp
)

target_link_libraries(Lexer_Tests PRIVATE hc_core)

add_executable(AST_Tests
        tests/ast_tests.cpp
)

target_link_libraries(AST_Tests PRIVATE hc_core)