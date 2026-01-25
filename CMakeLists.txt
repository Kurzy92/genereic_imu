cmake_minimum_required(VERSION 3.20)
project(generic_imu LANGUAGES CXX)

add_library(generic_imu STATIC
    drivers/lsm6dsox/lsm6dsox.cpp
)

target_include_directories(generic_imu PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/imu
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/external/embedded_utils/include
)

target_compile_features(generic_imu PUBLIC cxx_std_20)
