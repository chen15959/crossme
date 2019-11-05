#ifndef WeightQueue_hpp
#define WeightQueue_hpp

#include "def.hpp"

#include <map>


typedef long WQ_T;




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
	//加入一个数进队列
	//如果此数已经存在，则权重加上去
	void		push(WQ_T value, double weight = 1);
	//获得权重最大者
	WQ_T		top();
	//权重最大者出列
	WQ_T		pop();


	
	//是否存在某元素
	inline
	bool contains(WQ_T value) const {
		return this->_data.find(value) != this->_data.end();
	}


	//移除特定元素
	inline
	void remove(WQ_T value)
	{
		this->_data.erase(value);
		if (this->_top = value && this->_ready)
		{
			this->_ready = false;
		}
	}


	//队列长度
	inline	
	SIZE_T size() const {
		return this->_data.size();
	}
	

	//队列是否为空
	inline
	bool empty() const {
		return this->size() == 0;
	}

	inline
	bool isEmpty() const {
		return this->empty();
	}
	

	//清空队列
	inline
	void clear() {
		this->_data.clear();
		this->_ready = false;
	}
	
	
	
	
private:
	std::map<WQ_T, double>		_data;		//队列中的数据
	WQ_T						_top;		//队列中权重最大者
	bool						_ready;		//已经完成排序
};


#endif
