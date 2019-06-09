#include "WeightQueue.hpp"

#include <assert.h>
#include <float.h>


using namespace std;




WeightQueue::WeightQueue()
: _ready(false)
{
//	_ready = false;
}



WeightQueue::~WeightQueue()
{
}



WeightQueue::WeightQueue(const WeightQueue & other)
{
	copy(other);
}



WeightQueue & WeightQueue::operator=(const WeightQueue & rhs)
{
	if (this != &rhs)
	{
		free();
		copy(rhs);
	}

	return *this;
}


void WeightQueue::copy(const WeightQueue & rhs)
{
	this->_top = rhs._top;
	this->_ready = rhs._ready;

	for (map<WQ_T, double>::const_iterator it = rhs._data.begin(); it != rhs._data.end(); ++it)
	{
		this->_data.insert(pair<WQ_T, double>(it->first, it->second));
	}
}


void WeightQueue::free()
{
	this->_ready = false;
	this->_data.clear();
}





WQ_T WeightQueue::top()
{
	assert(size() > 0);

	if (!this->_ready)
	{
		//遍历寻找最大权重者
		double max_weight = -DBL_MAX;
		WQ_T max_value = 0;

		for (map<WQ_T, double>::const_iterator it = this->_data.begin(); it != this->_data.end(); ++it)
		{
			if (it->second > max_weight)
			{
				max_value = it->first;
				max_weight = it->second;
			}
		}

		this->_top = max_value;
		this->_ready = true;
	}

	return this->_top;
}
	


void WeightQueue::push(WQ_T value, double weight)
{
	if (this->_data.find(value) == this->_data.end())
	{
		this->_data[value] = weight;
	}
	else
	{
		this->_data[value] += weight;
	}
	this->_ready = false;
}



WQ_T WeightQueue::pop()
{
	assert(size() > 0);

	if (!this->_ready)
	{
		top();
	}

	this->_data.erase(this->_top);
	this->_ready = false;

	return this->_top;
}
