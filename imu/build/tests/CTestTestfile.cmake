# CMake generated Testfile for 
# Source directory: C:/Projects/Embedded/IMUs/imu/tests
# Build directory: C:/Projects/Embedded/IMUs/imu/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[imu_tests]=] "C:/Projects/Embedded/IMUs/imu/build/tests/imu_tests.exe")
set_tests_properties([=[imu_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Projects/Embedded/IMUs/imu/tests/CMakeLists.txt;20;add_test;C:/Projects/Embedded/IMUs/imu/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
