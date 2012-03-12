/*
 * driverServos.c
 *
 *  Created on: Feb 10, 2012
 *      Author: Trevor
 */
#include "driverServos.h"

#define DEFAULT_DEGREES 0.0f

#define AILERON_MIN  0.0f //todo figure out what these actual values are
#define AILERON_MAX  135.0f
#define ELEVATOR_MIN 0.0f
#define ELEVATOR_MAX 135.0f
#define RUDDER_MIN   0.0f
#define RUDDER_MAX   135.0f
#define THRUST_MIN   0.0f
#define THRUST_MAX   100.0f
float degreesMin[3] = {AILERON_MIN,ELEVATOR_MIN,RUDDER_MIN};
float degreesMax[3] = {AILERON_MAX,ELEVATOR_MAX,RUDDER_MAX};

volatile uint32_t* matchRegisters[3] = {&(LPC_PWM1->MR1),&(LPC_PWM1->MR2),&(LPC_PWM1->MR3)};

void servos_Init(void)
{
	//Positive Pulse Width = (1ms + deg/180)
	//Pulse Period = 20ms = 600000 cycles
	//Duty Cycle = PPW/20ms
	//Match Register Value = DC*600000
	//Match Register Value = ((1ms + deg/180)/20ms)*600000
	//Simplified Match Register Value = ((deg+180)*500)/3

	//Init peripheral
	LPC_SC->PCONP |= 1 << 6;      //Power up PWM peripheral
	LPC_SC->PCLKSEL0 |= 0 << 12; // PWM clock = uC/4 = 120MHz/4 = 30MHz
	LPC_PWM1->MR0 =  600000; // PWM freq = PWM clock/600000 = 50Hz, T=20ms
	LPC_PWM1->MCR |= 1 << 1; // Reset timer on Match0

	//Init PWM Channel 1 (Ailerons)
	LPC_PINCON->PINSEL3 |= 1 << 5; // P1.18 works as PWM1 output.
	LPC_PINCON->PINMODE3 |= 1 << 5; // enable neither pull up nor pull down.
	LPC_PWM1->MR1 = (int)(((DEFAULT_DEGREES+180.0f)*500.0f)/3);
	LPC_PWM1->PCR |= 1 << 9; // Enable PWM channel 1 output

	//Init PWM Channel 2 (Elevator)
	LPC_PINCON->PINSEL3 |= 1 << 9; // P1.20 works as PWM2 output.
	LPC_PINCON->PINMODE3 |= 1 << 9; // enable neither pull up nor pull down.
	LPC_PWM1->MR2 = (int)(((DEFAULT_DEGREES+180.0f)*500.0f)/3);
	LPC_PWM1->PCR |= 1 << 10; // Enable PWM channel 2 output

	//Init PWM Channel 3 (Rudder)
	LPC_PINCON->PINSEL7 |= 3 << 20; // P3.26 works as PWM3 output.
	LPC_PINCON->PINMODE7 |= 1 << 21; // enable neither pull up nor pull down.
	LPC_PWM1->MR3 = (int)(((DEFAULT_DEGREES+180.0f)*500.0f)/3);
	LPC_PWM1->PCR |= 1 << 11; // Enable PWM channel 3 output

	//Init PWM Channel 4 (Thrust)
	LPC_PINCON->PINSEL3 |= 1 << 15; // P1.23 works as PWM4 output.
	LPC_PINCON->PINMODE3 |= 1 << 15; // enable neither pull up nor pull down.
	LPC_PWM1->MR4 = (int)(((DEFAULT_DEGREES+180.0f)*500.0f)/3); //todo fix this init
	LPC_PWM1->PCR |= 1 << 12; // Enable PWM channel 4 output

	//Init PWM Channel 5 (Test FULL)
	LPC_PINCON->PINSEL3 |= 1 << 17; // P1.24 works as PWM5 output.
	LPC_PINCON->PINMODE3 |= 1 << 17; // enable neither pull up nor pull down.
	LPC_PWM1->MR5 = 60000; //Max Servo PW
	LPC_PWM1->PCR |= 1 << 13; // Enable PWM channel 5 output

	//Init PWM Channel 6 (Test MIN)
	LPC_PINCON->PINSEL4 |= 1 << 10; // P2.4 works as PWM6 output.
	LPC_PINCON->PINMODE4 |= 1 << 10; // enable neither pull up nor pull down.
	LPC_PWM1->MR6 = 30000;  //Min Servo PW
	LPC_PWM1->PCR |= 1 << 14; // Enable PWM channel 4 output

	LPC_PWM1->TCR |= (1 << 0) | (1 << 3);  //Enable PWM and PWM Counter/Timer
}

int servos_SetAngle(servo_channel_t channel, float degrees)
{
	if((int)channel>2)
	{
		//Invalid channel.
		return 1;
	}
	if((degrees>=degreesMin[(int)channel])&&(degrees<=degreesMax[(int)channel]))
	{
		*(matchRegisters[(int)channel]) = (int)(((degrees+180.0f)*500.0f)/3.0f);
		LPC_PWM1->LER |= (1<<((int)channel+1));
		return 0;
	} else {
		//Invalid degrees deflection.
		return 2;
	}
}
int servos_SetThrust(float thrust_pct)
{
	if((thrust_pct>=THRUST_MIN)&&(thrust_pct<=THRUST_MAX))
	{
		LPC_PWM1->MR4 = (int)((thrust_pct+100.0f)*300.0f);
		LPC_PWM1->LER |= (1<<4);
		return 0;
	}else{
		//Invalid thrust percentage.
		return 1;
	}
}
