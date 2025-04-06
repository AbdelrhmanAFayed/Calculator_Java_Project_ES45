
#include "STD_TYPES.h"

#include <util/delay.h>
#include "UART.h"
#include "HKEYPAD.h"
#include "HKEYPAD_cfg.h"

int main(void)
{
    u8 Buff = HKEYPAD_NO_KEY_PRESSED;
    u8 last_key = HKEYPAD_NO_KEY_PRESSED;
    
    UART_enuInit(8000000UL, 9600);
    HKEYPAD_enuInit();

    while (1)
    {
        /*Get current pressed key*/
        HKEYPAD_enuGetPressedKey(&Buff, 0);

        if (Buff != last_key)
        {
            UART_enuTransmit(&Buff, sizeof(Buff));
        }
        else { /* Do nothing */ }
        
        last_key = Buff;
        _delay_ms(100);

    }

    return 0 ;
}
