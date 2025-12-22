#pragma once
#include "imu_structs.hpp"


namespace imu {

    // IMU class

    template<AccelDriver Accel, 
            GyroDriver Gyro=NullGyro, 
            MagDriver Mag=NullMag>
    class IMU {
    public:
        static constexpr bool gyro_present = Gyro::present;
        static constexpr bool mag_present = Mag::present;

        constexpr IMU(Accel& accel, Gyro& gyro, Mag& mag) noexcept
            : accel_(accel), gyro_(gyro), mag_(mag) {}

        // Convinience constructors 3DoF / 6DoF
        constexpr IMU(Accel& accel) noexcept
        requires std::same_as<Gyro, NullGyro> && std::same_as<Mag, NullMag>
            : accel_(accel), gyro_(null_gyro_), mag_(null_mag_) {}  

        constexpr IMU(Accel& accel, Gyro& gyro) noexcept
        requires std::same_as<Mag, NullMag>
            : accel_(accel), gyro_(gyro), mag_(null_mag_) {}

        [[nodiscard]] Status init() noexcept {
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
                                    std::uint32_t  now_us,
                                    Gyro_rads*     g_out = nullptr,
                                    Mag_uT*        m_out = nullptr,
                                    std::uint32_t* dt_us_out = nullptr) noexcept {
            if(dt_us_out) *dt_us_out = (last_t_us_ == 0u) ? 0u : (now_us - last_t_us_);
            last_t_us_ = now_us;

            if (auto s = accel_.read(a_out); s != Status::OK) return s;
            if constexpr (gyro_present) {
                if (g_out) {
                    if (auto s = gyro_.read(*g_out); s != Status::OK) return s;
                }
            }
            if constexpr (mag_present) {
                if (m_out) {
                    if (auto s = mag_.read(*m_out); s != Status::OK) return s;
                }
            }
            return Status::OK;  
        }
    private:
        Accel& accel_;
        Gyro& gyro_;
        Mag& mag_;
        std::uint32_t last_t_us_{0u};

        inline static NullGyro null_gyro_{};
        inline static NullMag null_mag_{};
            
    };


}