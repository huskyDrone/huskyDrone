/*
 * testTask.c
 *
 *  Created on: Feb 6, 2012
 *      Author: jenya
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "testTask.h"

void vTestTask( void *pvParameters )
{
	portTickType xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		// wait for the next cycle
		vTaskDelayUntil(&xLastWakeTime, DELAY_PERIOD);

		// Turn the LED on
		LPC_GPIO3->FIOCLR = LED;

		// wait for the next cycle
		vTaskDelayUntil(&xLastWakeTime, DELAY_PERIOD);

		// Turn the LED off
		LPC_GPIO3->FIOSET = LED;
	}

}
