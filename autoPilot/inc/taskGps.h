/*
 * taskGps.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jenya
 */

#ifndef TASKGPS_H_
#define TASKGPS_H_

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "hwConfig.h"
#include "platformConfig.h"
#include "driverGps.h"




void vGpsTask(void *pvParameters);

#endif /* TASKGPS_H_ */
