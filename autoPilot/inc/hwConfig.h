/*
 * hw_config.h
 *
 *  Created on: Feb 7, 2012
 *      Author: jenya
 */

#ifndef HW_CONFIG_H_
#define HW_CONFIG_H_


#include "lpc17xx.h"
#include "platformConfig.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"

        /***************************************************************
         ***************** Command Function Prototypes *****************
         **************************************************************/
/*-------------------------------------------------------------------------------
 * Function Name	: setSystem
 * Description		: This function is ran at the beginning of the code execution
 *                    in order to set up the system
 * ASSUMPTIONS		:
 * Input			: None
 * Output			: Configures the hardware
 * Return			: None
 ------------------------------------------------------------------------------*/
void setSystem(void);

/*-------------------------------------------------------------------------------
 * Function Name	: configRedLed
 * Description		: Configures the red LED (GPIO_3_25) to a known state
 * ASSUMPTIONS		: GPIO line is powered ON
 * Input			: None
 * Output			: Configures the red LED
 * Return			: None
 ------------------------------------------------------------------------------*/
void configRedLed(void);

void configPwm(void);


#endif /* HW_CONFIG_H_ */
