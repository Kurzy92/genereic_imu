#pragma once
#include <gtest/gtest.h>
#include "fake_drivers.hpp"
#include "imu.hpp"

using namespace imu;

TEST(IMU, 9DOF_InitTest) {
    FakeTimer timer;
    FakeAccel accel;
    FakeGyro gyro;
    FakeMag mag;
    IMU<FakeTimer,FakeAccel, FakeGyro, FakeMag> imu(timer, accel, gyro, mag);

    EXPECT_EQ(imu.init(), Status::OK) << "IMU init failed";
    EXPECT_EQ(timer.init_calls, 1) << "Timer init not called once";
    EXPECT_EQ(accel.init_calls, 1) << "Accel init not called once";
    EXPECT_EQ(gyro.init_calls, 1) << "Gyro init called when not present";
    EXPECT_EQ(mag.init_calls, 1) << "Mag init called when not present";
}

TEST(IMU, 6DOF_InitTest) {
    FakeTimer timer;
    FakeAccel accel;
    FakeGyro gyro;
    IMU<FakeTimer,FakeAccel, FakeGyro> imu(timer, accel, gyro);

    EXPECT_EQ(imu.init(), Status::OK) << "IMU init failed";
    EXPECT_EQ(timer.init_calls, 1) << "Timer init not called once";
    EXPECT_EQ(accel.init_calls, 1) << "Accel init not called once";
    EXPECT_EQ(gyro.init_calls, 1) << "Gyro init not called once";
}

TEST(IMU, 3DOF_InitTest) {
    FakeTimer timer;
    FakeAccel accel;
    IMU<FakeTimer,FakeAccel> imu(timer, accel);

    EXPECT_EQ(imu.init(), Status::OK) << "IMU init failed";
    EXPECT_EQ(timer.init_calls, 1) << "Timer init not called once";
    EXPECT_EQ(accel.init_calls, 1) << "Accel init not called once";
}

TEST(IMU, Bad_InitTest) {
    FakeTimer timer;
    FakeAccel accel;
    FakeGyro gyro;
    FakeMag mag;
    imu::IMU<FakeTimer,FakeAccel, FakeGyro, FakeMag> imu(timer, accel, gyro, mag);

    timer.init_status = Status::BusError;
    EXPECT_EQ(imu.init(), Status::BusError) << "IMU init should have failed on timer";

    timer.init_status = Status::OK;
    accel.init_status = Status::NotReady;
    EXPECT_EQ(imu.init(), Status::NotReady) << "IMU init should have failed on accel";

    accel.init_status = Status::OK;
    gyro.init_status = Status::Timeout;
    EXPECT_EQ(imu.init(), Status::Timeout) << "IMU init should have failed on gyro";

    gyro.init_status = Status::OK;
    mag.init_status = Status::BadId;
    EXPECT_EQ(imu.init(), Status::BadId) << "IMU init should have failed on mag";
}

TEST(IMU, Read_AccelTest) {
    FakeTimer timer;
    FakeAccel accel;
    FakeGyro gyro;
    FakeMag mag;
    imu::IMU<FakeTimer,FakeAccel, FakeGyro, FakeMag> imu(timer, accel, gyro, mag);

    Accel_mps2 out;


    EXPECT_EQ(imu.read_accel(out), Status::OK) << "Accel read failed - read: " << 
    "out.x=" + std::to_string(out.x) 
    + ", out.y=" + std::to_string(out.y) 
    + ", out.z=" + std::to_string(out.z);

    EXPECT_EQ(accel.read_calls, 1) << "Accel read not called once";
    EXPECT_EQ(gyro.read_calls, 0) << "Gyro read called when not present";
    EXPECT_EQ(mag.read_calls, 0) << "Mag read called when not present";
}

TEST(IMU, Read_GyroTest) {
    FakeTimer timer;
    FakeAccel accel;
    FakeGyro gyro;
    FakeMag mag;
    imu::IMU<FakeTimer,FakeAccel, FakeGyro, FakeMag> imu(timer, accel, gyro, mag);

    Gyro_rads out;

    EXPECT_EQ(imu.read_gyro(out), Status::OK) << "Gyro read failed";
    EXPECT_EQ(accel.read_calls, 0) << "Accel read called when not present";
    EXPECT_EQ(gyro.read_calls, 1) << "Gyro read not called once";
    EXPECT_EQ(mag.read_calls, 0) << "Mag read called when not present";
}

TEST(IMU, Read_MagTest) {
    FakeTimer timer;
    FakeAccel accel;
    FakeGyro gyro;
    FakeMag mag;
    imu::IMU<FakeTimer,FakeAccel, FakeGyro, FakeMag> imu(timer, accel, gyro, mag);

    Mag_uT out;

    EXPECT_EQ(imu.read_mag(out), Status::OK) << "Mag read failed";
    EXPECT_EQ(accel.read_calls, 0) << "Accel read called when not present";
    EXPECT_EQ(gyro.read_calls, 0) << "Gyro read called when not present";
    EXPECT_EQ(mag.read_calls, 1) << "Mag read not called once";
}

TEST(IMU, Read_AllTest) {
    FakeTimer timer;
    FakeAccel accel;
    FakeGyro gyro;
    FakeMag mag;
    imu::IMU<FakeTimer,FakeAccel, FakeGyro, FakeMag> imu(timer, accel, gyro, mag);

    Accel_mps2 a_out;
    Gyro_rads g_out;
    Mag_uT m_out;

    EXPECT_EQ(imu.read_all(a_out, g_out, m_out), Status::OK) << "IMU read failed";
    EXPECT_EQ(accel.read_calls, 1) << "Accel read not called once";
    EXPECT_EQ(gyro.read_calls, 1) << "Gyro read not called once";
    EXPECT_EQ(mag.read_calls, 1) << "Mag read not called once";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


