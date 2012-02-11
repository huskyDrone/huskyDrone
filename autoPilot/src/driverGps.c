/*
 * driverGps.c
 *
 *  Created on: Feb 9, 2012
 *      Author: jenya
 */

/* Scheduler includes. */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "driverGps.h"

// GPS ring buffer
GPS_RING_BUFFER_TYPE gpsRb;

// current Tx Interrupt enable state
__IO FlagStatus TxIntStat;

// current GPS Rx status
extern __IO SetState gpsRxReady;

void configGpsUART(void)
{
	// GPS UART configuration structure
	UART_CFG_Type   UART_initStructure;
	// GPS UART FIFO configuration structure
	UART_FIFO_CFG_Type UARTFIFO_initStructure;
	// Pin configuration for GPS UART
	PINSEL_CFG_Type pin_initStructure;

	// initialize UART1 pin connect
	pin_initStructure.Funcnum   = GPS_PIN_FUNC;
	pin_initStructure.OpenDrain = PINSEL_PINMODE_NORMAL;
	pin_initStructure.Pinmode   = PINSEL_PINMODE_PULLUP;
	pin_initStructure.Pinnum    = GPS_PIN_TX;
	pin_initStructure.Portnum   = GPS_PORT;
	PINSEL_ConfigPin(&pin_initStructure);
	pin_initStructure.Pinnum    = GPS_PIN_RX;
	PINSEL_ConfigPin(&pin_initStructure);

	// initialize GPS UART
	UART_initStructure.Baud_rate = 115200;
	UART_initStructure.Databits  = UART_DATABIT_8;
	UART_initStructure.Parity    = UART_PARITY_NONE;
	UART_initStructure.Stopbits  = UART_STOPBIT_1;

	// configure the UART
	UART_Init((LPC_UART_TypeDef *)GPS_UART, &UART_initStructure);

	// initialize FIFO to default state:
	//          -FIFO_DMAMode = DISABLE
	//          -FIFO_Level = UART_FIFO_TRGLEV0
	//          -FIFO_ResetRxBuf = ENABLE
	//          -FIFO_ResetTxBuf = ENABLE
	//          -FIFO_State = ENABLE
	UART_FIFOConfigStructInit(&UARTFIFO_initStructure);

	// initialize FIFO for GPS UART
	UART_FIFOConfig((LPC_UART_TypeDef *)GPS_UART, &UARTFIFO_initStructure);

	// enable the UART
	UART_TxCmd((LPC_UART_TypeDef *)GPS_UART, ENABLE);

	// enable GPS_UART Rx interrupt
	UART_IntConfig((LPC_UART_TypeDef *)GPS_UART, UART_INTCFG_RBR, ENABLE);

	// reset ring buf head and tail idx
	__BUF_RESET(gpsRb.rx_head);
	__BUF_RESET(gpsRb.rx_tail);
	__BUF_RESET(gpsRb.tx_head);
	__BUF_RESET(gpsRb.tx_tail);

	// preemption = 1, sub-priority = 1
	NVIC_SetPriority(UART1_IRQn, ((0x01<<3)|0x01));
	// enable interrupt for GPS UART channel
	NVIC_EnableIRQ(UART1_IRQn);

	// reset the Rx state
	gpsRxReady = RESET;
}


void UART1_IRQHandler(void)
{
	//portBASE_TYPE xYieldRequired;
	uint32_t intsrc, tmp;

	// determine the interrupt source
	intsrc = UART_GetIntId((LPC_UART_TypeDef *)GPS_UART);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// receive data available
	if(tmp == UART_IIR_INTID_RDA)
	{
		//xYieldRequired = xTaskResumeFromISR();
		//if(xYieldRequired == pdTRUE)
		//{
		//	portYIELD_FROM_ISR();
		//}
		//GPS_IntReceive();

		// disable the interrupt
		UART_IntConfig((LPC_UART_TypeDef *)GPS_UART, UART_INTCFG_RBR, DISABLE);

		// set the Rx state flag
		gpsRxReady = SET;
	}

	// transmit holding empty
	if(tmp == UART_IIR_INTID_THRE)
	{
		//GPS_IntTransmit();
	}
}

void GPS_IntReceive(void)
{
	uint8_t tmpc;
	uint32_t rLen;

	while(1)
	{
		// call UART read function in UART driver
		rLen = UART_Receive((LPC_UART_TypeDef *)GPS_UART, &tmpc, 1, NONE_BLOCKING);

		// if there is data to receive
		if(rLen)
		{
			// check if there is more room in the buffer to put the character
			// if not, the rest will be trimmed off
			if(!__BUF_IS_FULL(gpsRb.rx_head, gpsRb.rx_tail))
			{
				gpsRb.rx[gpsRb.rx_head] = tmpc;
				__BUF_INCR(gpsRb.rx_head);
			}
		}
		else // no more data
		{
			break;
		}
	}
}

uint32_t GPSReceive(uint8_t *rxBuf, uint8_t bufLen)
{
	uint8_t *data = (uint8_t *)rxBuf;
	uint32_t bytes = 0;

	// loop until receive buffer ring is empty or until max_bytes expires
	while((bufLen > 0) && (!(__BUF_IS_EMPTY(gpsRb.rx_head, gpsRb.rx_tail))))
	{
		// read from the ring buffer into user buffer
		*data = gpsRb.rx[gpsRb.rx_tail];
		data++;

		// update the pointer
		__BUF_INCR(gpsRb.rx_tail);

		// increment data count and decrement buffer size count
		bytes++;
		bufLen--;
	}

	return bytes;
}

/*
void nmea_zero_GPVTG(nmeaGPVTG *pack)
{
	memset(pack, 0, sizeof(nmeaGPVTG));
	pack->dir_t = 'T';
	pack->dec_m = 'M';
	pack->spn_t = 'N';
	pack->spk_t = 'K';
}
*/
