cmake_minimum_required(VERSION 3.12)

# set project name and version
project(DsAlgorithms VERSION 1.0) # set PROJECT_SOURCE_DIR to full path of current directory

# configure a header file to pass the version number from CMake to the source code
configure_file("include/version/DsAlgorithmsConfig.h.in" "DsAlgorithmsConfig.h")

# add the executables I want to generate
add_executable(suffix_array_test "tests/suffix_array.cpp") # Note: hope that CMake could find suffix_array.cpp under CMAKE_SOURCE_DIR?

# Add directory of the configure file to list of include paths
target_include_directories(suffix_array_test PUBLIC
    "${${PROJECT_NAME}_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include") # add include directories to a target (i.e. a binary executable)

# specify C++ standard
# set(CMAKE_CXX_STANDARD 14) -- does not work on clang and macos, set -std=c++14 flag instead
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add GCC compiler flags
set(GCC_COVERAGE_COMPILER_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILER_FLAGS}")