/*
 * taskGps.c
 *
 *  Created on: Feb 10, 2012
 *      Author: jenya
 */

#include "taskGps.h"

// current GPS Rx status
extern __IO SetState gpsRxReady;

void vGpsTask( void *pvParameters )
{

	for( ;; )
	{
		if(gpsRxReady)
		{
			// get the message from the UART port and place it
			// into the ring buffer (gpsRb)
			GPS_IntReceive();

			// copy the command in the local buffer
			//GPSReceive(&gpsData.cmdString, GPS_DATA_SIZE);

			// we are done with the current message, re-enable
			// the RX interrupt
			UART_IntConfig((LPC_UART_TypeDef *)GPS_UART, UART_INTCFG_RBR, ENABLE);

			// reset the RX flag, should follow right
			// after enabling the interrupt
			gpsRxReady = RESET;
		}
	}

}
