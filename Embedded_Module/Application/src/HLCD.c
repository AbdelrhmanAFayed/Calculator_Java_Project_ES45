#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"
#include "MPORT.h"
#include "HLCD.h"
#include "HLCD_cfg.h"
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>

extern HLCD_strCfg_t HLCD_cfgArr[NUMBER_OF_LCD];

static HLCD_enuErrorStatus_t HLCD_enuGoToCGRAM(u8 Copy_BatternNum,u8 Copy_u8LCDNum); // to store chars

HLCD_enuErrorStatus_t HLCD_enuInit(void)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    for(u8 iterator = 0; iterator < NUMBER_OF_LCD ; iterator++)
    {
        for(u8 DataPinsIterator = 0 ;DataPinsIterator < 8 ; DataPinsIterator++ )
        {
            if(HLCD_cfgArr[iterator].HLCD_Mode == HLCD_4_BIT_MODE)
            {
                MPORT_enuSetPinDirection(HLCD_cfgArr[iterator].HLCD_DataPins[DataPinsIterator+4],MPORT_OUTPUT);
            }
            else
            {
                MPORT_enuSetPinDirection(HLCD_cfgArr[iterator].HLCD_DataPins[DataPinsIterator],MPORT_OUTPUT);
            }
        }
        for(u8 PowerPinsIterator = 0;PowerPinsIterator < 3; PowerPinsIterator++ )
        {
             MPORT_enuSetPinDirection(HLCD_cfgArr[iterator].HLCD_PowerPins[PowerPinsIterator],MPORT_OUTPUT);
        }
        _delay_ms(30);
        if(HLCD_cfgArr[iterator].HLCD_Mode == HLCD_4_BIT_MODE)
        {
            HLCD_enuWriteCommand(FUNCTION_SET_4BIT_2_LINES_5x8,iterator);
        }
        else if(HLCD_cfgArr[iterator].HLCD_Mode == HLCD_8_BIT_MODE)
        {
            HLCD_enuWriteCommand(FUNCTION_SET_8BIT_2_LINES_5x8,iterator);
        }
        _delay_ms(1);
        HLCD_enuWriteCommand(DISPLAY_ON_CURSOR_BLINK,iterator);
        _delay_ms(1);
        HLCD_enuWriteCommand(CLEAR_DISPLAY,iterator);
        _delay_ms(2);
        HLCD_enuWriteCommand(DISABLE_AUTO_SHIFT,iterator);
        _delay_ms(2);
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteData(u8 Copy_u8Data,u8 Copy_u8LCDNum)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    MPORT_enuPortNum_t Loc_enuRSPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_RS_PIN]);
    MPORT_enuPinNum_t Loc_enuRSPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_RS_PIN]);
    MPORT_enuPortNum_t Loc_enuRWPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_RW_PIN]);
    MPORT_enuPinNum_t Loc_enuRWPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_RW_PIN]);
    MPORT_enuPortNum_t Loc_enuENPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_EN_PIN]);
    MPORT_enuPinNum_t Loc_enuENPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_EN_PIN]);
    MDIO_enuSetPinValue(Loc_enuRSPort,Loc_enuRSPin,MDIO_PIN_HIGH);
    MDIO_enuSetPinValue(Loc_enuRWPort,Loc_enuRWPin,MDIO_PIN_LOW);
    MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_LOW);
    if(HLCD_cfgArr[Copy_u8LCDNum].HLCD_Mode == HLCD_8_BIT_MODE)
    {
        for(u8 iterator = 0 ; iterator < HLCD_8_BIT_MODE ; iterator++)
        {
            MPORT_enuPortNum_t Loc_enuPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator]);
            MPORT_enuPinNum_t Loc_enuPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator]);
            MDIO_enuSetPinValue(Loc_enuPort,Loc_enuPin,(Copy_u8Data>>iterator)&1);
        }
    }
    else if(HLCD_cfgArr[Copy_u8LCDNum].HLCD_Mode == HLCD_4_BIT_MODE)
    {
        for(u8 iterator = 0 ; iterator < HLCD_4_BIT_MODE ; iterator++)
        {
            MPORT_enuPortNum_t Loc_enuPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator+4]);
            MPORT_enuPinNum_t Loc_enuPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator+4]);
            MDIO_enuSetPinValue(Loc_enuPort,Loc_enuPin,(Copy_u8Data>>(iterator+4))&1);
        }
        MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_HIGH);
        _delay_ms(2);
        MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_LOW);
        for(u8 iterator = 0 ; iterator < HLCD_4_BIT_MODE ; iterator++)
        {
            MPORT_enuPortNum_t Loc_enuPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator+4]);
            MPORT_enuPinNum_t Loc_enuPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator+4]);
            MDIO_enuSetPinValue(Loc_enuPort,Loc_enuPin,(Copy_u8Data>>iterator)&1);
        }
    }
    else
    {
        Loc_enuErrorStatus = HLCD_INVALID_MODE;
    }
    MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_HIGH);
    _delay_ms(2);
    MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_LOW);
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteCommand(u8 Copy_u8Command, u8 Copy_u8LCDNum)
{
    HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    MPORT_enuPortNum_t Loc_enuRSPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_RS_PIN]);
    MPORT_enuPinNum_t Loc_enuRSPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_RS_PIN]);
    MPORT_enuPortNum_t Loc_enuRWPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_RW_PIN]);
    MPORT_enuPinNum_t Loc_enuRWPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_RW_PIN]);
    MPORT_enuPortNum_t Loc_enuENPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_EN_PIN]);
    MPORT_enuPinNum_t Loc_enuENPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_PowerPins[HLCD_EN_PIN]);
    MDIO_enuSetPinValue(Loc_enuRSPort,Loc_enuRSPin,MDIO_PIN_LOW);
    MDIO_enuSetPinValue(Loc_enuRWPort,Loc_enuRWPin,MDIO_PIN_LOW);
    MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_LOW);
    if(HLCD_cfgArr[Copy_u8LCDNum].HLCD_Mode == HLCD_8_BIT_MODE)
    {
        for(u8 iterator = 0 ; iterator < HLCD_8_BIT_MODE ; iterator++)
        {
            MPORT_enuPortNum_t Loc_enuPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator]);
            MPORT_enuPinNum_t Loc_enuPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator]);
            MDIO_enuSetPinValue(Loc_enuPort,Loc_enuPin,(Copy_u8Command>>iterator)&1);
        }
    }
    else if(HLCD_cfgArr[Copy_u8LCDNum].HLCD_Mode == HLCD_4_BIT_MODE)
    {
        for(u8 iterator = 0 ; iterator < HLCD_4_BIT_MODE ; iterator++)
        {
            MPORT_enuPortNum_t Loc_enuPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator+4]);
            MPORT_enuPinNum_t Loc_enuPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator+4]);
            MDIO_enuSetPinValue(Loc_enuPort,Loc_enuPin,(Copy_u8Command>>(iterator+4))&1);
        }
        MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_HIGH);
        _delay_ms(2);
        MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_LOW);
        for(u8 iterator = 0 ; iterator < HLCD_4_BIT_MODE ; iterator++)
        {
            MPORT_enuPortNum_t Loc_enuPort = GET_HIGH_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator+4]);
            MPORT_enuPinNum_t Loc_enuPin = GET_LOW_NIB(HLCD_cfgArr[Copy_u8LCDNum].HLCD_DataPins[iterator+4]);
            MDIO_enuSetPinValue(Loc_enuPort,Loc_enuPin,(Copy_u8Command>>iterator)&1);
        }
    }
    else
    {
        Loc_enuErrorStatus = HLCD_INVALID_MODE;
    }
    MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_HIGH);
    _delay_ms(2);
    MDIO_enuSetPinValue(Loc_enuENPort,Loc_enuENPin,MDIO_PIN_LOW);
    return Loc_enuErrorStatus;
}

