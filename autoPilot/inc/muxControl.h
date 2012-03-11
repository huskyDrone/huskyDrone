/*
 * muxControl.h
 *
 *  Created on: Mar 5, 2012
 *      Author: root
 */

#ifndef MUXCONTROL_H_
#define MUXCONTROL_H_

#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"


#define MUX_TIMER        LPC_TIM2
#define MUX_TIMER_IRQ    TIMER2_IRQn
#define SWITCH_PIN_FUNC  3
#define SWITCH_PORT      0
#define SWITCH_PIN       4

#define SEL_PIN_FUNC     0
#define SEL_PORT         0
#define SEL_PIN          19


void muxControlInit(void);
void muxSelManual(void);
void muxSelAutonomous(void);

#endif /* MUXCONTROL_H_ */
