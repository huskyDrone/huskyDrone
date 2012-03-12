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
	Bool toggle = 0;
	__IO uint32_t val1 = 0;
	uint32_t val1Old = 0;
	__IO uint32_t val2 = 0;
	__IO uint32_t val3 = 0;
	ledFlag = TRUE;

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

				// the interrupt is generated on both rising and falling edges
				// need to distinguish the counter value between the HIGH and
				// LOW states
				toggle = ~toggle;

				if (toggle)
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
			muxSelManual();   // switch the mode to Manual

			// this is used to make sure that the mode is switch
			// if the radio is switch OFF or mode is switch
			if(val1 == val1Old) cnt1++;
			else {cnt1 = 0;}
			val1Old = val1;
			if(cnt1 > 100000) val1 = 0;

		}
		else
		{
			muxSelAutonomous();  // switch the mode to Autonomous
		}
	}
}
