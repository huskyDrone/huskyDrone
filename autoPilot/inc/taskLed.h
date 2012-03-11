/*
 * testTask.h
 *
 *  Created on: Feb 6, 2012
 *      Author: jenya
 */

#ifndef TESTTASK_H_
#define TESTTASK_H_

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "hwConfig.h"
#include "platformConfig.h"

// time interval in uSec
#define DELAY_PERIOD 500


        /***************************************************************
         ***************** Command Function Prototypes *****************
         **************************************************************/
/*-------------------------------------------------------------------------------
 * Function Name	: vLedTask
 * Description		: This task is used as a test for various components
 * ASSUMPTIONS		: The task was created in the main.c
 * Input			: None
 * Output			: Flashes the RED led with DELAY_PERIOD interval
 * Return			: None
 ------------------------------------------------------------------------------*/
void vLedTask(void *pvParameters);

#endif /* TESTTASK_H_ */
