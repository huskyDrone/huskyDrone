/*
 * taskSerial.c
 *
 *  Created on: Feb 11, 2012
 *      Author: root
 */

#include "taskSerial.h"

// current GPS Rx status
extern __IO SetState serialRxReady;

void vSerialTask( void *pvParameters )
{
	for( ;; )
	{
		if(serialRxReady)
		{
			// get the message from the UART port and place it
			// into the ring buffer (gpsRb)
			UART0_IntReceive();

			// copy the command in the local buffer
			//GPSReceive(&gpsData.cmdString, GPS_DATA_SIZE);

			// we are done with the current message, re-enable
			// the RX interrupt
			UART_IntConfig((LPC_UART_TypeDef *)LPC_UART1, UART_INTCFG_RBR, ENABLE);

			// reset the RX flag, should follow right
			// after enabling the interrupt
			serialRxReady = RESET;
		}
	}

}
