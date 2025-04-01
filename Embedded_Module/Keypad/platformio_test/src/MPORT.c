/*
 * MPORT.c
 * Created: 03/01/2024
 * Author : Mariam Hossam
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MPORT.h"

extern MPORT_enuPinCfg_t MPORT_enuPinCfgArray[MPORT_NUM_OF_PORTS * MPORT_NUM_OF_PINS];

typedef struct  
{
	u8 PIN;
	u8 DDR;
	u8 PORT;
}MPORT_strPortReg_t;

#define MPORT_PORT_REG_BASE_ADD ((volatile MPORT_strPortReg_t*)(0x39))

#define MPORT_GET_PORT_ADD(PORT_NUM) (MPORT_strPortReg_t *)((MPORT_strPortReg_t *)(MPORT_PORT_REG_BASE_ADD) - (PORT_NUM))

MPORT_enuErrorStatus_t MPORT_enuSetPinConfigration(MPORT_enuPortNum_t Copy_enuPortNum,MPORT_enuPinNum_t Copy_enuPinNum,MPORT_enuPinCfg_t Copy_enuConfigration)
{
	MPORT_strPortReg_t * Loc_strPortAdd = MPORT_GET_PORT_ADD(Copy_enuPortNum);
	MPORT_enuErrorStatus_t Ret_enuErrorStatus = MPORT_NOK;
	if(Copy_enuPortNum > MPORT_PORTD)
	{	
		Ret_enuErrorStatus = MPORT_INVALID_PORT_NUM;
	}
	else if(Copy_enuPinNum > MPORT_PIN7)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PIN_NUM;
	}
	else if(Copy_enuConfigration > MPORT_EXTERNAL_PULLDOWN)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PIN_CFG;
	}
	else
	{
		Ret_enuErrorStatus = MPORT_OK;
		if(Copy_enuConfigration == MPORT_OUTPUT_LOW)
		{
			SET_BIT(Loc_strPortAdd->DDR,Copy_enuPinNum);
			CLR_BIT(Loc_strPortAdd->PORT,Copy_enuPinNum);
		}
		else if(Copy_enuConfigration == MPORT_OUTPUT_HIGH)
		{
			SET_BIT(Loc_strPortAdd->DDR,Copy_enuPinNum);
			SET_BIT(Loc_strPortAdd->PORT,Copy_enuPinNum);
		}
		else if(Copy_enuConfigration == MPORT_INTERNAL_PULLUP)
		{
			CLR_BIT(Loc_strPortAdd->DDR,Copy_enuPinNum);
			SET_BIT(Loc_strPortAdd->PORT,Copy_enuPinNum);
		}
		else
		{
			/* Do Nothing */
		}
	}
	return Ret_enuErrorStatus;	
}

MPORT_enuErrorStatus_t MPORT_enuSetPortConfigration(MPORT_enuPortNum_t Copy_enuPortNum,MPORT_enuPortCfg_t Copy_enuConfigration)
{
	MPORT_strPortReg_t * Loc_strPortAdd = MPORT_GET_PORT_ADD(Copy_enuPortNum);
	MPORT_enuErrorStatus_t Ret_enuErrorStatus = MPORT_NOK;
	if(Copy_enuPortNum > MPORT_PORTD)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PORT_NUM;
	}
	else if(Copy_enuConfigration > MPORT_EXTERNAL_PORT_PULLDOWN)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PORT_CFG;
	}
	else
	{
		Ret_enuErrorStatus = MPORT_OK;
		if(Copy_enuConfigration == MPORT_OUTPUT_PORT_LOW)
		{
			Loc_strPortAdd->DDR = MPORT_OUTPUT_PORT_HIGH;
			Loc_strPortAdd->PORT = MPORT_OUTPUT_PORT_LOW;
		}
		else if(Copy_enuConfigration == MPORT_OUTPUT_PORT_HIGH)
		{
			Loc_strPortAdd->DDR = MPORT_OUTPUT_PORT_HIGH;
			Loc_strPortAdd->PORT = MPORT_OUTPUT_PORT_HIGH;
		}
		else if(Copy_enuConfigration == MPORT_INTERNAL_PORT_PULLUP)
		{
			Loc_strPortAdd->DDR = MPORT_OUTPUT_PORT_LOW;
			Loc_strPortAdd->PORT = MPORT_OUTPUT_PORT_HIGH;
		}
		else if(Copy_enuConfigration == MPORT_EXTERNAL_PORT_PULLDOWN)
		{
			Loc_strPortAdd->DDR = MPORT_OUTPUT_PORT_LOW;
			Loc_strPortAdd->PORT = MPORT_OUTPUT_PORT_LOW;
		}
	}
	return Ret_enuErrorStatus;		
}

