#include "Clock.hpp"

#include <assert.h>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif



Clock::Clock()
: _start_time(-1), _stop_time(-1)
{
}


Clock::~Clock()
{
}


Clock::Clock(const Clock &)
{
	//禁用
	assert(0);
}
	
Clock & Clock::operator=(const Clock &)
{
	//禁用
	assert(0);
	return *this;
}




bool Clock::start()
{
	//已经停止
	//或从未开始
	if ((_start_time > 0 && _stop_time >= _start_time) || (_start_time < 0 && _stop_time < 0))
	{
		_start_time = now();
		return true;
	}
	else
	{
		return false;
	}
}



bool Clock::stop()
{
	if (running())
	{
		_stop_time = now();
		return true;
	}
	else
	{
		return false;
	}
}


bool Clock::running() const
{
	return _start_time > 0 && _stop_time < _start_time;
}


long Clock::elapsed_ms() const
{
	if (_start_time > 0)
	{
		long long t = _stop_time > _start_time ? _stop_time : now();
		return (long)(t - _start_time);
	}
	else
	{
		return -1;
	}
}



long long Clock::now()
{
#ifdef WIN32
	long long ftime;
	SYSTEMTIME stime;

	::GetSystemTime(&stime);
	::SystemTimeToFileTime(&stime, (FILETIME *)&ftime);

	return ftime / 10000;
#else
	//todo
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
#endif
}
