#include "lsm6dsox_bus.hpp"
#include "lsm6dsox_regs.hpp"

namespace lsm6dsox {

    enum class Interface {
        I2C,
        SPI
    };

    enum class Configuration {
        DEFAULT,
        HIGH_PERFORMANCE,
        LOW_POWER
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
    };  

}