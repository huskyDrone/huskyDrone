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


// buffer size, will be used as a ring buffer
#define RING_BUF_SIZE    256

// Macros to handle ring buffers
#define __BUF_MASK (RING_BUF_SIZE - 1)
// check if buf is full
#define __BUF_IS_FULL(head, tail) ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
// check buf will be full in next receiving or not
#define __BUF_WILL_FULL(hea, tail) ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
// check if buf is empty
#define __BUF_IS_EMPTY(head, tail) ((head&__BUF_MASK)==(tail&__BUF_MASK))
// reset the buf
#define __BUF_RESET(bufidx) (bufidx=0)
#define __BUF_INCR(bufidx)  (bufidx=(bufidx+1)&__BUF_MASK)


#endif /* PLATFORMCONFIG_H_ */
