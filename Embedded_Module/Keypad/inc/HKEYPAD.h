#ifndef HKEYPAD_H
#define HKEYPAD_H

#include "STD_TYPES.h"
#include "MPORT.h"
#include "MDIO.h"

/**** Enum for Error Status ****/
typedef enum
{
	HKEYPAD_OK = 0,
	HKEYPAD_NOK,
	HKEYPAD_NULL_POINTER,
	HKEYPAD_INVALID_ROW,
	HKEYPAD_INVALID_COLUMN,
	HKEYPAD_INVALID_KEYPAD_NUM
	
} HKEYPAD_enuErrorStatus_t ;

typedef struct
{
    MPORT_enuPORT_PIN_t HKEYPAD_RowPins[4];
	MPORT_enuPORT_PIN_t HKEYPAD_ColumnPins[4];

} HKEYPAD_strCfg_t;

extern HKEYPAD_enuErrorStatus_t HKEYPAD_enuInit(void);
extern HKEYPAD_enuErrorStatus_t HKEYPAD_enuGetPressedKey(u8 * Add_u8PressedKey,u8 Copy_u8KeypadNum);

#endif // HKEYPAD_H