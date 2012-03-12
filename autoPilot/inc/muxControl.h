/*
 * muxControl.h
 *
 *  Created on: Mar 5, 2012
 *      Author: root
 */

#ifndef MUXCONTROL_H_
#define MUXCONTROL_H_

// the necessary include
#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

// defines for pwm capture pin and timer
#define MUX_TIMER        LPC_TIM2
#define MUX_TIMER_IRQ    TIMER2_IRQn
#define SWITCH_PIN_FUNC  3
#define SWITCH_PORT      0
#define SWITCH_PIN       4

// defines for select line of the mux board
#define SEL_PIN_FUNC     0
#define SEL_PORT         0
#define SEL_PIN          19


        /***************************************************************
         ***************** Command Function Prototypes *****************
         **************************************************************/
/*-------------------------------------------------------------------------------
 * Function Name	: muxControlInit
 * Description		: Initializes the necessary data structures for a timer.
 *                    Also prepares the pwm capture pin and mux select line pin.
 *                    This function is ran at the beginning of the process to
 *                    initialize the appropriate hardware
 * ASSUMPTIONS		: None
 * Input			: None
 * Output			: Configures the hardware
 * Return			: None
 ------------------------------------------------------------------------------*/
void muxControlInit(void);

/*-------------------------------------------------------------------------------
 * Function Name	: muxSelManual
 * Description		: Used to control the mux select line; sets it LOW (Manual or
 *                    Radio mode)
 * ASSUMPTIONS		: muxControlInit has been ran beforehand
 * Input			: None
 * Output			: Switches the mux circuitry to the Manual/Radio mode
 * Return			: None
 ------------------------------------------------------------------------------*/
void muxSelManual(void);

/*-------------------------------------------------------------------------------
 * Function Name	: muxSelAutonomous
 * Description		: Used to control the mux select line; sets it HIGH
 *                    (Autonomous mode)
 * ASSUMPTIONS		: muxControlInit has been ran beforehand
 * Input			: None
 * Output			: Switches the mux circuitry to the Autonomous mode
 * Return			: None
 ------------------------------------------------------------------------------*/
void muxSelAutonomous(void);

#endif /* MUXCONTROL_H_ */
