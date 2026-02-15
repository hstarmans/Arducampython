cmake_minimum_required(VERSION 3.12)
project(camera)

#**************************************************************************************************
# CRITICAL FIX: Force CMake to use the Python provided by setup.py/uv
#**************************************************************************************************
if(DEFINED PYTHON_EXECUTABLE AND NOT DEFINED Python3_EXECUTABLE)
    set(Python3_EXECUTABLE ${PYTHON_EXECUTABLE})
endif()

#**************************************************************************************************
# General Settings
#**************************************************************************************************
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

#**************************************************************************************************
# Find Packages
#**************************************************************************************************

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    includes: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    libs:     ${OpenCV_LIBS}")

# Find Python 3 - It will now respect the 'Python3_EXECUTABLE' we set above
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

message(STATUS "Python 3 status:")
message(STATUS "    Executable: ${Python3_EXECUTABLE}")
message(STATUS "    Includes:   ${Python3_INCLUDE_DIRS}")
message(STATUS "    Libraries:  ${Python3_LIBRARIES}")
message(STATUS "    Version:    ${Python3_VERSION}")

# Detect NumPy from the FOUND Python (not system python)
execute_process(
  COMMAND "${Python3_EXECUTABLE}" -c "import numpy; print(numpy.get_include())"
  OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "NumPy Headers: ${NUMPY_INCLUDE_DIR}")

# Detect Pybind11 from the FOUND Python
execute_process(
  COMMAND "${Python3_EXECUTABLE}" -m pybind11 --cmakedir
  OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CMAKE_DIR}")
find_package(pybind11 CONFIG REQUIRED)
message(STATUS "Pybind11 Version: ${pybind11_VERSION}")

#**************************************************************************************************
# Build Configuration
#**************************************************************************************************

include_directories(${NUMPY_INCLUDE_DIR})
include_directories(${Python3_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

set(LIB_SOURCES ${PROJECT_SOURCE_DIR}/src/camera.cpp)

pybind11_add_module(camera ${PROJECT_SOURCE_DIR}/src/main.cpp ${LIB_SOURCES})

target_link_libraries(camera PRIVATE arducam_mipicamera ${OpenCV_LIBS})

set_target_properties(camera PROPERTIES CXX_VISIBILITY_PRESET "hidden")