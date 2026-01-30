include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest)

add_executable(imu_tests imu_tests.cpp)

target_link_libraries(imu_tests
    PRIVATE
    GTest::GTest
    imu
)

add_test(NAME imu_tests COMMAND imu_tests)
