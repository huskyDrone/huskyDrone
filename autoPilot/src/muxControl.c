/*
 * muxControl.c
 *
 *  Created on: Mar 5, 2012
 *      Author: root
 */

#include "muxControl.h"

__IO Bool muxFlag = FALSE;

void muxControlInit(void)
{
	PINSEL_CFG_Type     PinCfg;
	TIM_TIMERCFG_Type   muxTimer;
	TIM_CAPTURECFG_Type muxControlCapture;

	// prepare the GPIO for PWM capture
	PinCfg.Funcnum   = SWITCH_PIN_FUNC;
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCfg.Pinmode   = PINSEL_PINMODE_PULLUP;
	PinCfg.Portnum   = SWITCH_PORT;
	PinCfg.Pinnum    = SWITCH_PIN;
	PINSEL_ConfigPin(&PinCfg);

	// set p0.19 as an output
	GPIO_SetDir(SEL_PORT, (1 << SEL_PIN), 1);
	// set initial condition
	GPIO_SetValue(SEL_PORT, (1 << SEL_PIN));

	// prepare the Timer
	muxTimer.PrescaleOption = TIM_PRESCALE_TICKVAL;
	muxTimer.PrescaleValue  = 1;

	// prepare the capture module
	muxControlCapture.CaptureChannel = 0;
	muxControlCapture.FallingEdge    = ENABLE;
	muxControlCapture.RisingEdge     = ENABLE;
	muxControlCapture.IntOnCaption   = ENABLE;

	// initialize and reset the counter
	TIM_Init(MUX_TIMER, TIM_TIMER_MODE, &muxTimer);
	TIM_ConfigCapture(MUX_TIMER, &muxControlCapture);
	TIM_ResetCounter(MUX_TIMER);

	// prioritize the interrupt and start it
	NVIC_SetPriority(MUX_TIMER_IRQ, 10);
	NVIC_EnableIRQ(MUX_TIMER_IRQ);
	TIM_Cmd(MUX_TIMER, ENABLE);
}


void muxSelManual(void)
{
	GPIO_ClearValue(SEL_PORT, (1 << SEL_PIN));
}


void muxSelAutonomous(void)
{
	GPIO_SetValue(SEL_PORT, (1 << SEL_PIN));
}


void TIMER2_IRQHandler(void)
{
	if (TIM_GetIntCaptureStatus(MUX_TIMER,0))
	{
		if(!muxFlag) muxFlag = TRUE;
		TIM_ClearIntCapturePending(MUX_TIMER,0);
	}
}
