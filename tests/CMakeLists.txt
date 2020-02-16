# add the executables I want to generate
add_executable(suffix_array_test "suffix_array.cpp") # Note: hope that CMake could find suffix_array.cpp under CMAKE_SOURCE_DIR?

# Add directory of the configure file to list of include paths
target_include_directories(suffix_array_test PUBLIC
    "${${PROJECT_NAME}_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include") # add include directories to a target (i.e. a binary executable)