cmake_minimum_required(VERSION 3.23)
project("OmnityEngine")

set(CMAKE_CXX_STANDARD 20)

include("CMake/functions.cmake")
add_subdirectory("Source" "${CMAKE_BINARY_DIR}/Binary")