/*
 * driverSerial.h
 *
 *  Created on: Feb 11, 2012
 *      Author: root
 */

#ifndef DRIVERSERIAL_H_
#define DRIVERSERIAL_H_

#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "platformConfig.h"
#include "ringbuffer.h"
#include "util.h"

/*--- Serial Related Defines ---*/
#define SER_PIN_FUNC   PINSEL_FUNC_2
#define SER_PORT       PINSEL_PORT_0
#define SER_PIN_TX     PINSEL_PIN_0
#define SER_PIN_RX     PINSEL_PIN_1
#define SER_UART       LPC_UART3

#define SER_IN_MSG_SZ      30

typedef struct
{
	uint8_t   inputString[SER_IN_MSG_SZ];
	uint8_t   msgId;
	uint16_t  val;
} serInputStruct;

enum _serialMsgId
{
	DEBUG    = 0,
	OTHER
} serialMsgId;

void configSerial(void);
void Serial_IntReceive(void);
uint32_t SerialReceive(uint8_t *rxBuf, uint8_t bufLen);
Bool Serial_populateData(uint8_t *addr, uint8_t len);


#endif /* DRIVERSERIAL_H_ */
