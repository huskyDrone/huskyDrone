/*
 * muxTask.h
 *
 *  Created on: Mar 10, 2012
 *      Author: root
 */

#ifndef MUXTASK_H_
#define MUXTASK_H_

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "hwConfig.h"
#include "platformConfig.h"

#include "muxControl.h"
#include "lpc17xx_gpio.h"

void vMuxTask( void *pvParameters );

#endif /* MUXTASK_H_ */
