/*
 * hw_config.c
 *
 *  Created on: Feb 7, 2012
 *      Author: jenya
 */

#include "hwConfig.h"

void setSystem(void)
{
	// disable peripherals power
	LPC_SC->PCONP = 0;

	// enable GPIO power
	LPC_SC->PCONP = CLKPWR_PCONP_PCGPIO;

	// disable TPIU
	LPC_PINCON->PINSEL10 = 0;

	if ( LPC_SC->PLL0STAT & ( 1 << 25 ) )
	{
		/* Enable PLL, disconnected. */
		LPC_SC->PLL0CON = 1;
		LPC_SC->PLL0FEED = PLLFEED_FEED1;
		LPC_SC->PLL0FEED = PLLFEED_FEED2;
	}

	/* Disable PLL, disconnected. */
	LPC_SC->PLL0CON = 0;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/* Enable main OSC. */
	LPC_SC->SCS |= 0x20;
	while( !( LPC_SC->SCS & 0x40 ) );

	/* select main OSC, 12MHz, as the PLL clock source. */
	LPC_SC->CLKSRCSEL = 0x1;

	LPC_SC->PLL0CFG = 0x20031;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/* Enable PLL, disconnected. */
	LPC_SC->PLL0CON = 1;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;

	/* Set clock divider. */
	LPC_SC->CCLKCFG = 0x03;

	/* Configure flash accelerator. */
	LPC_SC->FLASHCFG = 0x403a;

	/* Check lock bit status. */
	while( ( ( LPC_SC->PLL0STAT & ( 1 << 26 ) ) == 0 ) );

	/* Enable and connect. */
	LPC_SC->PLL0CON = 3;
	LPC_SC->PLL0FEED = PLLFEED_FEED1;
	LPC_SC->PLL0FEED = PLLFEED_FEED2;
	while( ( ( LPC_SC->PLL0STAT & ( 1 << 25 ) ) == 0 ) );




	/* Configure the clock for the USB. */

	if( LPC_SC->PLL1STAT & ( 1 << 9 ) )
	{
		/* Enable PLL, disconnected. */
		LPC_SC->PLL1CON = 1;
		LPC_SC->PLL1FEED = PLLFEED_FEED1;
		LPC_SC->PLL1FEED = PLLFEED_FEED2;
	}

	/* Disable PLL, disconnected. */
	LPC_SC->PLL1CON = 0;
	LPC_SC->PLL1FEED = PLLFEED_FEED1;
	LPC_SC->PLL1FEED = PLLFEED_FEED2;

	LPC_SC->PLL1CFG = 0x23;
	LPC_SC->PLL1FEED = PLLFEED_FEED1;
	LPC_SC->PLL1FEED = PLLFEED_FEED2;

	/* Enable PLL, disconnected. */
	LPC_SC->PLL1CON = 1;
	LPC_SC->PLL1FEED = PLLFEED_FEED1;
	LPC_SC->PLL1FEED = PLLFEED_FEED2;
	while( ( ( LPC_SC->PLL1STAT & ( 1 << 10 ) ) == 0 ) );

	/* Enable and connect. */
	LPC_SC->PLL1CON = 3;
	LPC_SC->PLL1FEED = PLLFEED_FEED1;
	LPC_SC->PLL1FEED = PLLFEED_FEED2;
	while( ( ( LPC_SC->PLL1STAT & ( 1 << 9 ) ) == 0 ) );

	/*  Setup the peripheral bus to be the same as the PLL output (64 MHz). */
	LPC_SC->PCLKSEL0 = 0x05555555;

	// configure the RED_LED
	configRedLed();
}

void configRedLed(void)
{
	// RED LED on port 3
	LPC_GPIO3->FIODIR  = RED_LED;

	// start with the LED OFF
	LPC_GPIO3->FIOCLR = RED_LED;
}

void configPwm(void)
{
	// enable the PWM power
	LPC_SC->PCONP |= CLKPWR_PCONP_PCPWM1;

	// set the clock divider to 1
	LPC_SC->PCLKSEL0 |= CLKPWR_PCLKSEL_PWM1;
}

void configUART0(void)
{
	// GPS UART configuration structure
	UART_CFG_Type   UART_initStructure;
	// GPS UART FIFO configuration structure
	UART_FIFO_CFG_Type UARTFIFO_initStructure;
	// Pin configuration for GPS UART
	PINSEL_CFG_Type pin_initStructure;

	// initialize UART1 pin connect
	pin_initStructure.Funcnum   = PINSEL_FUNC_1;
	pin_initStructure.OpenDrain = PINSEL_PINMODE_NORMAL;
	pin_initStructure.Pinmode   = PINSEL_PINMODE_PULLUP;
	pin_initStructure.Pinnum    = PINSEL_PIN_3;
	pin_initStructure.Portnum   = PINSEL_PORT_0;
	PINSEL_ConfigPin(&pin_initStructure);
	pin_initStructure.Pinnum    = PINSEL_PIN_4;
	PINSEL_ConfigPin(&pin_initStructure);

	// initialize GPS UART
	UART_initStructure.Baud_rate = 115200;
	UART_initStructure.Databits  = UART_DATABIT_8;
	UART_initStructure.Parity    = UART_PARITY_NONE;
	UART_initStructure.Stopbits  = UART_STOPBIT_1;

	// configure the UART
	UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UART_initStructure);

	// initialize FIFO to default state:
	//          -FIFO_DMAMode = DISABLE
	//          -FIFO_Level = UART_FIFO_TRGLEV0
	//          -FIFO_ResetRxBuf = ENABLE
	//          -FIFO_ResetTxBuf = ENABLE
	//          -FIFO_State = ENABLE
	UART_FIFOConfigStructInit(&UARTFIFO_initStructure);

	// initialize FIFO for GPS UART
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFO_initStructure);

	// enable the UART
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);

	// enable GPS_UART Rx interrupt
	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART0, UART_INTCFG_RBR, ENABLE);

	/*
	// reset ring buf head and tail idx
	__BUF_RESET(gpsRb.rx_head);
	__BUF_RESET(gpsRb.rx_tail);
	__BUF_RESET(gpsRb.tx_head);
	__BUF_RESET(gpsRb.tx_tail);
	*/

	// preemption = 1, sub-priority = 1
	NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));
	// enable interrupt for GPS UART channel
	NVIC_EnableIRQ(UART0_IRQn);

	// reset the Rx state
	//gpsRxReady = RESET;
}
