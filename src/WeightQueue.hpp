#ifndef WeightQueue_hpp
#define WeightQueue_hpp

#include <map>



//权重队列
//依次按权重出列
class WeightQueue
{
public:
	//构造
	WeightQueue();
	//析构
	virtual ~WeightQueue();
	
	//拷贝构造
	WeightQueue(const WeightQueue &);
	//赋值运算符
	WeightQueue & operator=(const WeightQueue &);
	
private:
	//复制
	void copy(const WeightQueue &);
	//释放
	void free();
	
public:
	//获得权重最大者
	long	top();
	//加入一个数进队列
	//如果此数已经存在，则权重加上去
	void	push(long value, double weight = 1);
	//权重最大者出列
	long	pop();


	//队列长度
	inline	
	unsigned long	size() const
	{
		return _data.size();
	}
	
	//队列是否为空
	inline
	bool			empty() const
	{
		return size() == 0;
	}
	
	//清空队列
	void			clear()
	{
		_data.clear();
	}
	
	
	
	
private:
	std::map<long, double>	_data;		//队列中的数据
	long					_top;		//队列中权重最大者
	bool					_ready;		//已经完成排序
};


#endif
