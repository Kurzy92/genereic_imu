#pragma once
#include <cstdint>
#include <concepts>

namespace imu::bus {
    enum class Interface {
        I2C,
        SPI
    };
}

template<typename T>
concept DriverBus = requires(T bus, uint8_t reg, uint8_t* buf, size_t len) {
    { T::interface } noexcept -> std::convertible_to<imu::bus::Interface>;
    { bus.read(reg, buf, len) } noexcept -> std::same_as<bool>;
    { bus.write(reg, buf, len) } noexcept -> std::same_as<bool>;
};  