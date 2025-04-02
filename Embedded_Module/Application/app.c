

/*Includes*/

/*UART Driver TBD*/
//#include "uart.h"

/*Keypad Driver TBD*/
//#include "keypad.h"

/*Delay implemntation*/
//#include "delay.h"

int main(void)
{
    /*Init for UART*/
    //UART_Init();
    /*Init for Keypad*/
    //KEYPAD_Init();

    /*Declare var to store current key and last key pressed*/

    //u8 current_key = No_Key;
    //u8 last_key =  No_Key;
    //u16 counter = 0 ;

    /*Store data to be sent*/
    //u8 data 
    
    while (1)
    {
        /*Get current pressed key*/

        /*Take action depend on key pressed*/
        /*if(current key == last key)
        {
            counter++; 
            
        }else
        {
            last key = current key;
            counter = 0 ;
            
        }*/
            
        /*if(counter > 100)
        {
            Alternative key to be sent if a function is pressed long enough 
            example: Clear_key
            data = Clear_key;
        }
        else
        {
            data = current key;
        }*/
        /*Send data to UART*/
        //UART_SendData(data);    
        


        /*Delay between each key send to PC*/
        //Delay_ms(100);
    }
    

    return 0 ;
}
