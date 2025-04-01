/*
 * MPORT_CFG.c
 * Created: 24/12/2024
 *  Author: Mariam
 */ 
 
#include "MPORT_Cfg.h"
#include "MPORT.h"

MPORT_enuPinCfg_t MPORT_enuPinCfgArray[MPORT_NUM_OF_PORTS * MPORT_NUM_OF_PINS] =
{
	// PORTA Configuration
	MPORT_OUTPUT_LOW,
	MPORT_OUTPUT_HIGH,
	0,
	0,
	0,
	0,
	0,
	0,
	// PORTB Configuration
	MPORT_OUTPUT_LOW,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	// PORTC Configuration
	MPORT_OUTPUT_LOW,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	// PORTD Configuration
	0,
	0,
	0,
	MPORT_INTERNAL_PULLUP,
	MPORT_INTERNAL_PULLUP,
	MPORT_INTERNAL_PULLUP,
	0,
	0
};
 