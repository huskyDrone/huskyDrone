/*
 * driverGps.h
 *
 *  Created on: Feb 9, 2012
 *      Author: jenya
 */

#ifndef DRIVERGPS_H_
#define DRIVERGPS_H_

/* Scheduler includes. */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "platformConfig.h"
#include "ringbuffer.h"
#include "util.h"

/*--- GPS Related Defines ---*/
#define GPS_PIN_FUNC   PINSEL_FUNC_1
#define GPS_PORT       PINSEL_PORT_0
#define GPS_PIN_TX     PINSEL_PIN_2
#define GPS_PIN_RX     PINSEL_PIN_3
#define GPS_UART       LPC_UART0

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

*/

/*
 *  This enum reflects the order of parameters in a GPVTG type message
 */
enum _nmeaGPVTG_pack
{
	DIR            = 0,
	DIR_T          = 1,
	DEC            = 2,
	DEC_M          = 3,
	SPN            = 4,
	SPN_N          = 5,
	SPK            = 6,
	SPK_K          = 7,
	GPVTG_TOTAL    = 8
} nmeaGPVTG_pack;

typedef struct
{
	char  cmdString[GPS_DATA_SIZE];
	double          dir;    // True track made good (degrees)
	uint8_t         dir_t;  // Fixed text 'T' indicates that track make good is relative to true north
	double          dec;    // Magnetic track made good
	uint8_t         dec_m;  // Fixed text 'M'
	double          spn;    // Ground speed, knots
	uint8_t         spn_n;  // Fixed text 'N' indicates that speed over ground is in knots
	double          spk;    // Ground speed, k/h
	uint8_t         spk_k;  // Fixed text 'K' indicates that speed over ground in in K/h

} nmeaGPVTG;


void configGpsUART(void);

void GPS_IntTransmit(void);
void GPS_IntReceive(void);

uint32_t GPSReceive(char *rxBuf, uint8_t bufLen);
uint32_t GPSSend(LPC_UART_TypeDef *UARTPort, uint8_t *txBuf, uint8_t bufLen);
Bool GPS_validateChkSum(uint8_t *addr, uint8_t len);
uint8_t checkSum8(uint8_t *addr, uint8_t len);
uint8_t rxCheckSum(uint8_t *addr);

Bool GPS_populateGPVTG(uint8_t *addr, uint8_t len);

//void nmea_zero_GPVTG(nmeaGPVTG *pack);

#endif /* DRIVERGPS_H_ */
