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

long a2l(uint8_t *str)
{
	long ret = 0;
	while(ISDIGIT(*str))
		ret = 10 * ret + *str++ - '0';
	return 0;
}

double a2d(uint8_t *addr)
{
	double number;
	int negative;
	int exponent;
	int n;
	uint8_t *p = addr;
	double p10;
	int num_digits;
	int num_decimals;

	negative = 0;
	// find out if it is a negative value
	switch (*p)
	{
	case '-': negative = 1; // fall through
	case '+': p++;
	}

	number = 0;
	exponent = 0;
	num_digits = 0;
	num_decimals = 0;

	// take of the whole number (before decimal point)
	while(ISDIGIT(*p))
	{
		number = number * 10 + (*p - '0');
		p++;
		num_digits++;
	}

	// if there is a decimal point
	if(*p == '.')
	{
		p++;

		while(ISDIGIT(*p))
		{
			number = number * 10 + (*p - '0');
			p++;
			num_digits++;
			num_decimals++;
		}
		exponent = -num_decimals;
	}

	if(num_digits == 0)
	{
		return 0.0;
	}

	// take care of negative sign
	if(negative) number = -negative;

	// take of the decimals
	p10 = 10;
	n = exponent;
	if(n < 0) n = -n;
	while(n)
	{
		if(n & 1)
		{
			if(exponent < 0)
				number /= p10;
			else
				number *= p10;
		}
		n >>= 1;
		p10 *= p10;
	}
	return number;
}
