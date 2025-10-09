cmake_minimum_required(VERSION 3.15)
project(HybridCompressor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(pybind11)

file(GLOB LIB_SOURCES
        "src/huffman.cpp"
        "src/hybrid_compressor.cpp"
        "src/memory_pool.cpp"
        "src/minifier.cpp"
        "src/parser.cpp"
        "src/profiler.cpp"
        "src/serializer.cpp"
        "src/stream_api.cpp"
)

pybind11_add_module(hybridcompressor
        main.cpp
        ${LIB_SOURCES}
)

target_include_directories(hybridcompressor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_custom_command(
        TARGET hybridcompressor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:hybridcompressor>
        "${CMAKE_CURRENT_SOURCE_DIR}/python/hybridcompressor.pyd"
        COMMENT "✅ Copying compiled module to python directory..."
)