static HLCD_enuErrorStatus_t HLCD_enuGoToCGRAM(u8 Copy_BatternNum,u8 Copy_u8LCDNum)
{
	HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    u8 Loc_u8Location = 64;
    if((Copy_BatternNum > 7) || (Copy_BatternNum < 0))
    {
        Loc_enuErrorStatus = HLCD_INVALID_COLUMN;
    }
    else
    {
        Loc_u8Location += (8 * Copy_BatternNum);
        HLCD_enuWriteCommand(Loc_u8Location,Copy_u8LCDNum);
        
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuGoToRowColumn(HLCD_Row_t Copy_enuRow, u8 Copy_enuColumn,u8 Copy_u8LCDNum)
{
	HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    u8 Loc_u8Location = 128;
    if((Copy_enuColumn > 39) || (Copy_enuColumn < 0))
    {
        Loc_enuErrorStatus = HLCD_INVALID_COLUMN;
    }
    else if(Copy_enuRow == HLCD_FIRST_LINE)
    {
        Loc_u8Location += Copy_enuColumn;
        HLCD_enuWriteCommand(Loc_u8Location,Copy_u8LCDNum);
    }
    else if(Copy_enuRow == HLCD_SECOND_LINE)
    {
        Loc_u8Location += Copy_enuColumn + 0x40;
        HLCD_enuWriteCommand(Loc_u8Location,Copy_u8LCDNum);
    }
    else
    {
        Loc_enuErrorStatus = HLCD_INVALID_LINE;
    }
    return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuStoreSpecialChar(u8 * Copy_u8BatternArr,u8 Copy_BatternNum,u8 Copy_u8LCDNum )
{
	HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    if(NULL_PTR == Copy_u8BatternArr)
    {
        Loc_enuErrorStatus = HLCD_NULL_POINTER;
    }
    else if((Copy_BatternNum > 7) || (Copy_BatternNum < 0 ))
    {
        Loc_enuErrorStatus = HLCD_INVALID_BATTERN_NUMBER;
    }
    else
    {
        HLCD_enuGoToCGRAM(Copy_BatternNum,Copy_u8LCDNum);
        for(u8 itr = 0 ; itr < 8 ; itr++)
        {
            HLCD_enuWriteData(Copy_u8BatternArr[itr],Copy_u8LCDNum);
        }
        HLCD_enuGoToRowColumn(HLCD_FIRST_LINE,0,Copy_u8LCDNum);
    }
	return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuDisplaySpecialChar(u8 Copy_BatternNum,HLCD_Row_t Copy_enuRow, u8 Copy_enuColumn,u8 Copy_u8LCDNum)
{
	HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    if((Copy_BatternNum > 7) || (Copy_BatternNum < 0))
    {
        Loc_enuErrorStatus = HLCD_INVALID_BATTERN_NUMBER;
    }
    else if(Copy_enuRow > HLCD_SECOND_LINE)
    {
        Loc_enuErrorStatus = HLCD_INVALID_LINE;
    }
    else if((Copy_enuColumn > 40) || (Copy_enuColumn < 0))
    {
        Loc_enuErrorStatus = HLCD_INVALID_COLUMN;
    }
    else
    {
        HLCD_enuGoToRowColumn(Copy_enuRow,Copy_enuColumn,Copy_u8LCDNum);
        HLCD_enuWriteData(Copy_BatternNum,Copy_u8LCDNum);
    }
	return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteString(u8 * Add_String,u8 Copy_u8LCDNum)
{
	HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    while(*Add_String != '\0')
    {
        Loc_enuErrorStatus = HLCD_enuWriteData(*Add_String++,Copy_u8LCDNum);
    }
	return Loc_enuErrorStatus;
}

HLCD_enuErrorStatus_t HLCD_enuWriteNumber(s64 Copy_Number,u8 Copy_u8LCDNum)
{
	HLCD_enuErrorStatus_t Loc_enuErrorStatus = HLCD_OK;
    s64 Loc_u16Number = 1;
    if(Copy_Number == 0)
    {
         HLCD_enuWriteData('0',Copy_u8LCDNum);
    }
    else
    {
        if(Copy_Number < 0)
        {
            HLCD_enuWriteData('-',Copy_u8LCDNum);
            Copy_Number *= -1;
        }
        while(Copy_Number)                     /* to invert the number before sending */
        {
            Loc_u16Number = (Copy_Number%10) + (Loc_u16Number*10) ;
            Copy_Number /= 10;    
        }
        while(Loc_u16Number != 1)
        {
            HLCD_enuWriteData((Loc_u16Number%10)+'0',Copy_u8LCDNum);
            Loc_u16Number /= 10;
        }
    }
	return Loc_enuErrorStatus;
} 