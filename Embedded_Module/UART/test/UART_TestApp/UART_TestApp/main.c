/*
 * UART_TestApp.c
 *
 * Created: 4/1/2025 10:16:46 PM
 * Author : Mousa Mahmoud
 */ 

#define F_CPU 8000000UL
#include "STD_TYPES.h"
#include "UART.h"

int main(void)
{
	u8 Loc_u8Buf = 'M';
	
	/* NOT recommended to choose a baudrate with error greater than 2.1%. Refer to data sheet for more info */
	UART_enuInit(F_CPU, 9600);
    while (1) 
    {
		UART_enuReceive(&Loc_u8Buf, 1U);
		UART_enuTransmit(&Loc_u8Buf, 1U);
    }
}

