/*
 * driverServo.h
 *
 *  Created on: Feb 12, 2012
 *      Author: Trevor
 */

#ifndef DRIVERSERVOS_H_
#define DRIVERSERVOS_H_

#include "lpc17xx_pwm.h"

typedef enum {AILERONS = 0, ELEVATOR = 1, RUDDER = 2} servo_channel_t;

extern int servos_SetAngle(servo_channel_t channel, float degrees);
extern int servos_SetThrust(float thrust_pct);
extern void servos_Init(void);

#endif /* DRIVERSERVOS_H_ */
