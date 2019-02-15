#include "WeightQueue.hpp"

#include <assert.h>
#include <float.h>


using namespace std;




WeightQueue::WeightQueue()
{
	_ready = false;
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
	_top = rhs._top;
	_ready = rhs._ready;

	for (map<long, double>::const_iterator it = rhs._data.begin(); it != rhs._data.end(); ++it)
	{
		_data.insert(pair<long, double>(it->first, it->second));
	}
}


void WeightQueue::free()
{
	_ready = false;
	_data.clear();
}





long WeightQueue::top()
{
	assert(size() > 0);

	if (!_ready)
	{
		//FIND THE ONE
//		_top = _data.begin()->first;

		double max_weight = -DBL_MAX;
		long max_value = 0;

		for (map<long, double>::const_iterator it = _data.begin(); it != _data.end(); ++it)
		{
			if (it->second > max_weight)
			{
				max_value = it->first;
				max_weight = it->second;
			}
		}

		_top = max_value;
		_ready = true;
	}

	return _top;
}
	


void WeightQueue::push(long value, double weight)
{
	if (_data.find(value) == _data.end())
	{
		_data[value] = weight;
	}
	else
	{
		_data[value] += weight;
	}
}



void WeightQueue::pop()
{
	assert(size() > 0);


	if (!_ready)
	{
		top();
	}

	_data.erase(_top);
	_ready = false;
}
