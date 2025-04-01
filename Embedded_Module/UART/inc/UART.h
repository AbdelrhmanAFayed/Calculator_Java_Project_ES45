/**
 * @file UART.h
 * @author Mousa Mahmoud (mosa.mahmoud87@gmail.com@)
 * @brief UART(Universal Synchronous Receiver Transmitter) function prototypes with user needed macros for configuration
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

typedef enum _UART_enuErrStatus
{
    UART_enuERRSTATUS_OK = 0,
    UART_enuERRSTATUS_NOK,
    UART_enuERRSTATUS_NULL_PTR,
    UART_enuERRSTATUS_TIMEOUT,
    UART_enuERRSTATUS_INVALID_SYSCLK,
    UART_enuERRSTATUS_INVALID_BAUDRATE,
    UART_enuERRSTATUS_INVALID_SIZE,
} UART_enuErrStatus_t;

/**
 * @brief Initialize the UART Module
 * 
 * @param[in] Copy_u32Baudrate Transmitting and receiving baudrate(bits/s)
 * @return UART_enuErrStatus_t Error status of the function return
 */
UART_enuErrStatus_t UART_enuInit(u32 Copy_u32SysClk, u32 Copy_u32Baudrate);

/**
 * @brief Transmit a buffer of data synchronously
 * 
 * @param[in] Copy_pu8Data Pointer to the buffer to be transmitted
 * @param[in] Copy_u16Size Size of the buffer
 * @return UART_enuErrStatus_t Error status of the function return
 */
UART_enuErrStatus_t UART_enuTransmit(const u8 *Copy_pu8Data, u16 Copy_u16Size);

/**
 * @brief Receive a buffer of data synchronously
 * 
 * @param[out] Copy_pu8Data Pointer to the buffer to be received
 * @param[in] Copy_u16Size Size of the buffer
 * @return UART_enuErrStatus_t Error status of the function return
 */
UART_enuErrStatus_t UART_enuReceive(u8* const Copy_pu8Data, u16 Copy_u16Size);
