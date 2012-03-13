/*
 * taskDemo.c
 *
 *  Created on: Mar 5, 2012
 *      Author: Trevor
 */


/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "hwConfig.h"
#include "platformConfig.h"
#include "taskLed.h"
#include "driverServos.h"

#define DEMO_HOLD_RATE 2000
#define DEMO_TRANS_RATE 250
#define DEMO_MIN_ANGLE -45
#define DEMO_MAX_ANGLE 45
#define DEMO_TRANS_WAIT (unsigned int)(DEMO_TRANS_RATE/(DEMO_MAX_ANGLE-DEMO_MIN_ANGLE))

int angle = DEMO_MIN_ANGLE;

portTickType holdRate = DEMO_HOLD_RATE;
portTickType transRate = DEMO_TRANS_RATE;
portTickType transWait = DEMO_TRANS_WAIT;

void vDemoTask( void *pvParameters )
{
	portTickType xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		//servos_SetThrust(30);
		// wait for the next cycle
		vTaskDelayUntil(&xLastWakeTime, holdRate);
		while(angle<=DEMO_MAX_ANGLE)
		{
			angle++;
			servos_SetAngle(AILERONS,(float)angle);
			servos_SetAngle(ELEVATOR,(float)angle);
			servos_SetAngle(RUDDER,(float)angle);
			// wait for the next cycle
			vTaskDelayUntil(&xLastWakeTime, transWait);
		}
		//servos_SetThrust(35);
		// wait for the next cycle
		vTaskDelayUntil(&xLastWakeTime, holdRate);

		while(angle>=DEMO_MIN_ANGLE)
		{
			angle--;
			servos_SetAngle(AILERONS,(float)angle);
			servos_SetAngle(ELEVATOR,(float)angle);
			servos_SetAngle(RUDDER,(float)angle);
			// wait for the next cycle
			vTaskDelayUntil(&xLastWakeTime, transWait);
		}
	}

}
