/**
 * @file UART.c
 * @author Mousa Mahmoud (mosa.mahmoud87@gmail.com@)
 * @brief UART(Universal Synchronous Receiver Transmitter) Peripheral driver's source code
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART.h"

/**
 * @brief Registers definition
 * 
 */

#define UBRRH           *((volatile u8 *)0x40)

#define UCSRC           (UBRRH)
#define URSEL           (7U)
#define UCSZ1           (2U)
#define UCSZ0           (1U)

#define UDR             *((volatile u8 *)0x2C)

#define UCSRA           *((volatile u8 *)0x2B)
#define RXC             (7U)
#define UDRE            (5U)

#define UCSRB           *((volatile u8 *)0x2A)
#define RXEN            (4U)
#define TXEN            (3U)

#define UBRRL           *((volatile u8 *)0x29)

/**
 * @brief Public functions
 * 
 */

/**
 * @brief Initialize the UART Module
 * 
 * @param[in] Copy_u32Baudrate Transmitting and receiving baudrate(bits/s)
 * @return UART_enuErrStatus_t Error status of the function return
 */
UART_enuErrStatus_t UART_enuInit(u32 Copy_u32SysClk, u32 Copy_u32Baudrate)
{
    UART_enuErrStatus_t Ret_enuErrorStatus = UART_enuERRSTATUS_NOK;

    if (Copy_u32SysClk > 16000000UL || Copy_u32SysClk < 1000000UL)
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_INVALID_SYSCLK;
    }
    else if (Copy_u32Baudrate > 2000000UL || Copy_u32Baudrate < 2400UL)
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_INVALID_BAUDRATE;
    }
    else
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_OK;

        u32 UBRR = Copy_u32SysClk / 16UL / Copy_u32Baudrate - 1UL;
        UBRRH = (u8)(UBRR >> 8);
        UBRRL = (u8)(UBRR);
        /* Enable: Transmission and Reception */
        UCSRB |= (1U << TXEN) | (1U << RXEN);
        /* Operation Mode: Asynchronous, Parity: None, Stop Bit: 1-bit */
        
        /* Character size: 8-bit */
        UCSRC |= (1U << URSEL) | (1U << UCSZ1) | (1U << UCSZ0);
    }
    
    return Ret_enuErrorStatus;
}

/**
 * @brief Transmit a buffer of data synchronously
 * 
 * @param[in] Copy_pu8Data Pointer to the buffer to be transmitted
 * @param[in] Copy_u16Size Size of the buffer
 * @return UART_enuErrStatus_t Error status of the function return
 */
UART_enuErrStatus_t UART_enuTransmit(const u8 *Copy_pu8Data, u16 Copy_u16Size)
{
    UART_enuErrStatus_t Ret_enuErrorStatus = UART_enuERRSTATUS_NOK;
    u16 Loc_u16Counter = 0;

    if (NULL == Copy_pu8Data)
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_NULL_PTR;
    }
    else if (Copy_u16Size == 0U)
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_INVALID_SIZE;
    }
    else
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_OK;

        for (Loc_u16Counter = 0; Loc_u16Counter < Copy_u16Size; Loc_u16Counter++) {
            /* Wait until the transmit buffer is empty */
            while (!(UCSRA & (1 << UDRE)));
            UDR = *Copy_pu8Data;
            Copy_pu8Data++;
        }
    }
    
    return Ret_enuErrorStatus;
}

/**
 * @brief Receive a buffer of data synchronously
 * 
 * @param[out] Copy_pu8Data Pointer to the buffer to be received
 * @param[in] Copy_u16Size Size of the buffer
 * @return UART_enuErrStatus_t Error status of the function return
 */
UART_enuErrStatus_t UART_enuReceive(u8* const Copy_pu8Data, u16 Copy_u16Size)
{
    UART_enuErrStatus_t Ret_enuErrorStatus = UART_enuERRSTATUS_NOK;
    u16 Loc_u16Counter = 0;

    if (NULL == Copy_pu8Data)
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_NULL_PTR;
    }
    else if (Copy_u16Size == 0U)
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_INVALID_SIZE;
    }
    else
    {
        Ret_enuErrorStatus = UART_enuERRSTATUS_OK;

        for (Loc_u16Counter = 0; Loc_u16Counter < Copy_u16Size; Loc_u16Counter++)
        {
            /* Wait for data to be received */
            while (!(UCSRA & (1U << RXC)));
            Copy_pu8Data[Loc_u16Counter] = UDR;
        } 
    }
    
    return Ret_enuErrorStatus;
}
