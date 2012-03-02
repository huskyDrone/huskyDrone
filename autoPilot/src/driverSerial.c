/*
 * driverSerial.c
 *
 *  Created on: Feb 11, 2012
 *      Author: root
 */

#include "driverSerial.h"

// Serial port ring buffer
RING_BUFFER_TYPE serialRb;

// current Serail port Rx status
extern __IO SetState serialRxReady;

extern serInputStruct serData;

extern uint16_t ledRate;

// Serial RX ring buffer
RingBuffer serialRxRb;

void configSerial(void)
{
	// GPS UART configuration structure
	UART_CFG_Type   UART_initStructure;
	// GPS UART FIFO configuration structure
	UART_FIFO_CFG_Type UARTFIFO_initStructure;
	// Pin configuration for GPS UART
	PINSEL_CFG_Type pin_initStructure;

	// initialize UART3 pin connect
	pin_initStructure.Funcnum   = SER_PIN_FUNC;
	pin_initStructure.OpenDrain = PINSEL_PINMODE_NORMAL;
	pin_initStructure.Pinmode   = PINSEL_PINMODE_PULLUP;
	pin_initStructure.Pinnum    = SER_PIN_TX;
	pin_initStructure.Portnum   = SER_PORT;
	PINSEL_ConfigPin(&pin_initStructure);
	pin_initStructure.Pinnum    = SER_PIN_RX;
	PINSEL_ConfigPin(&pin_initStructure);

	// initialize GPS UART
	UART_initStructure.Baud_rate = 115200;
	UART_initStructure.Databits  = UART_DATABIT_8;
	UART_initStructure.Parity    = UART_PARITY_NONE;
	UART_initStructure.Stopbits  = UART_STOPBIT_1;

	// configure the UART
	UART_Init(SER_UART, &UART_initStructure);

	// initialize FIFO to default state:
	//          -FIFO_DMAMode = DISABLE
	//          -FIFO_Level = UART_FIFO_TRGLEV0
	//          -FIFO_ResetRxBuf = ENABLE
	//          -FIFO_ResetTxBuf = ENABLE
	//          -FIFO_State = ENABLE
	UART_FIFOConfigStructInit(&UARTFIFO_initStructure);

	// initialize FIFO for GPS UART
	UART_FIFOConfig(SER_UART, &UARTFIFO_initStructure);

	// enable the UART
	UART_TxCmd(SER_UART, ENABLE);

	// enable GPS_UART Rx interrupt
	UART_IntConfig(SER_UART, UART_INTCFG_RBR, ENABLE);

	// reset ring buf head and tail idx
	__BUF_RESET(serialRb.rx_head);
	__BUF_RESET(serialRb.rx_tail);
	__BUF_RESET(serialRb.tx_head);
	__BUF_RESET(serialRb.tx_tail);

	// preemption = 1, sub-priority = 1
	//NVIC_SetPriority(UART3_IRQn, ((0x01<<3)|0x01));
	NVIC_SetPriority(UART3_IRQn, 8);
	// enable interrupt for GPS UART channel
	NVIC_EnableIRQ(UART3_IRQn);

	// reset the Rx state
	serialRxReady = RESET;
}

void UART3_IRQHandler(void)
{
	//portBASE_TYPE xYieldRequired;
	uint32_t intsrc, tmp;

	// determine the interrupt source
	intsrc = UART_GetIntId(SER_UART);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// receive data available
	if(tmp == UART_IIR_INTID_RDA)
	{
		// disable the interrupt
		UART_IntConfig(SER_UART, UART_INTCFG_RBR, DISABLE);

		// set the Rx state flag
		serialRxReady = SET;
	}

	// transmit holding empty
	if(tmp == UART_IIR_INTID_THRE)
	{
		//GPS_IntTransmit();
	}
}


void Serial_IntReceive(void)
{
	uint8_t tmpc;
	uint32_t rLen;

	while(1)
	{
		// call UART read function in UART driver
		rLen = UART_Receive(SER_UART, &tmpc, 1, NONE_BLOCKING);

		// if there is data to receive
		if(rLen)
		{
			// checks whether the buffer is full and if it is not, adds the character
			// if there is no more room, trim the message
			ringBufferEnque(&serialRxRb, tmpc);
		}
		else // no more data
		{
			break;
		}
	}
}

uint32_t SerialReceive(uint8_t *rxBuf, uint8_t bufLen)
{
	uint8_t *data = (uint8_t *)rxBuf;
	uint32_t bytes = 0;

	// loop until receive buffer ring is empty or until max_bytes expires
	while((bufLen > 0) && (!ringBufferIsEmpty(&serialRxRb)))
	{
		ringBufferDeque(&serialRxRb, data);
		data++;

		// increment data count and decrement buffer size count
		bytes++;
		bufLen--;
	}

	return bytes;
}

Bool Serial_populateData(uint8_t *addr, uint8_t len)
{
	uint8_t *pBuff = addr;

	// find out type of the message
	if(*pBuff == 'D' && *(pBuff+1) == 'B' && *(pBuff+2) == 'G')
		serData.msgId = DEBUG;
	else
		serData.msgId = OTHER;

	// get to the comma (',')
	while(*pBuff != ',' && *pBuff != '*' && *pBuff != '\0')
	{
		pBuff++;
		len--;
		if(len == 0) return FALSE;
	}

	// next character after the comma
	pBuff++;

	switch (serData.msgId)
	{
	case DEBUG:
		ledRate = a2l(pBuff);
		break;
	default :
		return FALSE;
		break;
	}

	return TRUE;
}

void outbyte(char c)
{
	// write the character to the general UART
	UART_SendByte(SER_UART, (char) c);

	// loop until the end of transmission
	while ((SER_UART->LSR & UART_LSR_THRE) == RESET);
}
