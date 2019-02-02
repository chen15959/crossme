#include "Candidate.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>




Candidate::Candidate(size_t length, const char * data)
{
	assert(length > 0);
	assert(data);

	_length = length;
	_data = new char[_length + 1];
	memcpy(_data, data, _length);
	_data[_length] = '\0';
	
}



Candidate::Candidate(size_t length, char value)
{
	assert(length > 0);

	_length = length;
	_data = new char[_length + 1];
	memset(_data, value, _length);
	_data[_length] = '\0';
}



Candidate::Candidate(const Candidate & other)
{
	this->copy(other);
}



Candidate::~Candidate()
{
	free();
}



Candidate & Candidate::operator=(const Candidate & rhs)
{
	if (&rhs != this)
	{
		free();
		copy(rhs);
	}

	return *this;
}



void Candidate::copy(const Candidate & other)
{
	_length = other._length;
	
	_data = new char[_length + 1];
	memcpy(_data, other._data, _length + 1);
}


void Candidate::free()
{
	delete [] _data;
}



char Candidate::getValue(int pos) const
{
	assert(pos >= 0 && pos < _length);
	
	return _data[pos];
}



Candidate & Candidate::operator+=(const Candidate & rhs)
{
	assert(_length == rhs._length);

	for (int i = 0; i < _length; ++i)
	{
		if (_data[i] == VAL_NONE)
		{
			_data[i] = rhs._data[i];
		}
		else if (_data[i] != rhs._data[i])
		{
			_data[i] = VAL_UNKNOWN;
		}
	}

	return *this;
}
	


Candidate Candidate::operator+(const Candidate & rhs) const
{
	Candidate ret(*this);
	ret += rhs;
	return ret;
}



bool Candidate::operator==(const Line & rhs) const
{
	assert(_length == rhs.getLength());

	for (int i = 0; i < _length; ++i)
	{
		char value = rhs.getPoint(i)->getValue();
		if (value != VAL_UNKNOWN)
		{
			if (_data[i] != value)
			{
				return false;
			}
		}
	}

	return true;
}



bool Candidate::operator!=(const Line & rhs) const
{
	return !(*this == rhs);
}



bool Candidate::operator==(const Candidate & rhs) const
{
	assert(_length == rhs._length);

	for (int i = 0; i < _length; ++i)
	{
		if (_data[i] != rhs._data[i])
		{
			return false;
		}
	}

	return true;
}



bool Candidate::operator!=(const Candidate & rhs) const
{
	return !(*this == rhs);
}



