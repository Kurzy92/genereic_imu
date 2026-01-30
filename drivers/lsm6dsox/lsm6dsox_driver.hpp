#include "../driver_bus.hpp"
#include "lsm6dsox_regs.hpp"
#include "lsm6dsox_configuration.hpp"
#include "register.hpp"

namespace lsm6dsox {

    template<DriverBus T, Configuration config=Configuration::DEFAULT>
    class Driver {
    public:
        Driver(T& bus) : bus_(bus) {}

        bool init() {
            if (!init_interface_()) {
                return false;
            }

            if (!check_id_()) {
                return false;
            }
            
            return true;
        }

        bool read_accel(int16_t& x, int16_t& y, int16_t& z) {
            uint8_t data[6];
            if (!bus_.read(reg::OUTX_L_XL, data, 6)) {
                return false;
            }

            x = static_cast<int16_t>(data[0] | (data[1] << 8));
            y = static_cast<int16_t>(data[2] | (data[3] << 8));
            z = static_cast<int16_t>(data[4] | (data[5] << 8));

            return true;
        }

    private:
    // Member functions
        bool init_interface_() {
            if constexpr (T::interface == imu::bus::Interface::I2C) {
                ctrl4_c_.clear_bit(reg::CTRL4_C::I2C_DISABLE);
                
            } else if constexpr (T::interface == imu::bus::Interface::SPI) {
                ctrl4_c_.set_bit(reg::CTRL4_C::I2C_DISABLE);
            }
            return write_reg_(reg::CTRL4_C, ctrl4_c_.get_value());
        }

        // Check WHO_AM_I register
        bool check_id_() {
            uint8_t id;
            if (!read_reg_(reg::WHO_AM_I, id)) {
                return false;
            }
            return id == reg::WHO_AM_I::ID;
        }

        // Register read/write helpers
        bool read_reg_(uint8_t reg, uint8_t& data) {
            return bus_.read(reg, &data, 1);
        }

        bool write_reg_(uint8_t reg, uint8_t data) {
            return bus_.write(reg, &data, 1);
        }

    private:
    // Member variables
        T& bus_;

        // Registers
        Register ctrl1_xl_{CTRL1_XL::RESET_VALUE};
        Register ctrl2_g_{CTRL2_G::RESET_VALUE};
        Register ctrl3_c_{CTRL3_C::RESET_VALUE};
        Register ctrl4_c_{CTRL4_C::RESET_VALUE};
        Register ctrl5_g_{CTRL5_G::RESET_VALUE};
        Register ctrl7_g_{CTRL7_G::RESET_VALUE};

    };  

}