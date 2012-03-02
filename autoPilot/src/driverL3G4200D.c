/*
 * driverL3G4200D.c
 *
 *  Created on: Feb 21, 2012
 *      Author: Trevor
 */

#include "driverL3G4200D.h"

#define BUF_LEN 16
unsigned char Write_Buf[BUF_LEN];
unsigned char Read_Buf[BUF_LEN]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
I2C_M_SETUP_Type transferMCfg;

void L3G4200D_Init(void)
{
	complete_M =  RESET; //Reset flag
	Write_Buf[0] = (L3G4200D_CTRL_REG1|L3G4200D_AUTO_INC);
	Write_Buf[1] = 0xF0;   //Turn on, enable X,Y, and Z axis.
	Write_Buf[2] = 0x00;   //HP Filter in normal mode.
	Write_Buf[3] = 0x80;   //Interrupts enabled on INT1 pin.
	Write_Buf[4] = 0x00;   //200dps
	Write_Buf[5] = 0x50;   //FIFO Enabled, HP Filter Enabled.
	Write_Buf[6] = (L3G4200D_INT1_THS_XH|L3G4200D_AUTO_INC);
	Write_Buf[7] = 0x2C;   //Threshold=100dps
	Write_Buf[8] = 0xA4;   //Threshold=100dps
	Write_Buf[9] = 0x2C;   //Threshold=100dps
	Write_Buf[10] = 0xA4;  //Threshold=100dps
	Write_Buf[11] = 0x2C;  //Threshold=100dps
	Write_Buf[12] = 0xA4;  //Threshold=100dps
	Write_Buf[13] = 0x00;  //Duration = 0, interrupt only stays while above threshold
	transferMCfg.sl_addr7bit = L3G4200D_ADDRESS;
	transferMCfg.tx_data = Write_Buf;
	transferMCfg.tx_length = 14;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	/* Wait until complete */
	while (complete_M == RESET);
	/* Dummy read to force the HP filter to current angular rate value
       (i.e. set reference angular rate*/
	complete_M =  RESET; //Reset flag
	Write_Buf[0] = L3G4200D_REFERENCE;
	transferMCfg.sl_addr7bit = L3G4200D_ADDRESS;
	transferMCfg.tx_data = Write_Buf;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = Read_Buf;
	transferMCfg.rx_length = 1;
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	/* Wait until complete */
	while (complete_M == RESET);
	complete_M =  RESET; //Reset flag
	Write_Buf[0] = L3G4200D_INT1_CFG;
	Write_Buf[1] = 0x7F; //XH,XL,YH,YL,ZH,ZL ints all enabled latching OR. Cleared by reading INT1_SRC register.
	transferMCfg.sl_addr7bit = L3G4200D_ADDRESS;
	transferMCfg.tx_data = Write_Buf;
	transferMCfg.tx_length = 2;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_INTERRUPT);
}
int L3G4200D_ClearInt(void)
{	//todo redo this so this transfer doesn't block
	complete_M =  RESET; //Reset flag
	Write_Buf[0] = L3G4200D_INT1_SRC;
	transferMCfg.sl_addr7bit = L3G4200D_ADDRESS;
	transferMCfg.tx_data = Write_Buf;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = Read_Buf;
	transferMCfg.rx_length = 1;
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	/* Wait until complete */
	while (complete_M == RESET);
	return (int)Read_Buf[0];
}
int L3G4200D_GetStatus(void)
{
	complete_M =  RESET; //Reset flag
	Write_Buf[0] = L3G4200D_STATUS_REG;
	transferMCfg.sl_addr7bit = L3G4200D_ADDRESS;
	transferMCfg.tx_data = Write_Buf;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = Read_Buf;
	transferMCfg.rx_length = 1;
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_INTERRUPT);
	/* Wait until complete */
	while (complete_M == RESET);
	return (int)Read_Buf[0];
}
