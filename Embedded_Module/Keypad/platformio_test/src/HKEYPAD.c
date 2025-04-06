#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"
#include "MPORT.h"
#include "HKEYPAD.h"
#include "HKEYPAD_cfg.h"
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

extern HKEYPAD_strCfg_t HKEYPAD_cfgArr[NUMBER_OF_KEYPADS];

HKEYPAD_enuErrorStatus_t HKEYPAD_enuInit(void)
{
    HKEYPAD_enuErrorStatus_t Ret_enuErrorStatus = HKEYPAD_OK;
    for(u8 iterator = 0; iterator < NUMBER_OF_KEYPADS ; iterator++)
    {
        for(u8 PinsIterator = 0 ; PinsIterator < HKEYPAD_MAX_ROW_NUM ; PinsIterator++ )
        {
            Ret_enuErrorStatus = MPORT_enuSetPinDirection(HKEYPAD_cfgArr[iterator].HKEYPAD_RowPins[PinsIterator],MPORT_INPUT);
            Ret_enuErrorStatus = MPORT_enuSetPinMode(HKEYPAD_cfgArr[iterator].HKEYPAD_RowPins[PinsIterator],MPORT_PIN_MODE_INPUT_PULLUP);
        }
        for(u8 PinsIterator = 0 ; PinsIterator < HKEYPAD_MAX_COLUMN_NUM ; PinsIterator++ )
        {
            Ret_enuErrorStatus = MPORT_enuSetPinDirection(HKEYPAD_cfgArr[iterator].HKEYPAD_ColumnPins[PinsIterator],MPORT_OUTPUT);
            Ret_enuErrorStatus = MDIO_enuSetPinValue((HKEYPAD_cfgArr[iterator].HKEYPAD_ColumnPins[PinsIterator]>>4),(HKEYPAD_cfgArr[iterator].HKEYPAD_ColumnPins[PinsIterator]&0x0F),MDIO_PIN_HIGH);
        }
    }
    return Ret_enuErrorStatus;
}

HKEYPAD_enuErrorStatus_t HKEYPAD_enuGetPressedKey(u8 * Add_u8PressedKey,u8 Copy_u8KeypadNum)
{
    HKEYPAD_enuErrorStatus_t Ret_enuErrorStatus = HKEYPAD_OK;
    if(NULL_PTR == Add_u8PressedKey)
    {
        Ret_enuErrorStatus = HKEYPAD_NULL_POINTER;
    }
    else if((Copy_u8KeypadNum < 0) || (Copy_u8KeypadNum > NUMBER_OF_KEYPADS) )
    {
        Ret_enuErrorStatus = HKEYPAD_INVALID_KEYPAD_NUM;
    }
    else
    {
        *Add_u8PressedKey = HKEYPAD_NO_KEY_PRESSED;
        bool Loc_u8IsKeyPressed = false;

        for(u8 ColumnIterator = 0 ; ColumnIterator < HKEYPAD_MAX_COLUMN_NUM ; ColumnIterator++)
        {
            /* set current column LOW */
            Ret_enuErrorStatus = MDIO_enuSetPinValue((HKEYPAD_cfgArr[Copy_u8KeypadNum].HKEYPAD_ColumnPins[ColumnIterator]>>4),(HKEYPAD_cfgArr[Copy_u8KeypadNum].HKEYPAD_ColumnPins[ColumnIterator]&0x0F),MDIO_PIN_LOW);
            for(u8 RowIterator = 0 ; (RowIterator < HKEYPAD_MAX_ROW_NUM) && (Ret_enuErrorStatus == HKEYPAD_OK) ; RowIterator++)
            {
                u8 Loc_u8RowPinValue;
                Ret_enuErrorStatus = MDIO_enuGetPinValue((HKEYPAD_cfgArr[Copy_u8KeypadNum].HKEYPAD_RowPins[RowIterator]>>4),(HKEYPAD_cfgArr[Copy_u8KeypadNum].HKEYPAD_RowPins[RowIterator]&0x0F),&Loc_u8RowPinValue);
                if(Loc_u8RowPinValue == MDIO_PIN_LOW)
                {
                    /* Delay for debounce effect */
                    _delay_ms(25);
                    Ret_enuErrorStatus = MDIO_enuGetPinValue((HKEYPAD_cfgArr[Copy_u8KeypadNum].HKEYPAD_RowPins[RowIterator]>>4),(HKEYPAD_cfgArr[Copy_u8KeypadNum].HKEYPAD_RowPins[RowIterator]&0x0F),&Loc_u8RowPinValue);
                    if(Loc_u8RowPinValue == MDIO_PIN_LOW)
                    {
                        *Add_u8PressedKey = HKEYPAD_u8CharArr[RowIterator][ColumnIterator];
                        Loc_u8IsKeyPressed = true;
                        break;
                    }
                }
            }
            /* set current column HIGH */
            Ret_enuErrorStatus = MDIO_enuSetPinValue((HKEYPAD_cfgArr[Copy_u8KeypadNum].HKEYPAD_ColumnPins[ColumnIterator]>>4),(HKEYPAD_cfgArr[Copy_u8KeypadNum].HKEYPAD_ColumnPins[ColumnIterator]&0x0F),MDIO_PIN_HIGH);
            if(Loc_u8IsKeyPressed == true)
            {
                break;
            }
        }
    }
    return Ret_enuErrorStatus;
}