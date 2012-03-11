/*
 * driverGenAdc.h
 *
 *  Created on: Feb 18, 2012
 *      Author: Derek
 */

#ifndef DRIVERGENADC_H_
#define DRIVERGENADC_H_

#include "lpc17xx_pinsel.h"
#include "lpc17xx_adc.h"

// defines for the analog sensors
#define AIR_CHAN        ADC_CHANNEL_0
#define AIR_PIN_FUNC    PINSEL_FUNC_1
#define AIR_PORT        PINSEL_PORT_0
#define AIR_PIN         PINSEL_PIN_23
#define USON_CHAN       ADC_CHANNEL_1
#define USON_PIN_FUNC   PINSEL_FUNC_1
#define USON_PORT       PINSEL_PORT_0
#define USON_PIN		PINSEL_PIN_24

#define ADCAVERAGING 100;

        /***************************************************************
         ***************** Command Function Prototypes *****************
         **************************************************************/
/*-------------------------------------------------------------------------------
 * Function Name	: analogSensorsInit
 * Description		: Initializes the necessary data structures for the ADC.
 *                    Also prepares the analog (ADC) pins for AIR_CHAN and
 *                    USON_CHAN. This function is ran at the beginning of the
 *                    process to initialize the appropriate hardware
 * ASSUMPTIONS		: None
 * Input			: None
 * Output			: Configures the hardware
 * Return			: None
 ------------------------------------------------------------------------------*/
void analogSensorsInit(void);

/*-------------------------------------------------------------------------------
 * Function Name	: uSonicValGet
 * Description		: Measures the ADC for the ultrasonic sensor and returns the
 *                    value
 * ASSUMPTIONS		: analogSensorsInit is ran beforehand
 * Input			: None
 * Output			: None
 * Return			: ADC value for the ultrasonic sensor
 ------------------------------------------------------------------------------*/
uint32_t uSonicValGet(void);

/*-------------------------------------------------------------------------------
 * Function Name	: airSpeedValGet
 * Description		: Measures the ADC for the air speed sensor and returns the
 *                    value
 * ASSUMPTIONS		: analogSensorsInit is ran beforehand
 * Input			: None
 * Output			: None
 * Return			: ADC value for the air speed sensor
 ------------------------------------------------------------------------------*/
uint32_t airSpeedValGet(void);

#endif /* DRIVERGENADC_H_ */
