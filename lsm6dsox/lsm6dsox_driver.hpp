#include "lsm6dsox_bus.hpp"
#include "lsm6dsox_regs.hpp"
#include "lsm6dsox_configuration.hpp"
#include "register.hpp"

namespace lsm6dsox {

    enum class Interface {
        I2C,
        SPI
    };

    template<Bus T, Interface interfaceType, Configuration config=Configuration::DEFAULT>
    class Driver {
    public:
        Driver(T& bus) : bus_(bus) {}

        bool init() {
            if (!init_interface_()) {
                return false;
            }

            return true;
        }

    private:
    // Member functions
        bool init_interface_() {
            uint8_t data = 0;
            // read and store CTRL4_C for bit manipulation
            if (!read_reg_(reg::CTRL4_C, data)) return false;
            
            if constexpr (interfaceType == Interface::I2C) {
                data &= ~(1u << reg::CTRL4_C::I2C_DISABLE);
                
            } else if constexpr (interfaceType == Interface::SPI) {
                data |= (1u << reg::CTRL4_C::I2C_DISABLE);
            }
            return write_reg_(reg::CTRL4_C, data);
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
        Register ctrl5_g_{CTRL5_C::RESET_VALUE};
        Register ctrl7_g_{CTRL7_G::RESET_VALUE};

    };  

}