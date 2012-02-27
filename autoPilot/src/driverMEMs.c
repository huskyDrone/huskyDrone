/*
 * driverMEMs.c
 *
 *  Created on: Feb 18, 2012
 *      Author: Trevor
 */


#include "driverMEMs.h"
#define LSM303DLH_ADDRESS 0x69 //todo correct?

#define I20_CLK 400000

__IO FlagStatus complete_M;
int int_status = 0;
void I2C0_IRQHandler(void);

void mems_Init(void)
{
	EXTI_InitTypeDef EXTICfg;
	PINSEL_CFG_Type PinCfg;

	// Setup I2C
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Funcnum = 1;
	PinCfg.Pinnum = 27;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 28;
	PINSEL_ConfigPin(&PinCfg);

	// Initialize Master I2C peripheral
	I2C_Init(LPC_I2C0, I20_CLK);

	// Setup I2C0 Interrupt
	NVIC_DisableIRQ(I2C0_IRQn);
	NVIC_SetPriority(I2C0_IRQn, 5);

	// Enable Master I2C operation
	I2C_Cmd(LPC_I2C0, ENABLE);

	// Force complete flag for the first time of running
	complete_M =  RESET;

	/* 3D Accelerometer and Magnetometer */

	//todo

	/* 3D Gyros */
	// Setup External Interrupt Pin for L3G4200D
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 13;
	PinCfg.Portnum = 2;
	PINSEL_ConfigPin(&PinCfg);
	/* Initialize External 0 interrupt */
	EXTI_Init();
	EXTICfg.EXTI_Line = EXTI_EINT3;
	/* edge sensitive */
	EXTICfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	EXTICfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;
	EXTI_Config(&EXTICfg);

	NVIC_DisableIRQ(EINT3_IRQn);
	NVIC_SetPriority(EINT3_IRQn,6);
	NVIC_EnableIRQ(EINT3_IRQn);
	L3G4200D_Init();
	int_status = L3G4200D_GetStatus(); //todo dev only
}

void I2C0_IRQHandler(void)
{
	I2C_MasterHandler(LPC_I2C0);
	if (I2C_MasterTransferComplete(LPC_I2C0)){
		complete_M = SET;
	}
}
void EINT3_IRQHandler(void)
{
	int_status = L3G4200D_ClearInt();
	EXTI_ClearEXTIFlag(EXTI_EINT3);
}
