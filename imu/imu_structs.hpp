#pragma once
#include <cstdint>
#include <type_traits>
#include <concepts>

namespace imu {
    enum class [[nodiscard]] Status : uint8_t {
        OK = 0,
        BusError,
        NotReady,
        BadId,
        Timeout,
        NotPresent
    };
    
    // Units    
    struct Accel_mps2 { float x, y, z; };   // m/s^2
    struct Gyro_rads { float x, y, z; };    // rad/s
    struct Mag_uT { float x, y, z; };       // uT  
    
    // Compile-time checks for driver interfaces
    template<typename T>
    concept AccelDriver = requires(T d, Accel_mps2& out) {
        { d.init() } noexcept -> std::same_as<Status>;
        { d.read(out) } noexcept -> std::same_as<Status>;
    };

    template<typename T>
    concept GyroDriver = requires(T d, Gyro_rads& out) {
        { d.init() } noexcept -> std::same_as<Status>;
        { d.read(out) } noexcept -> std::same_as<Status>;
        { T::present } -> std::convertible_to<bool>;
    };

    template<typename T>
    concept MagDriver = requires(T d, Mag_uT& out) {
        { d.init() } noexcept -> std::same_as<Status>;
        { d.read(out) } noexcept -> std::same_as<Status>;
        { T::present } -> std::convertible_to<bool>;
    };

    template<typename T>
    concept TimerSource = requires(T t, uint32_t& out) {
        { t.init() } noexcept -> std::same_as<Status>; 
        { t.now_us(out) } noexcept -> std::same_as<Status>;
    };

    // Null drivers
    struct NullGyro {
        static constexpr bool present = false;
        Status init() noexcept { return Status::NotPresent; }
        Status read(Gyro_rads& out) noexcept { return Status::NotPresent; }
    };

    struct NullMag {
        static constexpr bool present = false;
        Status init() noexcept { return Status::NotPresent; }
        Status read(Mag_uT& out) noexcept { return Status::NotPresent; }
    };

}