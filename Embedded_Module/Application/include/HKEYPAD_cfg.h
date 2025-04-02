#ifndef HKEYPAD_CFG_H
#define HKEYPAD_CFG_H

typedef enum
{
    KEYPAD_ONE = 0,
    NUMBER_OF_KEYPADS

} HLCD_enuNumberOfKeypad_t;

typedef enum
{
	HKEYPAD_ROW_0 = 0,
	HKEYPAD_ROW_1,
	HKEYPAD_ROW_2,
	HKEYPAD_ROW_3,
    HKEYPAD_MAX_ROW_NUM

} HKEYPAD_enuRowPin_t;

typedef enum
{
	HKEYPAD_Column_0 = 0,
	HKEYPAD_Column_1,
	HKEYPAD_Column_2,
	HKEYPAD_Column_3,
    HKEYPAD_MAX_COLUMN_NUM

} HKEYPAD_enuColumnPin_t;

/* Define the keypad size */
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define HKEYPAD_NO_KEY_PRESSED 'K'

static const u8 HKEYPAD_u8CharArr[KEYPAD_ROWS][KEYPAD_COLS] = 
{
    {'7', '8', '9', '/'},   
    {'4', '5', '6', '*'},   
    {'1', '2', '3', '-'},   
    {'C', '0', '=', '+'}    
};

#endif // HKEYPAD_CFG_H