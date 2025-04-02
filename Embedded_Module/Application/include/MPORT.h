/*
 * MPORT.h
 * Created: 03/01/2024
 * Author : Mariam Hossam
 */
 
#ifndef MPORT_H_
#define MPORT_H_

#include "STD_TYPES.h"
#include "MPORT_Cfg.h"

/**** Enum for Error Status ****/
typedef enum
{
	MPORT_OK = 0,
	MPORT_NOK,
	MPORT_INVALID_PIN_NUM,
    MPORT_INVALID_PORT_NUM,
    MPORT_INVALID_PIN_MODE,
    MPORT_INVALID_PIN_DIR,
	MPORT_INVALID_PIN_CFG,
    MPORT_INVALID_PORT_CFG,
	MPORT_NULL_POINTER
	
} MPORT_enuErrorStatus_t ;

/**** Enum for Port Number ****/
typedef enum
{
	MPORT_PORTA = 0,
	MPORT_PORTB,
	MPORT_PORTC,
	MPORT_PORTD
	
} MPORT_enuPortNum_t ;

/**** Enum for Pin Number ****/
typedef enum
{
	MPORT_PIN0 = 0,
	MPORT_PIN1,
	MPORT_PIN2,
	MPORT_PIN3,
	MPORT_PIN4,
	MPORT_PIN5,
	MPORT_PIN6,
	MPORT_PIN7
	
} MPORT_enuPinNum_t ;

/**** Enum for Pin and Port Numbrs Combined ****/
typedef enum
{
    // Pins for PORTA
    MPORT_PINA_0 = (MPORT_PORTA << 4) | MPORT_PIN0,
    MPORT_PINA_1 = (MPORT_PORTA << 4) | MPORT_PIN1,
    MPORT_PINA_2 = (MPORT_PORTA << 4) | MPORT_PIN2,
    MPORT_PINA_3 = (MPORT_PORTA << 4) | MPORT_PIN3,
    MPORT_PINA_4 = (MPORT_PORTA << 4) | MPORT_PIN4,
    MPORT_PINA_5 = (MPORT_PORTA << 4) | MPORT_PIN5,
    MPORT_PINA_6 = (MPORT_PORTA << 4) | MPORT_PIN6,
    MPORT_PINA_7 = (MPORT_PORTA << 4) | MPORT_PIN7,

    // Pins for PORTB
    MPORT_PINB_0 = (MPORT_PORTB << 4) | MPORT_PIN0,
    MPORT_PINB_1 = (MPORT_PORTB << 4) | MPORT_PIN1,
    MPORT_PINB_2 = (MPORT_PORTB << 4) | MPORT_PIN2,
    MPORT_PINB_3 = (MPORT_PORTB << 4) | MPORT_PIN3,
    MPORT_PINB_4 = (MPORT_PORTB << 4) | MPORT_PIN4,
    MPORT_PINB_5 = (MPORT_PORTB << 4) | MPORT_PIN5,
    MPORT_PINB_6 = (MPORT_PORTB << 4) | MPORT_PIN6,
    MPORT_PINB_7 = (MPORT_PORTB << 4) | MPORT_PIN7,

    // Pins for PORTC
    MPORT_PINC_0 = (MPORT_PORTC << 4) | MPORT_PIN0,
    MPORT_PINC_1 = (MPORT_PORTC << 4) | MPORT_PIN1,
    MPORT_PINC_2 = (MPORT_PORTC << 4) | MPORT_PIN2,
    MPORT_PINC_3 = (MPORT_PORTC << 4) | MPORT_PIN3,
    MPORT_PINC_4 = (MPORT_PORTC << 4) | MPORT_PIN4,
    MPORT_PINC_5 = (MPORT_PORTC << 4) | MPORT_PIN5,
    MPORT_PINC_6 = (MPORT_PORTC << 4) | MPORT_PIN6,
    MPORT_PINC_7 = (MPORT_PORTC << 4) | MPORT_PIN7,

    // Pins for PORTD
    MPORT_PIND_0 = (MPORT_PORTD << 4) | MPORT_PIN0,
    MPORT_PIND_1 = (MPORT_PORTD << 4) | MPORT_PIN1,
    MPORT_PIND_2 = (MPORT_PORTD << 4) | MPORT_PIN2,
    MPORT_PIND_3 = (MPORT_PORTD << 4) | MPORT_PIN3,
    MPORT_PIND_4 = (MPORT_PORTD << 4) | MPORT_PIN4,
    MPORT_PIND_5 = (MPORT_PORTD << 4) | MPORT_PIN5,
    MPORT_PIND_6 = (MPORT_PORTD << 4) | MPORT_PIN6,
    MPORT_PIND_7 = (MPORT_PORTD << 4) | MPORT_PIN7

} MPORT_enuPORT_PIN_t;

/**** Enum for Pin Direction ****/
typedef enum
{
	MPORT_INPUT = 0,
	MPORT_OUTPUT
	
} MPORT_enuPinDir_t ;

/**** Enum for Pin Configuration ****/
typedef enum
{
	MPORT_OUTPUT_LOW = 0,
	MPORT_OUTPUT_HIGH,
	MPORT_INTERNAL_PULLUP,
	MPORT_EXTERNAL_PULLDOWN
} MPORT_enuPinCfg_t ;

/**** Enum for Port Configuration ****/
typedef enum
{
	MPORT_OUTPUT_PORT_LOW = 0x00,
	MPORT_OUTPUT_PORT_HIGH = 0xFF,
	MPORT_INTERNAL_PORT_PULLUP,
	MPORT_EXTERNAL_PORT_PULLDOWN
	
} MPORT_enuPortCfg_t ;

