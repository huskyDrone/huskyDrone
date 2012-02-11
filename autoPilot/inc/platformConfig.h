/*
 * platformConfig.h
 *
 *  Created on: Feb 7, 2012
 *      Author: jenya
 */

#ifndef PLATFORMCONFIG_H_
#define PLATFORMCONFIG_H_

#include "lpc17xx_pinsel.h"

        /***************************************************************
         ****************** Registers Bits Definition ******************
         **************************************************************/
/*-------------------------------------------------------------------------------
 * Register Name	:
 * Function			:
 ------------------------------------------------------------------------------*/
#define PLLFEED_FEED1   0x000000AA
#define PLLFEED_FEED2   0x00000055

#define RED_LED ( 1UL << 25UL )

#endif /* PLATFORMCONFIG_H_ */
