cmake_minimum_required(VERSION 3.22)
add_library(imu INTERFACE)

enable_testing()
add_subdirectory(tests)
target_include_directories(imu INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
