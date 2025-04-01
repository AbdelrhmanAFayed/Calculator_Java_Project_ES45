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
		switch(KeyValue)
		{
			case '0':
				HLCD_enuWriteNumber(0,LCD_ONE);
			break;
			case '1':
				HLCD_enuWriteNumber(1,LCD_ONE);
			break;
			case '2':
				HLCD_enuWriteNumber(2,LCD_ONE);
			break;
			case '3':
				HLCD_enuWriteNumber(3,LCD_ONE);
			break;
			case '4':
				HLCD_enuWriteNumber(4,LCD_ONE);
			break;
			case '5':
				HLCD_enuWriteNumber(5,LCD_ONE);
			break;
			case '6':
				HLCD_enuWriteNumber(6,LCD_ONE);
			break;
			case '7':
				HLCD_enuWriteNumber(7,LCD_ONE);
			break;
			case '8':
				HLCD_enuWriteNumber(8,LCD_ONE);
			break;
			case '9':
				HLCD_enuWriteNumber(9,LCD_ONE);
			break;
			case 'C':
				Clear_LCD();
			break;
			case '+':
				HLCD_enuWriteData('+',LCD_ONE);
			break;
			case '-':
				HLCD_enuWriteData('-',LCD_ONE);
			break;
			case '*':
				HLCD_enuWriteData('*',LCD_ONE);
			break;
			case '/':
				HLCD_enuWriteData('/',LCD_ONE);
			break;
			case '=':
				HLCD_enuWriteData('=',LCD_ONE);
			break;
			default :
				/* Do Nothing */
			break;	
		}
	}
	return 0;
}

void Clear_LCD(void)
{
	HLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
}
