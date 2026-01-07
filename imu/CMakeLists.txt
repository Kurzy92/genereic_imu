add_library(imu INTERFACE)

target_include_directories(imu INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(imu INTERFACE c_std_20)