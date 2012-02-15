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

/*--- Serial Related Defines ---*/
#define SER_PIN_FUNC   PINSEL_FUNC_2
#define SER_PORT       PINSEL_PORT_0
#define SER_PIN_TX     PINSEL_PIN_0
#define SER_PIN_RX     PINSEL_PIN_1
#define SER_UART       LPC_UART3

void configSerial(void);
void Serial_IntReceive(void);
uint32_t SerialReceive(uint8_t *rxBuf, uint8_t bufLen);


#endif /* DRIVERSERIAL_H_ */
