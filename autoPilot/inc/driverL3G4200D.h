/*
 * driverL3G4200D.h
 *
 *  Created on: Feb 21, 2012
 *      Author: Trevor
 */

#ifndef DRIVERL3G4200D_H_
#define DRIVERL3G4200D_H_

#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_i2c.h"
#include "driverMEMs.h"

#define L3G4200D_ADDRESS                        0xD0
#define L3G4200D_AUTO_INC                       0x80
#define L3G4200D_CTRL_REG1                      0x20
#define L3G4200D_CTRL_REG2                      0x21
#define L3G4200D_CTRL_REG3                      0x22
#define L3G4200D_CTRL_REG4                      0x23
#define L3G4200D_CTRL_REG5                      0x24
#define L3G4200D_REFERENCE                      0x25
#define L3G4200D_STATUS_REG                     0x27
#define L3G4200D_INT1_CFG                       0x30
#define L3G4200D_INT1_SRC                       0x31
#define L3G4200D_INT1_THS_XH					0x32
#define L3G4200D_INT1_THS_XL					0x33
#define L3G4200D_INT1_THS_YH					0x34
#define L3G4200D_INT1_THS_YL					0x35
#define L3G4200D_INT1_THS_ZH					0x36
#define L3G4200D_INT1_THS_ZL					0x37
#define L3G4200D_INT1_DURATION                  0x38
#define L3G4200D_FIFO_CTRL_REG                  0x2E
#define L3G4200D_READ_REG                       0xA6
#define L3G4200D_FIFO_SRC_REG                   0x2F

typedef struct _gyro_data
{
  short sAngle_x;
  short sAngle_y;
  short sAngle_z;
  char sTemperature;
  char status;
} gyro_data;

gyro_data L3G4200D_GetData();
//void L3G4200D_ReadData(Twid *twid);
extern void L3G4200D_Init(void);
extern int L3G4200D_ClearInt(void);
extern int L3G4200D_GetStatus(void);
//void L3G4200D_StreamMode(Twid *twid);
//void L3G4200D_Reset(Twid *twid);
//void L3G4200D_Calibrate(Twid *twid);

#endif /* DRIVERL3G4200D_H_ */
