/*
 * driverMEMs.h
 *
 *  Created on: Feb 18, 2012
 *      Author: Trevor
 */

#ifndef DRIVERMEMS_H_H
#define DRIVERMEMS_H_H

#include "lpc17xx_i2c.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "driverL3G4200D.h"

extern __IO FlagStatus complete_M;

extern void mems_Init(void);

#endif /* DRIVERMEMS_H_H */
