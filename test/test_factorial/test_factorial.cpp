// test_factorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

#define PI	3.1415926535
#define E	2.7182818


double factorial_stirling1(unsigned long n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		double a = n / E;
		double r = sqrt(2 * PI * n);
//		double e = pow(a, n);
		
		for (int i = 0; i < n; ++i)
		{
			r *= a;
		}
		
		return r;
	}
}


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



double factorial_mult(unsigned long n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	else
	{
		double r = 1;
		for (unsigned long i = 2; i <= n; ++i)
		{
			r *= i;
		}

		return r;
	}
}


void compare(unsigned long n)
{
//	double v1 = factorial_stirling1(n);
	double v2 = factorial_stirling(n);
	double v3 = factorial_mult(n);


//	double diff_ab = (v1 - v2) * 2 / (v1 + v2);
	double diff_base = (v2 - v3) * 2 / (v2 + v3);


//	printf("input = %u\tdiff A|B: %f\tdiff: %f\n", n, diff_ab, diff_base);
	printf("input = %u\tdiff: %f\n", n, diff_base);

}


int _tmain(int argc, _TCHAR* argv[])
{
	for (unsigned long i = 0; i < 100; ++i)
	{
		compare(i);
	}

	return 0;
}

