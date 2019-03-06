#ifndef Clock_hpp
#define Clock_hpp


class Clock
{
public:
	Clock();
	virtual ~Clock();

private:
	Clock(const Clock &);
	Clock & operator=(const Clock &);

public:
	bool start();
	bool stop();

	bool running() const;

	long elapsed_ms() const;


private:
	static long long now();

private:
	long long _start_time;
	long long _stop_time;
};



#endif