MPORT_enuErrorStatus_t MPORT_enuSetPinDirection( MPORT_enuPORT_PIN_t Copy_enuPinNum  ,  MPORT_enuPinDir_t  Copy_enuPinDirection  )
{
	MPORT_enuPortNum_t Loc_enuPortNum = GET_HIGH_NIB(Copy_enuPinNum);
	MPORT_enuPinNum_t Loc_enuPinNum = GET_LOW_NIB(Copy_enuPinNum);
    MPORT_strPortReg_t * Loc_strPortAdd = MPORT_GET_PORT_ADD(Loc_enuPortNum);
	MPORT_enuErrorStatus_t Ret_enuErrorStatus = MPORT_NOK;
	if(Loc_enuPortNum > MPORT_PORTD)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PORT_NUM;
	}
	else if(Loc_enuPinNum > MPORT_PIN7)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PIN_NUM;
	}
	else if(Copy_enuPinDirection > MPORT_OUTPUT)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PIN_DIR;
	}
	else
	{
		Ret_enuErrorStatus = MPORT_OK;
		switch(Copy_enuPinDirection)
		{
			case MPORT_INPUT :
				CLR_BIT(Loc_strPortAdd->DDR,Loc_enuPinNum);
			break;
			case MPORT_OUTPUT :
            	SET_BIT(Loc_strPortAdd->DDR,Loc_enuPinNum);
			break;
		}
	}
	return Ret_enuErrorStatus;		
}

MPORT_enuErrorStatus_t MPORT_enuSetPinMode( MPORT_enuPinNum_t Copy_enuPinNum  ,  MPORT_enuPinMode_t Copy_enuPinMode )
{
    MPORT_enuPortNum_t Loc_enuPortNum = GET_HIGH_NIB(Copy_enuPinNum);
	MPORT_enuPinNum_t Loc_enuPinNum = GET_LOW_NIB(Copy_enuPinNum);
    MPORT_strPortReg_t * Loc_strPortAdd = MPORT_GET_PORT_ADD(Loc_enuPortNum);
	MPORT_enuErrorStatus_t Ret_enuErrorStatus = MPORT_NOK;
	if(Loc_enuPortNum > MPORT_PORTD)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PORT_NUM;
	}
	else if(Loc_enuPinNum > MPORT_PIN7)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PIN_NUM;
	}
	else if(Copy_enuPinMode > MPORT_PIN_MODE_INPUT_PULLUP)
	{
		Ret_enuErrorStatus = MPORT_INVALID_PIN_MODE;
	}
	else
	{
		Ret_enuErrorStatus = MPORT_OK;
		switch(Copy_enuPinMode)
		{
			case MPORT_PIN_MODE_INPUT_PULLUP :
				CLR_BIT(Loc_strPortAdd->DDR,Loc_enuPinNum);
				SET_BIT(Loc_strPortAdd->PORT,Loc_enuPinNum);
			break;
		}
	}
	return Ret_enuErrorStatus;
}
void MPORT_vInit(void)
{
	MPORT_enuPortNum_t Loc_enuCurrentPort = MPORT_PORTA;
	MPORT_enuPinNum_t Loc_enuCurrentPin = MPORT_PIN0;
	for(u8 itration = 0 ; itration < (MPORT_NUM_OF_PORTS * MPORT_NUM_OF_PINS) ; itration++)
	{
		Loc_enuCurrentPort = itration / MPORT_NUM_OF_PINS;
		Loc_enuCurrentPin = itration % MPORT_NUM_OF_PINS;
		MPORT_enuSetPinConfigration(Loc_enuCurrentPort,Loc_enuCurrentPin,MPORT_enuPinCfgArray[itration]);
	}
	
}

