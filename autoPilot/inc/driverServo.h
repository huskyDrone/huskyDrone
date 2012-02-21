/*
 * driverServo.h
 *
 *  Created on: Feb 12, 2012
 *      Author: Trevor
 */

#ifndef DRIVERSERVO_H_
#define DRIVERSERVO_H_

typedef enum {AILERON_LEFT = 0, AILERON_RIGHT = 1, ELEVATOR = 2, RUDDER = 3} servo_channel_t;

extern int servoSetAngle(servo_channel_t channel, float degrees);
extern int servoSetThrust(float thrust_pct);
#endif /* DRIVERSERVO_H_ */
