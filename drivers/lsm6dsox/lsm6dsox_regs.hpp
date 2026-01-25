#pragma once
#include <cstdint>

namespace lsm6dsox {

    namespace reg {
        constexpr uint8_t FUNC_CFG_ACCESS   = 0x01;
        constexpr uint8_t WHO_AM_I          = 0x0F;
        constexpr uint8_t INT1_CTRL         = 0x0D;
        constexpr uint8_t INT2_CTRL         = 0x0E;
        constexpr uint8_t CTRL1_XL          = 0x10;
        constexpr uint8_t CTRL2_G           = 0x11;
        constexpr uint8_t CTRL3_C           = 0x12;
        constexpr uint8_t CTRL4_C           = 0x13;
        constexpr uint8_t CTRL5_C           = 0x14;
        constexpr uint8_t CTRL6_C           = 0x15;
        constexpr uint8_t CTRL7_G           = 0x16;
        constexpr uint8_t CTRL8_XL          = 0x17;
        constexpr uint8_t CTRL9_XL          = 0x18;
        constexpr uint8_t CTRL10_C          = 0x19;
        constexpr uint8_t OUT_TEMP_L        = 0x20;
        constexpr uint8_t OUT_TEMP_H        = 0x21;
        constexpr uint8_t OUTX_L_G          = 0x22;
        constexpr uint8_t OUTX_H_G          = 0x23;
        constexpr uint8_t OUTY_L_G          = 0x24;
        constexpr uint8_t OUTY_H_G          = 0x25;
        constexpr uint8_t OUTZ_L_G          = 0x26;
        constexpr uint8_t OUTZ_H_G          = 0x27;
        constexpr uint8_t OUTX_L_XL         = 0x28;
        constexpr uint8_t OUTX_H_XL         = 0x29; 
        constexpr uint8_t OUTY_L_XL         = 0x2A;
        constexpr uint8_t OUTY_H_XL         = 0x2B;
        constexpr uint8_t OUTZ_L_XL         = 0x2C;
        constexpr uint8_t OUTZ_H_XL         = 0x2D;
    }

    // Constants
    constexpr uint8_t WHO_AM_I_RESPONSE     = 0x6C;

    // Registers Masks

    namespace INT1_CTRL {
        constexpr uint8_t INT1_DRDY_XL      = 0x00;
        constexpr uint8_t INT1_DRDY_G       = 0x01;
        constexpr uint8_t INT1_BOOT         = 0x02;
        constexpr uint8_t INT1_FTH          = 0x03;
        constexpr uint8_t INT1_OVRUN        = 0x04;
        constexpr uint8_t INT1_FSS5         = 0x05;
        constexpr uint8_t INT1_CNT_BDR      = 0x06;
        constexpr uint8_t DEN_DRDY_flag     = 0x07;

        constexpr uint8_t RESET_VALUE       = 0x00;
    }

    namespace INT2_CTRL {
        constexpr uint8_t INT2_DRDY_XL      = 0x00;
        constexpr uint8_t INT2_DRDY_G       = 0x01;
        constexpr uint8_t INT2_DRDY_TEMP    = 0x02;
        constexpr uint8_t INT2_FTH          = 0x03;
        constexpr uint8_t INT2_OVRUN        = 0x04;
        constexpr uint8_t INT2_FSS5         = 0x05;
        constexpr uint8_t INT2_CNT_BDR      = 0x06;

        constexpr uint8_t RESET_VALUE       = 0x00;
    }

    namespace CTRL1_XL {
        constexpr uint8_t LPF2_XL_EN        = 0x01;
        constexpr uint8_t FS_XL_H           = 0x02;
        constexpr uint8_t ODR_XL            = 0x04;

        enum class FS_XL_e {
            FS_2g                           = 0b00,
            FS_16g                          = 0b01,
            FS_4g                           = 0b10,
            FS_8g                           = 0b11
        };

        enum class ODR_XL_e {
            ODR_XL_OFF                     = 0b0000,
            ODR_XL_12_5Hz                  = 0b0001,
            ODR_XL_26Hz                    = 0b0010,
            ODR_XL_52Hz                    = 0b0011,
            ODR_XL_104Hz                   = 0b0100,
            ODR_XL_208Hz                   = 0b0101,
            ODR_XL_417Hz                   = 0b0110,
            ODR_XL_833Hz                   = 0b0111,
            ODR_XL_1_66kHz                 = 0b1000,
            ODR_XL_3_33kHz                 = 0b1001,
            ODR_XL_6_66kHz                 = 0b1010,
            ODR_XL_1_33kHz                 = 0b1011,
            ODR_XL_2_66kHz                 = 0b1100,
            ODR_XL_5_33kHz                 = 0b1101,
            ODR_XL_10_66kHz                = 0b1110,
            ODR_XL_21_33kHz                = 0b1111
        };

