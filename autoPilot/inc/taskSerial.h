/*
 * taskSerial.h
 *
 *  Created on: Feb 11, 2012
 *      Author: root
 */

#ifndef TASKSERIAL_H_
#define TASKSERIAL_H_

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "hwConfig.h"
#include "platformConfig.h"
#include "driverSerial.h"
#include "print_utils.h"

void vSerialTask( void *pvParameters );

#endif /* TASKSERIAL_H_ */
