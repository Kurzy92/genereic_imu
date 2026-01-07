cmake_minimum_required(VERSION 3.20)
project(lsm6dsox LANGUAGES CXX)

add_library(lsm6dsox STATIC lsm6dsox.cpp)


# bring in embedded_utils (folder above us)
add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../../embedded_utils
    ${CMAKE_BINARY_DIR}/embedded_utils_build
)

target_link_libraries(lsm6dsox PUBLIC embedded_utils)

target_include_directories(lsm6dsox PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/platform
)

target_compile_features(lsm6dsox PUBLIC cxx_std_20)
