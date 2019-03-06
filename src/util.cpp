#include "util.hpp"

#include <math.h>


#define PI	3.1416
#define E	2.718



double factorial_stirling(unsigned long n)
{
	switch (n)
	{
	case 0:
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 6;
	case 4:
		return 24;
	case 5:
		return 120;
	case 6:
		return 720;
	default:
		double a = n / E;
		double r = sqrt(2 * PI * n);
		double e = pow(a, (double)n);
		
		return r * e;
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