        constexpr uint8_t RESET_VALUE      = 0x00;
    }
    
    namespace CTRL2_G {
        constexpr uint8_t FS_125Hz         = 0x01;
        constexpr uint8_t FS_G             = 0x02;
        constexpr uint8_t ODR_G            = 0x04;

        enum class FS_G_e {
            FS_250dps                      = 0b00,
            FS_500dps                      = 0b01,
            FS_1000dps                     = 0b10,
            FS_2000dps                     = 0b11
        };

        enum class ODR_G_e {
            ODR_G_OFF                      = 0b0000,
            ODR_G_12_5Hz                   = 0b0001,
            ODR_G_26Hz                     = 0b0010,
            ODR_G_52Hz                     = 0b0011,
            ODR_G_104Hz                    = 0b0100,
            ODR_G_208Hz                    = 0b0101,
            ODR_G_416Hz                    = 0b0110,
            ODR_G_833Hz                    = 0b0111,
            ODR_G_1_66kHz                  = 0b1000,
            ODR_G_3_33kHz                  = 0b1001,
            ODR_G_6_66kHz                  = 0b1010,
        };

        constexpr uint8_t RESET_VALUE      = 0x00;
    }

    namespace CTRL3_C {
        constexpr uint8_t SW_RESET         = 0x00;
        constexpr uint8_t IF_INC           = 0x02;
        constexpr uint8_t SIM              = 0x03;
        constexpr uint8_t PP_OD            = 0x04;
        constexpr uint8_t H_LACTIVE        = 0x05;
        constexpr uint8_t BDU              = 0x06;
        constexpr uint8_t BOOT             = 0x07;

        constexpr uint8_t RESET_VALUE      = 0x04;  // IF_INC bit is 1 at reset
    }

    namespace CTRL4_C {
        constexpr uint8_t LPF1_SEL_G       = 0x01;
        constexpr uint8_t I2C_DISABLE      = 0x02;
        constexpr uint8_t DRDY_MASK        = 0x03;
        constexpr uint8_t INT2_ON_INT1     = 0x05;
        constexpr uint8_t SLEEP_G          = 0x06;

        constexpr uint8_t RESET_VALUE      = 0x00;
    }

    namespace CTRL5_C {
        constexpr uint8_t ST0_XL            = 0x00;
        constexpr uint8_t ST1_XL            = 0x01;
        constexpr uint8_t ST0_G             = 0x02;
        constexpr uint8_t ST1_G             = 0x03;
        constexpr uint8_t ROUNDING_STATUS   = 0x04;
        constexpr uint8_t ROUNDING0         = 0x05;
        constexpr uint8_t ROUNDING1         = 0x06;
        constexpr uint8_t XL_ULP_EN         = 0x07;

        constexpr uint8_t RESET_VALUE       = 0x00;
    }

    namespace CTRL6_C {
        constexpr uint8_t FTYPE_0           = 0x00;
        constexpr uint8_t FTYPE_1           = 0x01;
        constexpr uint8_t FTYPE_2           = 0x02;
        constexpr uint8_t USR_OFF_W         = 0x03;
        constexpr uint8_t XL_HM_MODE        = 0x04;
        constexpr uint8_t LVL2_EN           = 0x05;
        constexpr uint8_t LVL1_EN           = 0x06;
        constexpr uint8_t TRIG_EN           = 0x07;

        constexpr uint8_t RESET_VALUE       = 0x00;
    }

    namespace CTRL7_G {
        constexpr uint8_t OIS_ON            = 0x00;
        constexpr uint8_t USR_OFF_ON_OUT    = 0x01;
        constexpr uint8_t OIS_ON_EN         = 0x02;
        constexpr uint8_t HPM0_G            = 0x04;
        constexpr uint8_t HPM1_G            = 0x05;
        constexpr uint8_t HP_EN_G           = 0x06;
        constexpr uint8_t G_HM_MODE         = 0x07;

        constexpr uint8_t RESET_VALUE       = 0x00;
    }
} // namespace lsm6dsox


