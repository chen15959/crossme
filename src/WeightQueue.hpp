#ifndef WeightQueue_hpp
#define WeightQueue_hpp

#include <map>
#include <assert.h>


template<typename T>
class WeightQueue
{
public:
	WeightQueue() {
	}

	virtual ~WeightQueue() {
	}
	
	WeightQueue(const WeightQueue<T> & other) {
		for (typename std::map<T, int>::const_interator it1 = other._data.begin(); it1 != other._data.end(); ++it1) {
			_data.insert(std::pair<T, int>(it1->first, it1->second));
		}
	}
	
	WeightQueue & operator=(const WeightQueue<T> & rhs) {
		if (&rhs != this) {
			_data.clear();
			for (typename std::map<T, int>::const_interator it1 = rhs._data.begin(); it1 != rhs._data.end(); ++it1) {
				_data.insert(std::pair<T, int>(it1->first, it1->second));
			}
		}
		return *this;
	}
	
public:
	void enqueue(const T & element, int weight = 1) {
		if (_data.find(element)!= _data.end()) {
			_data[element] += weight;
		}
		else {
			_data.insert(std::pair<T, int>(element, weight));
			
		}
	}

	T dequeue() {
		assert(size() > 0);
		
		int max_weight = -2147483648;
		typename std::map<T, int>::const_iterator max_ptr = _data.end();
		for (typename std::map<T, int>::const_iterator it = _data.begin(); it != _data.end(); ++it) {
			if (it->second > max_weight) {
				max_weight = it->second;
				max_ptr = it;
			}
		}
		
		T retVal = max_ptr->first;
		_data.erase(max_ptr);
		
		return retVal;
	}
	
	inline unsigned long size() const {
		return _data.size();
	}
	inline bool isEmpty() const {
		return size() == 0;
	}

private:
	std::map<unsigned long, int> _data;
};





#endif

