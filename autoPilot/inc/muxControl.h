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


#define MUX_TIMER   LPC_TIM3
#define MUX_TIMER_IRQ  TIMER0_IRQn
#define SWITCH_PIN_FUNC  3
#define SWITCH_PORT 1
#define SWITCH_PIN  26


void muxControlInit(void);

#endif /* MUXCONTROL_H_ */
