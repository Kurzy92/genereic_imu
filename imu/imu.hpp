#pragma once
#include "imu_structs.hpp"


namespace imu {
    // IMU class
    template<TimerSource Timer,
            AccelDriver Accel, 
            GyroDriver Gyro=NullGyro, 
            MagDriver Mag=NullMag
            >

    class IMU {
    public:
        static constexpr bool gyro_present = Gyro::present;
        static constexpr bool mag_present = Mag::present;

        constexpr IMU(Timer& timer, Accel& accel, Gyro& gyro, Mag& mag) noexcept
            : timer_(timer), accel_(accel), gyro_(gyro), mag_(mag) {}

        // Convinience constructors 3DoF / 6DoF
        constexpr IMU(Timer& timer, Accel& accel) noexcept
        requires std::same_as<Gyro, NullGyro> && std::same_as<Mag, NullMag>
            : timer_(timer), accel_(accel), gyro_(null_gyro_), mag_(null_mag_) {}  

        constexpr IMU(Timer& timer, Accel& accel, Gyro& gyro) noexcept
        requires std::same_as<Mag, NullMag>
            : timer_(timer), accel_(accel), gyro_(gyro), mag_(null_mag_) {}

        [[nodiscard]] Status init() noexcept {
            if (auto s = timer_.init(); s != Status::OK) return s;
            if (auto s = accel_.init(); s != Status::OK) return s;
            if constexpr (gyro_present) {
                if (auto s = gyro_.init(); s != Status::OK) return s;
            }
            if constexpr (mag_present) {
                if (auto s = mag_.init(); s != Status::OK) return s;
            }
            return Status::OK;
        }

        [[nodiscard]] Status read_accel(Accel_mps2& out) noexcept {
            return accel_.read(out);
        }

        [[nodiscard]] Status read_gyro(Gyro_rads& out) noexcept {
            if constexpr (gyro_present) {
                return gyro_.read(out);
            } else {
                return Status::NotPresent;
            }
        }

        [[nodiscard]] Status read_mag(Mag_uT& out) noexcept {
            if constexpr (mag_present) {
                return mag_.read(out);
            } else {
                return Status::NotPresent;
            }
        }

        [[nodiscard]] Status read_all(Accel_mps2&   a_out, 
                                    Gyro_rads&     g_out = nullptr,
                                    Mag_uT&        m_out = nullptr) noexcept {
            
            uint32_t tmpTimer = 0;
            if (auto s = timer_.now_us(tmpTimer); s != Status::OK) {
                return s;
            }
            
            last_t_us_ = tmpTimer;

            if (auto s = accel_.read(a_out); s != Status::OK) 
                return s;

            if constexpr (gyro_present) {
                if (auto s = gyro_.read(g_out); s != Status::OK) 
                    return s;
            }
            if constexpr (mag_present) {
                if (auto s = mag_.read(m_out); s != Status::OK) 
                    return s;
            }
            return Status::OK;  
        }
    private:
        Timer& timer_;
        Accel& accel_;
        Gyro& gyro_;
        Mag& mag_;
        std::uint32_t last_t_us_{0u};

        inline static NullGyro null_gyro_{};
        inline static NullMag null_mag_{};
            
    };


}