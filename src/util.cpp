#include "util.hpp"

#include <math.h>


#define PI	3.1416
#define E	2.718



double factorial_stirling(unsigned long n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		double a = n / E;
		double r = sqrt(2 * PI * n);
		
		for (int i = 0; i < n; ++i)
		{
			r *= a;
		}
		
		return r;
	}
}




long zip(short a, short b)
{
	short v[2];
	v[0] = a;
	v[1] = b;
	return *((long *)v);
}


void unzip(long zip, short & a, short & b)
{
	short * v = (short *)(&zip);
	a = v[0];
	b = v[1];
}
