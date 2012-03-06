/*
 * driverGenAdc.h
 *
 *  Created on: Feb 18, 2012
 *      Author: Derek
 */

#ifndef DRIVERGENADC_H_
#define DRIVERGENADC_H_

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_adc.h"
#include "platformConfig.h"

/*------ ADC --------*/
#define AIR_PIN_FUNC    PINSEL_FUNC_1
#define AIR_PORT        PINSEL_PORT_0
#define AIR_PIN         PINSEL_PIN_23
#define USON_PIN_FUNC   PINSEL_FUNC_1
#define USON_PORT       PINSEL_PORT_0
#define USON_PIN		PINSEL_PIN_24

#define ADCAVERAGING 100;


void adcconfig(void);
void adcinterupt(void);

#endif /* DRIVERGENADC_H_ */
