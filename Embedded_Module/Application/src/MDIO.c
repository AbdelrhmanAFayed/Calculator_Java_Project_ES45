/*
 * MDIO.c
 * Created: 17/12/2024
 * Author : Mariam Hossam
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"

/* struct used for accessing the port,pin,ddr registers*/
typedef struct  
{
	u8 PIN;
	u8 DDR;
	u8 PORT;
}MDIO_strPortReg_t;

/* base address of the portA*/
#define MDIO_PORT_REG_BASE_ADD ((volatile MDIO_strPortReg_t*)(0x39))
/* macro like function used to access the desired register(port,pin,ddr from A to D)*/
#define MDIO_GET_PORT_ADD(PORT_NUM) (MDIO_strPortReg_t *)((MDIO_PORT_REG_BASE_ADD) - (PORT_NUM))


MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum,MDIO_enuPinNum_t Copy_enuPinNum,MDIO_enuPinState_t Copy_enuState)
{
	MDIO_strPortReg_t * Loc_strPortAdd = MDIO_GET_PORT_ADD(Copy_enuPortNum);
	MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_NOK;
	if(Copy_enuPortNum > MDIO_PORTD)
	{
		Ret_enuErrorStatus = MDIO_INVALID_PORT_NUM;
	}
	else if(Copy_enuPinNum > MDIO_PIN7)
	{
		Ret_enuErrorStatus = MDIO_INVALID_PIN_NUM;
	}
	else if(Copy_enuState > MDIO_PIN_HIGH)
	{
		Ret_enuErrorStatus = MDIO_INVALID_PIN_STATE;
	}
	else
	{
		Ret_enuErrorStatus = MDIO_OK;
		if(Copy_enuState == MDIO_PIN_LOW)
		{
			CLR_BIT(Loc_strPortAdd->PORT,Copy_enuPinNum);
		}
		else if(Copy_enuState == MDIO_PIN_HIGH)
		{
			SET_BIT(Loc_strPortAdd->PORT,Copy_enuPinNum);
		}
	}
	return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum , u8 Copy_enuPortState)
{
	MDIO_strPortReg_t * Loc_strPortAdd = MDIO_GET_PORT_ADD(Copy_enuPortNum);
	MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_NOK;
	if(Copy_enuPortNum > MDIO_PORTD)
	{
		Ret_enuErrorStatus = MDIO_INVALID_PORT_NUM;
	}
	else if(Copy_enuPortState > MDIO_PORT_HIGH)
	{
		Ret_enuErrorStatus = MDIO_INVALID_PORT_STATE;
	}
	else
	{
		Ret_enuErrorStatus = MDIO_OK;
		Loc_strPortAdd->PORT = (Copy_enuPortState & Loc_strPortAdd->DDR);
	}		
	return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum,MDIO_enuPinNum_t Copy_enuPinNum,u8* Add_pu8PinValue)
{
	MDIO_strPortReg_t * Loc_strPortAdd = MDIO_GET_PORT_ADD(Copy_enuPortNum);
	MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_NOK;
	if(Copy_enuPortNum > MDIO_PORTD)
	{
		Ret_enuErrorStatus = MDIO_INVALID_PORT_NUM;
	}
	else if(Copy_enuPinNum > MDIO_PIN7)
	{
		Ret_enuErrorStatus = MDIO_INVALID_PIN_NUM;
	}
	else if(Add_pu8PinValue == NULL_PTR)
	{
		Ret_enuErrorStatus = MDIO_NULL_POINTER;
	}
	else
	{
		Ret_enuErrorStatus = MDIO_OK;
		* Add_pu8PinValue = GET_BIT(Loc_strPortAdd->PIN,Copy_enuPinNum);
	}
	return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuGetPortValue(MDIO_enuPortNum_t Copy_enuPortNum,u8* Add_pu8PinValue) 
{
	MDIO_strPortReg_t * Loc_strPortAdd = MDIO_GET_PORT_ADD(Copy_enuPortNum);
	MDIO_enuErrorStatus_t Ret_enuErrorStatus = MDIO_NOK;
	if(Copy_enuPortNum > MDIO_PORTD)
	{
		Ret_enuErrorStatus = MDIO_INVALID_PORT_NUM;
	}
	else if(Add_pu8PinValue == NULL_PTR)
	{
		Ret_enuErrorStatus = MDIO_NULL_POINTER;
	}
	else
	{	
		Ret_enuErrorStatus = MDIO_OK;
		* Add_pu8PinValue = Loc_strPortAdd->PIN;
	}
	return Ret_enuErrorStatus;
}
