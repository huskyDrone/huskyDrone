/*
 * taskSerial.c
 *
 *  Created on: Feb 11, 2012
 *      Author: root
 */

#include "taskSerial.h"

// current GPS Rx status
extern __IO SetState serialRxReady;

extern serInputStruct serData;

uint8_t testStr[20] = "huskyDrone";

void vSerialTask( void *pvParameters )
{
	UART_Send(SER_UART, &testStr, 10, NONE_BLOCKING);

	for( ;; )
	{

		if(serialRxReady)
		{
			// get the message from the UART port and place it
			// into the ring buffer
			Serial_IntReceive();

			// copy the command in the local buffer
			SerialReceive(&serData.inputString[0], SER_IN_MSG_SZ);

			// we are done with the current message, re-enable
			// the RX interrupt
			UART_IntConfig(SER_UART, UART_INTCFG_RBR, ENABLE);

			// reset the RX flag, should follow right
			// after enabling the interrupt
			serialRxReady = RESET;

			// decompose the message
			Serial_populateData(&serData.inputString[0], SER_IN_MSG_SZ);
		}
	}

}
