cmake_minimum_required(VERSION 3.3)
# pybind requires c14++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Arducam)

#Bring the headers, deprecated
include_directories(src)

# this code can be used to build c++ examples
# compilation output is placed in  binary folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# build the python module
add_subdirectory(${PROJECT_SOURCE_DIR}/src/pybind11/)

pybind11_add_module(camera ${PROJECT_SOURCE_DIR}/src/main.cpp ${LIB_SOURCES})