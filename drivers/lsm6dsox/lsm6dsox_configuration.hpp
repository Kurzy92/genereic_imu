
#pragma once    

#include "lsm6dsox_regs.hpp"

namespace lsm6dsox {
    using namespace reg;

    enum class Configuration {
        DEFAULT,
        HIGH_PERFORMANCE,
        LOW_POWER
    };

    struct AccelConfig {
        CTRL1_XL::ODR_XL_e odr;
        CTRL1_XL::FS_XL_e fs;
        float mg_per_lsb;
        
        constexpr AccelConfig(  CTRL1_XL::ODR_XL_e odr, 
                                CTRL1_XL::FS_XL_e fs, 
                                float mg_per_lsb
                            ) : odr(odr), fs(fs), mg_per_lsb(mg_per_lsb) {}
    };

    struct GyroConfig {
        CTRL2_G::ODR_G_e odr;
        CTRL2_G::FS_G_e fs;
        float mdps_per_lsb;
        
        constexpr GyroConfig(   CTRL2_G::ODR_G_e odr, 
                                CTRL2_G::FS_G_e fs, 
                                float mdps_per_lsb
                            ) : odr(odr), fs(fs), mdps_per_lsb(mdps_per_lsb) {}
    };

    struct PresetConfig {
        AccelConfig accel;
        GyroConfig gyro;
    };

    template<Configuration C>
    struct ConfigTraits {
        static_assert(false, "ConfigTraits not specialized for this Configuration");
    };

    template<>
    struct ConfigTraits<Configuration::DEFAULT> {
        static inline constexpr PresetConfig preset {
            AccelConfig(CTRL1_XL::ODR_XL_e::ODR_XL_104Hz, CTRL1_XL::FS_XL_e::FS_2g, 0.061f),
            GyroConfig(CTRL2_G::ODR_G_e::ODR_G_104Hz, CTRL2_G::FS_G_e::FS_250dps, 0.0076f)
        };
    };
    
    template<>
    struct ConfigTraits<Configuration::HIGH_PERFORMANCE> {
        static inline constexpr PresetConfig preset {
            AccelConfig(CTRL1_XL::ODR_XL_e::ODR_XL_104Hz, CTRL1_XL::FS_XL_e::FS_2g, 0.061f),
            GyroConfig(CTRL2_G::ODR_G_e::ODR_G_104Hz, CTRL2_G::FS_G_e::FS_250dps, 0.0076f)
        };
    };
    
    template<>
    struct ConfigTraits<Configuration::LOW_POWER> {
        static inline constexpr PresetConfig preset {
            AccelConfig(CTRL1_XL::ODR_XL_e::ODR_XL_104Hz, CTRL1_XL::FS_XL_e::FS_2g, 0.061f),
            GyroConfig(CTRL2_G::ODR_G_e::ODR_G_104Hz, CTRL2_G::FS_G_e::FS_250dps, 0.0076f)
        };
    };
}
    
    

