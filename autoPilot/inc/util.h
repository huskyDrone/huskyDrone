/*
 * util.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jenya
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "lpc_types.h"


          /***************************************************************
          ***************** Command Function Prototypes *****************
          **************************************************************/
/*-------------------------------------------------------------------------------
* Function Name	    : isDigit
* Description		: Checks whether the character is a number
* ASSUMPTIONS		:
* Input			    : c-> a character
* Output			: None
* Return			: True if the character is a number, False otherwise
------------------------------------------------------------------------------*/
Bool isDigit(char c) {return c >= '0' && c <= '9';}

/*-------------------------------------------------------------------------------
* Function Name	    : strCmp
* Description		: Compares the two strings
* ASSUMPTIONS		:
* Input			    : Pointers to two strings will be compared
* Output			: None
* Return			: 0 if the strings are equal, none-zero otherwise
------------------------------------------------------------------------------*/
int strCmp(const char *str1, const char *str2);

/*-------------------------------------------------------------------------------
* Function Name	    : a2l
* Description		: Converts the given string (number) into long
* ASSUMPTIONS		:
* Input			    : Pointer to the string
* Output			: None
* Return			: Number (long)
------------------------------------------------------------------------------*/
long a2l(const char *str);

/*-------------------------------------------------------------------------------
* Function Name	    : a2d
* Description		: Converts the given string (decimal number) into an unsigned
*                     long equivalent.  The last two digits of the return value
*                     correspond to two decimal digits
* ASSUMPTIONS		:
* Input			    : Pointer to the string
* Output			: None
* Return			: Number (unsigned long)
------------------------------------------------------------------------------*/
unsigned long a2d(const char *str);

#endif /* UTIL_H_ */
