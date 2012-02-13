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

void configUART0(void);
void UART0_IntReceive(void);
uint32_t UART0Receive(uint8_t *rxBuf, uint8_t bufLen);


#endif /* DRIVERSERIAL_H_ */
