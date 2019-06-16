#ifndef Clock_hpp
#define Clock_hpp


//计时器
//精度到
class Clock
{
public:
	//构造
	Clock();
	//析构
	virtual ~Clock();

private:
	Clock(const Clock &);
	Clock & operator=(const Clock &);

public:
	//开始计时
	bool start();
	//停止计时
	bool stop();

	//是否在运行
	bool running() const;

	//计时器读数（毫秒）
	long elapsed_ms() const;


private:
	//获取当前时间
	static long long now();

private:
	//开始时间
	long long _start_time;
	//结束时间
	long long _stop_time;
};



#endif
