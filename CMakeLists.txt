cmake_minimum_required(VERSION 3.22)
project(generic_imu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# target_include_directories(generic_imu PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}
#     ${CMAKE_CURRENT_LIST_DIR}/imu
#     ${CMAKE_CURRENT_LIST_DIR}/drivers
#     ${CMAKE_CURRENT_LIST_DIR}/external/embedded_utils
# )

# Testing
enable_testing()
add_subdirectory(imu)
add_subdirectory(external/embedded_utils)

# Run all tests with: cmake --build . --target check
add_custom_target(check_imu ALL
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS imu_tests 
)
