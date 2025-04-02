

/*Includes*/


/*Keypad Driver TBD*/
//#include "keypad.h"

#include "STD_TYPES.h"



#include <util/delay.h>
#include "UART.h"
#include "HKEYPAD.h"
#include "HKEYPAD_cfg.h"

//{'7', '8', '9', '/'},   
//{'4', '5', '6', '*'},   
//{'1', '2', '3', '-'},   
//{'C', '0', '=', '+'}  


int main(void)
{
    UART_enuInit(8000000UL, 9600);
    HKEYPAD_enuInit();
   
    u8 Buff = HKEYPAD_NO_KEY_PRESSED;

    
    while (1)
    {
        

        /*Get current pressed key*/
        HKEYPAD_enuGetPressedKey(&Buff, 0);

      
            
        
        UART_enuTransmit(&Buff, sizeof(Buff));
        _delay_ms(100);

      }
    

    return 0 ;
}
