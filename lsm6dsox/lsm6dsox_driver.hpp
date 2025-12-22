#include "lsm6dsox_bus.hpp"

namespace lsm6dsox {

    enum class Interface {
        I2C,
        SPI
    };

    template<Bus T, Interface interfaceType>
    class Driver {
    public:
        Driver(T bus) : bus(bus) {}

        bool init() {
            return true;
        }

        bool read(uint8_t reg, uint8_t* buf, size_t len) {
            return bus.read(reg, buf, len);
        }

        bool write(uint8_t reg, uint8_t* buf, size_t len) {
            return bus.write(reg, buf, len);
        }

    private:
        T bus;
    };  

}