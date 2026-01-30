# Drivers

This folder contains **sensor-specific drivers** used to construct adapter objects
that satisfy the IMU interfaces defined in `imu/imu_structs.hpp`.

Sensor drivers are **not used directly by the IMU class**.
Instead, they provide the sensor-specific functionality required by the adapter
layer, which exposes the generic IMU interfaces (`AccelDriver`, `GyroDriver`, `MagDriver`).

---

## Overview

Drivers bridge the gap between generic IMU interfaces and concrete sensor hardware.

Each driver:
    - Knows the sensor register map
    - Performs sensor initialization and configuration
    - Reads raw sensor data
    - Converts raw values to SI units
    - Remains completely MCU- and HAL-agnostic

Drivers do **not** perform low-level I/O themselves.
All register access is delegated to a bus object supplied by the user.

---

## DriverBus Interface

Before instantiating a driver, a platform-specific **bus implementation** must be
provided that satisfies the `DriverBus` concept defined in `driver_bus.hpp`.

The bus implementation is responsible for performing low-level register access
using the appropriate physical interface (SPI or I2C).

### Requirements

| Requirement            | Description                                                                       |
| ---------------------- | --------------------------------------------------------------------------------- |
| `interface`            | Static member specifying `imu::bus::Interface::I2C` or `imu::bus::Interface::SPI` |
| `read(reg, buf, len)`  | Read `len` bytes starting at register `reg` into `buf`                            |
| `write(reg, buf, len)` | Write `len` bytes from `buf` starting at register `reg`                           |

All operations must be `noexcept` and report errors via return values.

---

## Example Bus Implementation

```cpp
#include "driver_bus.hpp"

class MyI2CBus {
public:
    static constexpr imu::bus::Interface interface =
        imu::bus::Interface::I2C;

    MyI2CBus(I2C_HandleTypeDef* hi2c, uint8_t addr)
        : hi2c_(hi2c), addr_(addr) {}

    bool read(uint8_t reg, uint8_t* buf, size_t len) noexcept {
        return HAL_I2C_Mem_Read(
            hi2c_, addr_, reg, 1, buf, len, 100
        ) == HAL_OK;
    }

    bool write(uint8_t reg, const uint8_t* buf, size_t len) noexcept {
        return HAL_I2C_Mem_Write(
            hi2c_, addr_, reg, 1, const_cast<uint8_t*>(buf), len, 100
        ) == HAL_OK;
    }

private:
    I2C_HandleTypeDef* hi2c_;
    uint8_t addr_;
};
