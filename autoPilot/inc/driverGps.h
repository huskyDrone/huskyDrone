/*
 * driverGps.h
 *
 *  Created on: Feb 9, 2012
 *      Author: jenya
 */

#ifndef DRIVERGPS_H_
#define DRIVERGPS_H_

#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"

/*--- GPS Related Defines ---*/
#define GPS_PIN_FUNC   PINSEL_FUNC_1
#define GPS_PORT       PINSEL_PORT_0
#define GPS_PIN_TX     PINSEL_PIN_15
#define GPS_PIN_RX     PINSEL_PIN_16
#define GPS_UART       LPC_UART1

// buffer size, will be used as a ring buffer
#define GPS_RING_BUFSIZE    256

// buf mask
#define __BUF_MASK (GPS_RING_BUFSIZE - 1)
// check if buf is full
#define __BUF_IS_FULL(head, tail) ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
// check buf will be full in next receiving or not
#define __BUF_WILL_FULL(hea, tail) ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
// check if buf is empty
#define __BUF_IS_EMPTY(head, tail) ((head&__BUF_MASK)==(tail&__BUF_MASK))
// reset the buf
#define __BUF_RESET(bufidx) (bufidx=0)
#define __BUF_INCR(bufidx)  (bufidx=(bufidx+1)&__BUF_MASK)


typedef struct
{
	__IO uint32_t tx_head;               // Tx ring buffer head index
	__IO uint32_t tx_tail;               // Tx ring buffer tail index
	__IO uint32_t rx_head;               // Rx ring buffer head index
	__IO uint32_t rx_tail;               // Rx ring buffer tail index
	__IO uint8_t  tx[GPS_RING_BUFSIZE];  // Tx data ring buffer
	__IO uint8_t  rx[GPS_RING_BUFSIZE];  // Rx data ring buffer
} GPS_RING_BUFFER_TYPE;


#define GPS_DATA_SIZE    30
#define MESS_ID_SIZE      5

/*
// NMEA packets type
enum nmeaPACKTYPE
{
	GPNON   = 0x0000,   // Unknown packet type
	GPGGA   = 0x0001,   // GGA - Essential fix data which proved 3d location and accuracy data
	GPGSA   = 0x0002,   // GSA - GPS receiver operating mode, SVs used for navigation, and DOP values
	GPGSV   = 0x0004,   // GSV - Number of SVs in the view, PRN numbers, elevation, azimuth & SNR values
	GPRMC   = 0x0008,   // RMC - Recommended Minimum Specific GPS/TRANSIT data
	GPVTG   = 0x0010,   // VTG - Actual track make good and speed over ground
};

typedef struct
{
	uint8_t  cmdString[GPS_DATA_SIZE];
	double   dir;  // True track made good (degrees)
	uint8_t  dir_t;  // Fixed text 'T' indicates that track make good is relative to true north
	double   dec;    // Magnetic track made good
	uint8_t  dec_m;  // Fixed text 'M'
	double   spn;    // Ground speed, knots
	uint8_t  spn_t;  // Fixed text 'N' indicates that speed over ground is in knots
	double   spk;    // Ground speed, k/h
	uint8_t  spk_t;  // Fixed text 'K' indicates that speed over ground in in K/h

} nmeaGPVTG;

*/
void configGpsUART(void);

void UART1_IRQHandler(void);
void GPS_IntTransmit(void);
void GPS_IntReceive(void);

uint32_t GPSReceive(uint8_t *rxBuf, uint8_t bufLen);
uint32_t GPSSend(LPC_UART_TypeDef *UARTPort, uint8_t *txBuf, uint8_t bufLen);

//void nmea_zero_GPVTG(nmeaGPVTG *pack);

#endif /* DRIVERGPS_H_ */