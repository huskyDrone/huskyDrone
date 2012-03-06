/*
 * ADC.c
 *
 *  Created on: Feb 12, 2012
 *      Author: Derek
 */

#include "driverGenAdc.h"

uint32_t   airpressADC;
uint32_t   usonicADC;
//uint32_t   AirSpdADC[ADCAVERAGING];
//uint32_t   DistADC[ADCAVERAGING];
uint32_t   ADCCount;
uint32_t   AveAirSpdADC;
uint32_t   AveDistADC;
uint32_t   AveAirSpd;
uint32_t   AveDist;

void adcconfig(void)
{

	// pin configuration for AirSpeed Sensor
	PINSEL_CFG_Type airPin_intStr;
	// Pin Config for UltraSonic Distance Sensor
	PINSEL_CFG_Type usonicPin_intStr;

	//Setup Air Speed Sensor Pin
	airPin_intStr.Funcnum = AIR_PIN_FUNC;
	airPin_intStr.OpenDrain = PINSEL_PINMODE_NORMAL;
	airPin_intStr.Pinmode = PINSEL_PINMODE_PULLUP;
	airPin_intStr.Pinnum = AIR_PIN;
	airPin_intStr.Portnum = AIR_PORT;
	PINSEL_ConfigPin(&airPin_intStr);

	//UltraSonic Sensor Pin
	usonicPin_intStr.Funcnum = USON_PIN_FUNC;
	usonicPin_intStr.OpenDrain = PINSEL_PINMODE_NORMAL;
	usonicPin_intStr.Pinmode = PINSEL_PINMODE_PULLUP;
	usonicPin_intStr.Pinnum = USON_PIN;
	usonicPin_intStr.Portnum = USON_PORT;
	PINSEL_ConfigPin(&usonicPin_intStr);

	//Set AD Conversion Speed and Enable AD Channels
	ADC_Init(LPC_ADC, 200000);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_1, ENABLE);

	//Set Interupt after all conversions
	ADC_IntConfig (LPC_ADC, ADC_ADGINTEN, SET);

	//Start the AD Conversion Burst
	ADC_BurstCmd(LPC_ADC,ENABLE);

	airpressADC = 0;
	usonicADC = 0;
	ADCCount=0;
/*
	{
		AirSpdADC[ADCCount] = 0;
		DistADC[ADCCount] = 0;
		ADCCount++;
	} while (ADCCount<100)
	ADCCount = 0;
*/
}


void ADC_IRQHandler(void)
{
    //Grab Sensor Values
//	airpressADC = ADC_GetData(ADC_CHANNEL_0);
//    usonicADC= ADC_GetData(ADC_CHANNEL_1);

    //Store Sensor Values
//    AirSpdADC[ADCCount] = -.00017*airpressADC*airpressADC+1.4*airpressADC-2600; //Converts AD result to Kilometers per hour
//    DistADC[ADCCount] = .0021*usonicADC-.1; //Converts AD result to meters

    //Shifts Sensor Result Array
    ADCCount++;
    if (ADCCount>=100)
    {
    	ADCCount=0;
    }

    //Calculate Averaged Sensor Values

    AveDistADC=0;
//    int i;
/*
    for (i = 0; i<ADCAVERAGING; i++)
    {
    	AveAirSpdADC=AveAirSpdADC+AirSpdADC[i];
    	AveDistADC=AveDistADC+DistADC[i];
    }
    AveAirSpd=(32.2381*AveAirSpdADC-99966)^(.5)-33.871;
    AveDist=.0021*AveDistADC-.1;
*/
}
