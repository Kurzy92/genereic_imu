#pragma once
#include <cstdint>
#include <concepts>

template<typename T>
concept Bus = requires(T bus, uint8_t reg, uint8_t* buf, size_t len) {
    { bus.read(reg, buf, len) } -> std::same_as<bool>;
    { bus.write(reg, buf, len) } -> std::same_as<bool>;
};  