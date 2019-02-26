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
