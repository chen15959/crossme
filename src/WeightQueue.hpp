#ifndef WeightQueue_hpp
#define WeightQueue_hpp

#include <map>




class WeightQueue
{
public:
	WeightQueue();
	virtual ~WeightQueue();
	
	WeightQueue(const WeightQueue &);
	WeightQueue & operator=(const WeightQueue &);
	
private:
	void copy(const WeightQueue &);
	void free();
	
public:
	long	top();
	void	push(long value, double weight = 1);
	long	pop();



	inline	
	unsigned long	size() const
	{
		return _data.size();
	}
	
	inline
	bool			empty() const
	{
		return size() == 0;
	}
	
	void			clear()
	{
		_data.clear();
	}
	
	
	
	
private:
	std::map<long, double>	_data;
	long					_top;
	bool					_ready;
};


#endif
