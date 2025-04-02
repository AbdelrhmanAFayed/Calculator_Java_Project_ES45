#include "HLCD.h"
#include "HLCD_cfg.h"

HLCD_strCfg_t HLCD_cfgArr[NUMBER_OF_LCD] = {
    [LCD_ONE] = {
        .HLCD_Mode = HLCD_8_BIT_MODE,
        .HLCD_DataPins = {
            [HLCD_PIN_0] = MPORT_PINC_0,
            [HLCD_PIN_1] = MPORT_PINC_1,
            [HLCD_PIN_2] = MPORT_PINC_2,
            [HLCD_PIN_3] = MPORT_PINC_3,
            [HLCD_PIN_4] = MPORT_PINC_4,
            [HLCD_PIN_5] = MPORT_PINC_5,
            [HLCD_PIN_6] = MPORT_PINC_6,
            [HLCD_PIN_7] = MPORT_PINC_7,
        },
        .HLCD_PowerPins = {
            [HLCD_RS_PIN] = MPORT_PIND_2,
            [HLCD_RW_PIN] = MPORT_PIND_1,
            [HLCD_EN_PIN] = MPORT_PIND_0,
        }
    }
};
