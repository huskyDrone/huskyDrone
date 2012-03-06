/*
 * taskSerial.c
 *
 *  Created on: Feb 11, 2012
 *      Author: root
 */

#include "taskSerial.h"

// current GPS Rx status
extern __IO SetState serialRxReady;

//extern serInputStruct serData;

//extern RingBuffer serialRxRb;

uint8_t buff[10];

void vSerialTask( void *pvParameters )
{
	uint32_t len;

	printf("Hello, this is a welcome message\r");
	printf("for huskyDrone project\r");
	printf("Authors: Trevor Wilcox, Derek Knox and Yevgeniy Maksimenko\r");

	for( ;; )
	{
		len = 0;


		if(serialRxReady)
		{
			printf("here\r");
			serialRxReady = RESET;
		}
/*
		while(len == 0)
		{
			len = UART_Receive(SER_UART, buff, sizeof(buff)-1, NONE_BLOCKING);
		}
		printf("len = %d\r", len);
*/
	}
}
