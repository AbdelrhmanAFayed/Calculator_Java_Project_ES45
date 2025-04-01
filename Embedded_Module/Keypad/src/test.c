/* This Application is testing the Keypad driver using LCD  */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"
#include "MPORT.h"
#include "HKEYPAD.h"
#include "HKEYPAD_cfg.h"
#include "HLCD.h"
#include "HLCD_cfg.h"

void Clear_LCD(void);

//     {'7', '8', '9', '/'},   
//     {'4', '5', '6', '*'},   
//     {'1', '2', '3', '-'},   
//     {'C', '0', '=', '+'}    

int main(void)
{
	HLCD_enuInit();
    HKEYPAD_enuInit();
	u8 KeyValue = HKEYPAD_NO_KEY_PRESSED;
	while(1) 
    {
		HKEYPAD_enuGetPressedKey(&KeyValue,KEYPAD_ONE);
		if(KeyValue != HKEYPAD_NO_KEY_PRESSED)
		{
			if(KeyValue == 'C')
			{
				Clear_LCD();		
			}
			else
			{
				HLCD_enuWriteData(KeyValue,LCD_ONE);
			}
		}
	}
	return 0;
}

void Clear_LCD(void)
{
	HLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
}
