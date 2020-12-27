project(camera)

#**************************************************************************************************
# General cMake settings
#**************************************************************************************************
cmake_minimum_required(VERSION 3.5)
# pybind requires c14++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#**************************************************************************************************
# Find Package **************************************************************************************************
find_package(OpenCV REQUIRED)
MESSAGE( " *** OpenCV_INCLUDE_DIRS : " ${OpenCV_INCLUDE_DIRS} )
MESSAGE( " *** OpenCV_LIB_DIRS : " ${OpenCV_LIB_DIRS} )
MESSAGE( " *** OpenCV_LIBS : " ${OpenCV_LIBS} )

find_package(PythonLibs 3 REQUIRED)
MESSAGE( " *** PYTHON_INCLUDE_DIRS : " ${PYTHON_INCLUDE_DIRS} )
MESSAGE( " *** PYTHON_LIBRARIES : " ${PYTHON_LIBRARIES} )

#**************************************************************************************************
# Include **************************************************************************************************
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS}/opencv4)
#Bring the headers, deprecated
include_directories(src)

#**************************************************************************************************
# Set variable **************************************************************************************************
set(LIB_SOURCES 
            ${PROJECT_SOURCE_DIR}/src/camera.cpp
            ${PROJECT_SOURCE_DIR}/src/ndarray_converter.cpp
)

# this code can be used to build c++ examples
# compilation output is placed in  binary folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# build the python module
add_subdirectory(${PROJECT_SOURCE_DIR}/src/pybind11/)

pybind11_add_module(camera ${PROJECT_SOURCE_DIR}/src/main.cpp ${LIB_SOURCES})

target_link_libraries(camera PRIVATE arducam_mipicamera ${OpenCV_LIBS})