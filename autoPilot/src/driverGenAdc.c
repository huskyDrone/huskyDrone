/*
 * ADC.c
 *
 *  Created on: Feb 12, 2012
 *      Author: Derek
 */

#include "driverGenAdc.h"

void analogSensorsInit(void)
{

	// pin configuration for AirSpeed Sensor
	PINSEL_CFG_Type airPin_intStr;
	// pin configuration for UltraSonic Distance Sensor
	PINSEL_CFG_Type usonicPin_intStr;

	//Setup Air Speed Sensor Pin
	airPin_intStr.Funcnum   = AIR_PIN_FUNC;
	airPin_intStr.OpenDrain = PINSEL_PINMODE_NORMAL;
	airPin_intStr.Pinmode   = PINSEL_PINMODE_PULLUP;
	airPin_intStr.Pinnum    = AIR_PIN;
	airPin_intStr.Portnum   = AIR_PORT;
	PINSEL_ConfigPin(&airPin_intStr);

	//UltraSonic Sensor Pin
	usonicPin_intStr.Funcnum   = USON_PIN_FUNC;
	usonicPin_intStr.OpenDrain = PINSEL_PINMODE_NORMAL;
	usonicPin_intStr.Pinmode   = PINSEL_PINMODE_PULLUP;
	usonicPin_intStr.Pinnum    = USON_PIN;
	usonicPin_intStr.Portnum   = USON_PORT;
	PINSEL_ConfigPin(&usonicPin_intStr);

	// set AD Conversion speed
	ADC_Init(LPC_ADC, 200000);
	// disable the interrupt
	ADC_IntConfig (LPC_ADC, ADC_ADGINTEN, SET);
	// enable the ADC channels
	ADC_ChannelCmd(LPC_ADC, AIR_CHAN, ENABLE);
	ADC_ChannelCmd(LPC_ADC, USON_CHAN, ENABLE);
}


uint32_t uSonicValGet(void)
{
	// start conversion
	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	// wait conversion complete
	while (!(ADC_ChannelGetStatus(LPC_ADC, USON_CHAN, ADC_DATA_DONE)));
	// return the value
	return ADC_ChannelGetData(LPC_ADC, USON_CHAN);
}


uint32_t airSpeedValGet(void)
{
	// start conversion
	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	// wait conversion complete
	while (!(ADC_ChannelGetStatus(LPC_ADC, AIR_CHAN, ADC_DATA_DONE)));
	// return the value
	return ADC_ChannelGetData(LPC_ADC, AIR_CHAN);
}
/*
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

    for (i = 0; i<ADCAVERAGING; i++)
    {
    	AveAirSpdADC=AveAirSpdADC+AirSpdADC[i];
    	AveDistADC=AveDistADC+DistADC[i];
    }
    AveAirSpd=(32.2381*AveAirSpdADC-99966)^(.5)-33.871;
    AveDist=.0021*AveDistADC-.1;

}
*/
