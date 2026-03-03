#cmake_minimum_required(VERSION 3.15)
#project(HybridCompressor)
#
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
#
#add_subdirectory(pybind11)
#
#file(GLOB LIB_SOURCES
#
#)
#
#pybind11_add_module(hybridcompressor
#        main.cpp
#        ${LIB_SOURCES}
#)
#
#target_include_directories(hybridcompressor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
#
#add_custom_command(
#        TARGET hybridcompressor POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:hybridcompressor>
#        "${CMAKE_CURRENT_SOURCE_DIR}/python/hybridcompressor.pyd"
#        COMMENT "✅ Copying compiled module to python directory..."
#)




cmake_minimum_required(VERSION 3.15)
project(HybridCompressor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)

file(GLOB CORE_SOURCES
        src/Lexer.cpp
        src/Parser.cpp
        src/HybridCompressor.cpp
)

set(PYTHON_BINDINGS_SOURCE python/hybridcompressor/_native.cpp)

pybind11_add_module(_core MODULE ${PYTHON_BINDINGS_SOURCE} ${CORE_SOURCES})

target_include_directories(_core PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_custom_command(
        TARGET _core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:_core>
        "${CMAKE_CURRENT_SOURCE_DIR}/python/hybridcompressor/$<TARGET_FILE_NAME:_core>"
        COMMENT "✅ Copying compiled module to python package directory..."
)

add_executable(HybridCompressor_Test src/main.cpp
        include/hybridcompressor/HybridCompressor.h
        src/HybridCompressor.cpp
        src/Lexer.cpp)
target_include_directories(HybridCompressor_Test PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
