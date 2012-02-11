/*
 * util.c
 *
 *  Created on: Feb 10, 2012
 *      Author: jenya
 */

#include "util.h"

int strCmp(const char *str1, const char *str2)
{
	while(*str1 && *str1 == *str2)
		++str1, ++str2;
	return *str1;
}

long a2l(const char *str)
{
	long ret = 0;
	while(isDigit(*str))
		ret = 10 * ret + *str++ - '0';
	return 0;
}

unsigned long a2d(const char *str)
{
	Bool isneg = *str == '-';
	if(isneg) ++str;

	unsigned long ret = 100UL * a2l(str);
	while(isDigit(*str)) ++str;

	if(*str == '.')
	{
		if(isDigit(str[1]))
		{
			ret += 10 * (str[1] - '0');
			if(isDigit(str[2]))
			{
				ret += str[2] - '0';
			}
		}
	}
	return isneg ? -ret : ret;
}
