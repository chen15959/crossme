// test_clock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
	FILETIME ftime;
	SYSTEMTIME stime;

	::GetSystemTime(&stime);
	::SystemTimeToFileTime(&stime, &ftime);
*/


int _tmain(int argc, _TCHAR* argv[])
{
	SYSTEMTIME stime;

	::GetSystemTime(&stime);

	printf("time1: %d s %d ms\n", stime.wSecond, stime.wMilliseconds);

	long long ftime;
	::SystemTimeToFileTime(&stime, (FILETIME *)&ftime);

	printf("ftime of time1: %lld\n", ftime);

	stime.wMilliseconds++;

printf("1 ms passed ...\n");

	printf("time2: %d s %d ms\n", stime.wSecond, stime.wMilliseconds);

	::SystemTimeToFileTime(&stime, (FILETIME *)&ftime);

	printf("ftime of time2: %lld\n", ftime);





	return 0;
}

