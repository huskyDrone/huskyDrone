/*
 * muxTask.c
 *
 *  Created on: Mar 10, 2012
 *      Author: root
 */

#include "muxTask.h"

extern __IO Bool muxFlag;

__IO Bool ledFlag = FALSE;

void vMuxTask( void *pvParameters )
{
	Bool stable = FALSE;
	uint32_t cnt = 0;
	uint32_t cnt1 = 0;
	Bool toggle2 = 0;
	__IO uint32_t val1 = 0;
	uint32_t val1Old = 0;
	__IO uint32_t val2 = 0;
	__IO uint32_t val3 = 0;
	ledFlag = TRUE;

	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{

		if(muxFlag)
		{

			muxFlag = FALSE;

			if(!stable)
			{
				val3 = TIM_GetCaptureValue(MUX_TIMER, TIM_COUNTER_INCAP0);

				TIM_Cmd(MUX_TIMER,DISABLE);
				TIM_ResetCounter(MUX_TIMER);
				TIM_Cmd(MUX_TIMER,ENABLE);
				cnt++;
				if(cnt == 50) stable = TRUE;  //stable
			}
			else
			{
				cnt = 0;
				toggle2 = ~toggle2;

				if (toggle2)
				{
					val1 = TIM_GetCaptureValue(MUX_TIMER, TIM_COUNTER_INCAP0);
				}
				else
				{
					val2 = TIM_GetCaptureValue(MUX_TIMER, TIM_COUNTER_INCAP0);
				}

				TIM_Cmd(MUX_TIMER,DISABLE);
				TIM_ResetCounter(MUX_TIMER);
				TIM_Cmd(MUX_TIMER,ENABLE);
			}
		}

		//val1 = 599813: connected to PWM, one edge detection
		if(val1 > 480000)
		{
			muxSelManual();

			if(val1 == val1Old) cnt1++;
			else {cnt1 = 0;}
			val1Old = val1;

			if(cnt1 > 100000) val1 = 0;

		}
		else
		{
			muxSelAutonomous();
		}
	}
}