/**** Enum for Pin Direction ****/
typedef enum
{
    MPORT_PIN_MODE_INPUT_PULLUP = 0,  /* Input with internal pull-up resistor */
    //MPORT_PIN_MODE_UART

} MPORT_enuPinMode_t ;

/*************************************************************************** APIs *******************************************************************************/

/****************************************************************************************************************************************************************
MPORT_enuErrorStatus_t MPORT_enuSetPinDirection( u8 Copy_enuPinNum  ,  u8  Copy_enuPinDirection  );
Purpose:
The Port_SetPinDirection API is part of the AUTOSAR Port Driver module. it allows you to change the direction of a specific microcontroller pin at runtime. 
Pin direction determines whether the pin:

    Acts as an input  (reads data/signals from external devices).
    Acts as an output (sends data/signals to external devices).

Parameters:

    Copy_enuPinNum:
        Typically defined using a combination of the port and pin numbers (e.g., 0x10 might represent Pin 0 on Port B in an 8-bit architecture).
        Example : #define PIN_A0 0x00 // Port A, Pin 0      ,   #define PIN_C3  0x23 // Port C, Pin 3

    Copy_enuPinDirection:
        Specifies the desired configuration for the pin. Examples:
            OUTPUT,INPUT.

Return:
    MPORT_OK, MPORT_ERROR_INVALID_PIN, MPORT_NOK,MPORT_ERROR_INVALID_DIRECTION.
******************************************************************************************************************************************************************/
MPORT_enuErrorStatus_t MPORT_enuSetPinDirection( MPORT_enuPORT_PIN_t Copy_enuPinNum  ,  MPORT_enuPinDir_t  Copy_enuPinDirection  );

/*****************************************************************************************************************************************************************
MPORT_enuErrorStatus_t MPORT_enuSetPinMode( u8 Copy_enuPinNum  ,  MPORT_enuPinMode_t Copy_enuPinMode );
Purpose :
    The Port_SetPinMode function is part of the AUTOSAR Port Driver module. Its primary purpose is to configure the mode of a specific pin during runtime. 
The mode determines the pin's behavior -> digital communication pin (e.g., UART, SPI), or if it uses internal pull-up or pull-down resistors.


Parmeters:

   Copy_enuPinNum:
        Typically defined using a combination of the port and pin numbers (e.g., 0x10 might represent Pin 0 on Port B in an 8-bit architecture).
        Example : #define PIN_A0 0x00 // Port A, Pin 0      ,   #define PIN_C3  0x23 // Port C, Pin 3

   Copy_enuPinMode:
 
    Specifies the mode to be set for the pin.

    Examples of possible modes (depending on microcontroller configuration):
        PORT_PIN_MODE_INPUT_PULLUP  : Input with internal pull-up resistor.
        PORT_PIN_MODE_INPUT_PULLDOWN: Input with pull-down resistor.
        PORT_PIN_MODE_UART          : UART communication mode.
        .
        .
        .

Return:
    MPORT_OK, MPORT_ERROR_INVALID_PIN , MPORT_NOK , MPORT_ERROR_INVALID_MODE, MPORT_ERROR_UNCHANGEABLE_MODE .
_________________________________________________________________________________________________________________________________________________________________
*****************************************************************************************************************************************************************/
MPORT_enuErrorStatus_t MPORT_enuSetPinMode( MPORT_enuPinNum_t Copy_enuPinNum  ,  MPORT_enuPinMode_t Copy_enuPinMode );

/****************************************************************************************************************************************************************
MPORT_enuErrorStatus_t MPORT_enuSetPinConfigration(Copy_enuPortNum,Copy_enuPinNum,Copy_enuConfigration);
Purpose:
    This API configures a specific pin within a port with the desired functionality, such as input, output,
    or pull-up/down configuration. It allows precise control over individual pins in a microcontroller's GPIO.
Parameters:
    Copy_enuPortNum:
    Specifies the port containing the pin to configure (e.g., PORTA, PORTB, PORTC, etc.).
    Copy_enuPinNum:
    Specifies the pin within the port to configure (e.g., PIN0, PIN1, PIN2, etc.).
    Copy_enuConfigration:
    Specifies the desired configuration for the pin. Examples:
    OUTPUT,INPUT_PULLUP,INPUT_PULLDOWN
Return:
    MPORT_OK, MPORT_INVALID_PARAM, MPORT_NOK
*****************************************************************************************************************************************************************/
MPORT_enuErrorStatus_t MPORT_enuSetPinConfigration(MPORT_enuPortNum_t Copy_enuPortNum,MPORT_enuPinNum_t Copy_enuPinNum,MPORT_enuPinCfg_t Copy_enuConfigration);

/****************************************************************************************************************************************************************
MPORT_enuErrorStatus_t MPORT_enuSetPortConfigration(Copy_enuPortNum,Copy_enuConfigration);
Purpose:
    This API configures all pins in a specific port at once, saving time when multiple pins 
	need the same configuration (e.g., all as inputs or outputs).
Parameters:
    Copy_enuPortNum:
    Specifies the port to configure (e.g., PORTA, PORTB, PORTC, etc.).
Copy_enuConfigration:
    Specifies the configuration to apply to all pins in the port (e.g., all INPUT, all OUTPUT).
Return:
    MPORT_OK, MPORT_INVALID_PARAM, MPORT_NOK
******************************************************************************************************************************************************************/
MPORT_enuErrorStatus_t MPORT_enuSetPortConfigration(MPORT_enuPortNum_t Copy_enuPortNum,MPORT_enuPortCfg_t Copy_enuConfigration);


void MPORT_vInit(void);

#endif //MPORT_H_