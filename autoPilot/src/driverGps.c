/*
 * driverGps.c
 *
 *  Created on: Feb 9, 2012
 *      Author: jenya
 */

#include "driverGps.h"

// GPS ring buffer
RING_BUFFER_TYPE gpsRb;

// GPS RX ring buffer
RingBuffer gpsRxRb;

// current Tx Interrupt enable state
__IO FlagStatus TxIntStat;

// current GPS Rx status
extern __IO SetState gpsRxReady;

// structure with of GPS data in GPVTG format
extern nmeaGPVTG gpsData;

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
	UART_Init(GPS_UART, &UART_initStructure);

	// initialize FIFO to default state:
	//          -FIFO_DMAMode = DISABLE
	//          -FIFO_Level = UART_FIFO_TRGLEV0
	//          -FIFO_ResetRxBuf = ENABLE
	//          -FIFO_ResetTxBuf = ENABLE
	//          -FIFO_State = ENABLE
	UART_FIFOConfigStructInit(&UARTFIFO_initStructure);

	// initialize FIFO for GPS UART
	UART_FIFOConfig(GPS_UART, &UARTFIFO_initStructure);

	// enable the UART
	UART_TxCmd(GPS_UART, ENABLE);

	// enable GPS_UART Rx interrupt
	UART_IntConfig(GPS_UART, UART_INTCFG_RBR, ENABLE);

	// reset ring buf head and tail idx
	__BUF_RESET(gpsRb.rx_head);
	__BUF_RESET(gpsRb.rx_tail);
	__BUF_RESET(gpsRb.tx_head);
	__BUF_RESET(gpsRb.tx_tail);

	// reset the Rx ring buffer
	ringBufferInit(&gpsRxRb);

	// preemption = 1, sub-priority = 1
	//NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));
	NVIC_SetPriority(UART0_IRQn, 7);
	// enable interrupt for GPS UART channel
	NVIC_EnableIRQ(UART0_IRQn);

	// reset the Rx state
	gpsRxReady = RESET;
}


void UART0_IRQHandler(void)
{
	//portBASE_TYPE xYieldRequired;
	uint32_t intsrc, tmp;

	// determine the interrupt source
	intsrc = UART_GetIntId(GPS_UART);
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
		UART_IntConfig(GPS_UART, UART_INTCFG_RBR, DISABLE);

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
		rLen = UART_Receive(GPS_UART, &tmpc, 1, NONE_BLOCKING);

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

			// checks whether the buffer is full and if it is not, adds the character
			// if there is no more room, trim the message
			//ringBufferEnque(&gpsRxRb, tmpc);
		}
		else // no more data
		{
			break;
		}
	}
}

uint32_t GPSReceive(char *rxBuf, uint8_t bufLen)
{
	uint8_t *data = (uint8_t *)rxBuf;
	uint32_t bytes = 0;
/*
	// loop until receive buffer ring is empty or until max_bytes expires
	while((bufLen > 0) && (!ringBufferIsEmpty(&gpsRxRb)))
	{
		ringBufferDeque(&gpsRxRb, data);
		data++;

		// increment data count and decrement buffer size count
		bytes++;
		bufLen--;
	}
*/
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

Bool GPS_populateGPVTG(uint8_t *addr, uint8_t len)
{
	uint8_t *pBuff = addr;
	int i;

	for(i = 0; i < GPVTG_TOTAL; i++)
	{
		// get to the comma (',')
		while(*pBuff != ',' && *pBuff != '*' && *pBuff != '\0')
		{
			pBuff++;
			len--;
			if(len == 0) return FALSE;
		}

		pBuff++;

		switch(i)
		{
		case DIR:
			gpsData.dir = a2d(pBuff);
			break;
		case DIR_T:
			gpsData.dir_t = *pBuff;
			break;
		case DEC:
			gpsData.dec = a2d(pBuff);
			break;
		case DEC_M:
		    gpsData.dec_m = *pBuff;
		    break;
		case SPN:
			gpsData.spn = a2d(pBuff);
			break;
		case SPN_N:
			gpsData.spn_n = *pBuff;
			break;
		case SPK:
			gpsData.spk = a2d(pBuff);
			break;
		case SPK_K:
			gpsData.spk_k = *pBuff;
			break;
		default:
			return FALSE;
			break;
		}
	}
	return TRUE;
}

Bool GPS_validateChkSum(uint8_t *addr, uint8_t len)
{
	uint8_t *pBuff     = addr;
	uint8_t compChkSum = 0;
	uint8_t rxChkSum   = 0;

	compChkSum = checkSum8((pBuff+1), len - 4);
	rxChkSum = rxCheckSum(pBuff);

	return (compChkSum == rxChkSum);
}

uint8_t checkSum8(uint8_t *addr, uint8_t len)
{
	__IO uint8_t checkSum = 0;

	while(len > 1)
	{
		checkSum ^= *(addr)++;
		len--;
	}

	if(len > 0)
	{
		checkSum ^= *addr;
	}

	return checkSum;
}

uint8_t rxCheckSum(uint8_t *addr)
{
	uint8_t firstPart  = 0;
	uint8_t secondPart = 0;
	uint8_t final      = 0;

	while(*addr != '\0' && *addr != '*')
	{
		addr++;
	}

	if(*addr == '*')
	{
		addr++;
		firstPart = XTOD(*addr);
		secondPart = XTOD(*(addr+1));
		final = (firstPart << 4 | secondPart);
	}

	return final;
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
