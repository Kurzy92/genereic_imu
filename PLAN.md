# Project Goals

    1. Create a portable C++20 IMU framework, that outputs IMU data for use in different systems
    2. Focus on good code quality and principles

## IMU Architecture 

    1. The IMU class is a templated class that takes in an accelerometer and gyroscope driver, and an optional magnetometer driver. It provides a single interface for reading IMU data, and outputs IMU data in a standard format.
    2. The IMU class is designed to be portable, and can be used with any accelerometer and gyroscope drivers that implement the required interface.
    
## IMU Interfaces

    The IMU class requires several interfaces (c++20 concepts) to be implemented in order to work. These interfaces are:
    1. **AccelDriver** - An interface for reading data from an accelerometer
    2. **GyroDriver** - An interface for reading data from a gyroscope
    3. **MagDriver** - An interface for reading data from a magnetometer

    The IMU also defines null drivers for use cases where we don't need to use either a gyroscope, a magnetometer, or both:
    1. NullGyro - A null gyroscope driver that returns a fixed value for all gyroscope readings
    2. NullMag - A null magnetometer driver that returns a fixed value for all magnetometer readings

    The above interfaces requires implementing adapters utilizing the sensors drivers. The IMU class will then use these adapters to read data from the sensors.

## Architecture Layers

    The framework is organized into four distinct layers:

    ```
    ┌─────────────────────────────────────────┐
    │           IMU Abstraction               │
    │   Unified interface for 3/6/9 DOF       │
    └─────────────────────────────────────────┘
                        │
                        ▼
    ┌─────────────────────────────────────────┐
    │            Driver Layer                 │
    │   Sensor-specific (LSM6DSOX, etc...)    │
    └─────────────────────────────────────────┘
                        │
                        ▼
    ┌─────────────────────────────────────────┐
    │             Bus Layer                   │
    │   I2C / SPI abstraction (concept)       │
    └─────────────────────────────────────────┘
                        │
                        ▼
    ┌─────────────────────────────────────────┐
    │           Platform Layer                │
    │   MCU-specific (STM32 HAL, ESP-IDF)     │
    └─────────────────────────────────────────┘
    ```

    1. **IMU Abstraction** (`imu/`) - The top-level interface that applications use. Handles sensor composition and provides unified read methods.

    2. **Driver Layer** (`drivers/`) - Sensor-specific implementations that know how to configure registers, read raw data, and convert to SI units. Each driver implements the required concept interface.

    3. **Bus Layer** - A concept-based abstraction (`Bus`) that defines read/write operations. Drivers depend on this concept, not concrete implementations.

    4. **Platform Layer** (`platforms/`) - MCU-specific implementations of the Bus concept. This is where HAL calls live, keeping all other layers portable.

## Design Rationale

### Why C++20 Concepts over Virtual Interfaces?

    - **Zero runtime overhead** - No vtable lookups, no indirect calls. Critical for embedded where every cycle counts.
    - **Compile-time errors** - Interface mismatches are caught during compilation, not at runtime.
    - **Better optimization** - Compiler can inline and optimize across abstraction boundaries.
    - **No heap allocation** - Virtual interfaces often require pointers/dynamic allocation; templates work with value semantics.

### Why SI Units at the Interface Boundary?

    - **Consistency** - All drivers output the same units regardless of sensor sensitivity settings.
    - **Safety** - No unit conversion bugs at the application level.
    - **Clarity** - `Accel_mps2`, `Gyro_rads`, `Mag_uT` are self-documenting.
    - Conversion from raw counts to SI units happens once, inside the driver.

### Why Status-Based Error Handling?

    - **No exceptions** - Most embedded toolchains disable exceptions for code size/determinism.
    - **Explicit checking** - `[[nodiscard]]` forces callers to handle errors.
    - **Lightweight** - Single byte enum, no overhead.

### Why Template-Based Configuration?

    - **Compile-time selection** - `Configuration::HIGH_PERFORMANCE` vs `Configuration::LOW_POWER` resolved at build time.
    - **Dead code elimination** - Unused configurations don't bloat the binary.
    - **Type safety** - Can't accidentally mix incompatible configurations.

## Milestones & TODO's

## Milestone 1: Basic IMU Framework