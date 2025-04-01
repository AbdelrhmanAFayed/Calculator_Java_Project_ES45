/*
 * MDIO.h
 * Created: 17/12/2024
 * Author : Mariam Hossam
 */ 

#ifndef MDIO_H_
#define MDIO_H_

#include "STD_TYPES.h"

/**** Enum for Error Status ****/
typedef enum
{
	MDIO_OK = 0,
	MDIO_NOK,
	MDIO_INVALID_PORT_NUM,
	MDIO_INVALID_PIN_NUM,
	MDIO_INVALID_PORT_STATE,
	MDIO_INVALID_PIN_STATE,
	MDIO_NULL_POINTER
	
}MDIO_enuErrorStatus_t ;

/**** Enum for Port Number ****/
typedef enum
{
	MDIO_PORTA = 0,
	MDIO_PORTB,
	MDIO_PORTC,
	MDIO_PORTD
	
}MDIO_enuPortNum_t ;

/**** Enum for Pin Number ****/
typedef enum
{
	MDIO_PIN0 = 0,
	MDIO_PIN1,
	MDIO_PIN2,
	MDIO_PIN3,
	MDIO_PIN4,
	MDIO_PIN5,
	MDIO_PIN6,
	MDIO_PIN7
	
}MDIO_enuPinNum_t ;

/**** Enum for Pin State ****/
typedef enum
{
	MDIO_PIN_LOW = 0,
	MDIO_PIN_HIGH = 1
	
}MDIO_enuPinState_t ;

/**** Enum for Port State ****/
typedef enum
{
	MDIO_PORT_LOW = 0x00,
	MDIO_PORT_HIGH = 0xff
	
}MDIO_enuPortState_t ;

/*************************************************************************** APIs *******************************************************************************/

/*****************************************************************************************************************************************************************
MDIO_enuErrorStatus_t MDIO_enuSetPinValue( Copy_enuPortNum, Copy_enuPinNum, Copy_enuState);
Purpose:
    This API sets the logical state of a specific pin (e.g., HIGH or LOW).
Parameters:
    Copy_enuPortNum:
    Specifies the port containing the pin (e.g., PORTA, PORTB, etc.).
    Copy_enuPinNum:
    Specifies the pin within the port to set (e.g., PIN0, PIN1, PIN2, etc.).
    Copy_enuState:
    Specifies the desired state for the pin: HIGH,LOW
Return:
    MDIO_OK, MDIO_INVALID_PARAM, MDIO_NOK .........
*****************************************************************************************************************************************************************/
MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum,MDIO_enuPinNum_t Copy_enuPinNum,MDIO_enuPinState_t Copy_enuState);

/*****************************************************************************************************************************************************************
MDIO_enuErrorStatus_t MDIO_enuSetPortValue(Copy_enuPortNum,Copy_enuPortState);
Purpose:
    This API sets the logical states of all pins in a specified port at once, which is useful for initializing or modifying the state of a port efficiently.
Parameters:
    Copy_enuPortNum:
    Specifies the port to modify (e.g., PORTA, PORTB, etc.).
Copy_enuPortState:
    Specifies the collective state for all pins in the port (e.g. all HIGH, all LOW).
Return:
    MDIO_OK, MDIO_INVALID_PARAM, MDIO_NOK .........
*******************************************************************************************************************************************************************/
MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum,u8 Copy_enuPortState);

/******************************************************************************************************************************************************************
MDIO_enuErrorStatus_t MDIO_enuGetPinValue(Copy_enuPortNum,Copy_enuPinNum,u8* Add_pu8PinValue);
Purpose:
    This API retrieves the logical state (HIGH or LOW) of a specific pin.
Copy_enuPortNum:
    Specifies the port containing the pin to read (e.g., PORTA, PORTB, etc.).
Copy_enuPinNum:
    Specifies the pin within the port to read (e.g., PIN0, PIN1, PIN2, etc.).
Add_pu8PinValue:
    Pointer to store the retrieved pin value.
Return: 
    MDIO_OK, MDIO_INVALID_PARAM, MDIO_NULL_PTR, MDIO_NOK
*******************************************************************************************************************************************************************/
MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum,MDIO_enuPinNum_t Copy_enuPinNum,u8* Add_pu8PinValue);

/******************************************************************************************************************************************************************
MDIO_enuErrorStatus_t MDIO_enuGetPortValue(Copy_enuPortNum,u8* Add_pu8PinValue);
Purpose:
    This API retrieves the logical state (HIGH or LOW) of a specific port.
Copy_enuPortNum:
    Specifies the port to read (e.g., PORTA, PORTB, etc.).
Add_pu8PinValue:
    Pointer to store the retrieved port value.
Return: 
    MDIO_OK, MDIO_INVALID_PARAM, MDIO_NULL_PTR, MDIO_NOK
*******************************************************************************************************************************************************************/
MDIO_enuErrorStatus_t MDIO_enuGetPortValue(MDIO_enuPortNum_t Copy_enuPortNum,u8* Add_pu8PinValue) ;

#endif /* MDIO_H_ */

