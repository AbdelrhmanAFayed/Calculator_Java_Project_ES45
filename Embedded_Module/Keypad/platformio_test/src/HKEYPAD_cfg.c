#include "HKEYPAD.h"
#include "HKEYPAD_cfg.h"

HKEYPAD_strCfg_t HKEYPAD_cfgArr[NUMBER_OF_KEYPADS] = {
    [KEYPAD_ONE] = {
        .HKEYPAD_RowPins = {
            [HKEYPAD_ROW_0] = MPORT_PINA_4,
            [HKEYPAD_ROW_1] = MPORT_PINA_5,
            [HKEYPAD_ROW_2] = MPORT_PINA_6,
            [HKEYPAD_ROW_3] = MPORT_PINA_7,
        },
        .HKEYPAD_ColumnPins = {
            [HKEYPAD_Column_0] = MPORT_PINA_3,
            [HKEYPAD_Column_1] = MPORT_PINA_2,
            [HKEYPAD_Column_2] = MPORT_PINA_1,
            [HKEYPAD_Column_3] = MPORT_PINA_0,
        }
    }
};
