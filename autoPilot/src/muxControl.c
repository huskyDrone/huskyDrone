/*
 * muxControl.c
 *
 *  Created on: Mar 5, 2012
 *      Author: root
 */

#include "muxControl.h"

void muxControlInit(void)
{
	PINSEL_CFG_Type PinCfg;
	TIM_TIMERCFG_Type  muxTimer;
	TIM_CAPTURECFG_Type muxControlCapture;

	// prepare the GPIO function
	PinCfg.Funcnum   = SWITCH_PIN_FUNC;
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCfg.Pinmode   = PINSEL_PINMODE_PULLUP;
	PinCfg.Portnum   = SWITCH_PORT;
	PinCfg.Pinnum    = SWITCH_PIN;
	PINSEL_ConfigPin(&PinCfg);

	// prepare the Timer
	muxTimer.PrescaleOption = TIM_PRESCALE_USVAL;
	muxTimer.PrescaleValue  = 1000000;

	// prepare the capture module
	muxControlCapture.CaptureChannel = 0;
	muxControlCapture.FallingEdge    = ENABLE;
	muxControlCapture.RisingEdge     = DISABLE;
	muxControlCapture.IntOnCaption   = ENABLE;


	TIM_Init(MUX_TIMER, TIM_TIMER_MODE, &muxTimer);
	TIM_ConfigCapture(MUX_TIMER, &muxControlCapture);
	TIM_ResetCounter(MUX_TIMER);

	NVIC_SetPriority(MUX_TIMER_IRQ, ((0x01<<3)|0x01));
	NVIC_EnableIRQ(MUX_TIMER_IRQ);
	TIM_Cmd(MUX_TIMER, ENABLE);
}

void TIMER3_IRQHandler(void)
{
	if (TIM_GetIntCaptureStatus(MUX_TIMER, 0))
	{
		TIM_ClearIntCapturePending(MUX_TIMER, 0);
		printf("hi\r");
	}
}
