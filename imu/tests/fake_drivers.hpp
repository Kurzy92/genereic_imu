#pragma once
#include "imu_structs.hpp"

struct FakeTimer {
    imu::Status init_status = imu::Status::OK;
    imu::Status now_status = imu::Status::OK;
    uint32_t current_time = 0;

    int init_calls = 0;
    int now_calls = 0;

    imu::Status init() noexcept {
        init_calls++;
        return init_status;
    }

    imu::Status now_us(uint32_t& out) noexcept {
        now_calls++;
        out = current_time;
        return now_status;
    }
};

struct FakeAccel {
    imu::Status init_status = imu::Status::OK;
    imu::Status read_status = imu::Status::OK;

    int init_calls = 0;
    int read_calls = 0;

    imu::Status init() noexcept {
        init_calls++;
        return init_status;
    }

    imu::Status read(imu::Accel_mps2& out) noexcept {
        read_calls++;
        out = {1.0f, 2.0f, 3.0f};
        return read_status;
    }
};

struct FakeGyro {
    imu::Status init_status = imu::Status::OK;
    imu::Status read_status = imu::Status::OK;
    static constexpr bool present = true;
    
    

    int init_calls = 0;
    int read_calls = 0;

    imu::Status init() noexcept {
        init_calls++;
        return init_status;
    }

    imu::Status read(imu::Gyro_rads& out) noexcept {
        read_calls++;
        out = {1.0f, 2.0f, 3.0f};
        return read_status;
    }
};

struct FakeMag {
    imu::Status init_status = imu::Status::OK;
    imu::Status read_status = imu::Status::OK;
    static constexpr bool present = true;


    int init_calls = 0;
    int read_calls = 0;

    imu::Status init() noexcept {
        init_calls++;
        return init_status;
    }

    imu::Status read(imu::Mag_uT& out) noexcept {
        read_calls++;
        out = {1.0f, 2.0f, 3.0f};
        return read_status;
    }
};