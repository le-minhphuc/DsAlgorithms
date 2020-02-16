cmake_minimum_required(VERSION 3.12)

# set project name and version
project(DsAlgorithms VERSION 1.0) # set PROJECT_SOURCE_DIR to full path of current directory
# configure a header file to pass the version number from CMake to the source code
configure_file("include/version/DsAlgorithmsConfig.h.in" "DsAlgorithmsConfig.h")

# add GCC compiler flags - this need to be before any add_executable
set(GCC_COVERAGE_COMPILER_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILER_FLAGS}")

# execute CMake code in subdir called "tests/"
# targets specified in tests/CMakeLists.txt will be written to {current_bin_dir}/tests/
add_subdirectory(tests)