/*
 * testTask.c
 *
 *  Created on: Feb 6, 2012
 *      Author: jenya
 */

#include "taskLed.h"

extern __IO Bool ledFlag;

void vLedTask( void *pvParameters )
{

	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		if(ledFlag)
		{
			// wait for the next cycle
			vTaskDelayUntil(&xLastWakeTime, DELAY_PERIOD);

			// Turn the LED on
			LPC_GPIO3->FIOCLR = RED_LED;

			// wait for the next cycle
			vTaskDelayUntil(&xLastWakeTime, DELAY_PERIOD);

			// Turn the LED off
			LPC_GPIO3->FIOSET = RED_LED;
		}
	}
}
