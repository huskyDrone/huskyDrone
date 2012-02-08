/*
 * hw_config.h
 *
 *  Created on: Feb 7, 2012
 *      Author: jenya
 */

#ifndef HW_CONFIG_H_
#define HW_CONFIG_H_

/* Bit definitions. */
#define PCONP_PCGPIO    0x00008000
#define PLLFEED_FEED1   0x000000AA
#define PLLFEED_FEED2   0x00000055

#define RED_LED ( 1UL << 25UL )


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


#endif /* HW_CONFIG_H_ */
