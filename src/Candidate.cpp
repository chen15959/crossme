﻿#include "Candidate.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>




Candidate::Candidate(const VALUE_T * data, LENGTH_T length)
{
	assert(length > 0);
	assert(data);

	_length = length;
	_data = new VALUE_T[_length + 1];
	memcpy(_data, data, _length * sizeof(VALUE_T));
	_data[_length] = '\0';
	
}



Candidate::Candidate(LENGTH_T length, VALUE_T value)
{
	assert(length > 0);

	_length = length;
	_data = new VALUE_T[_length + 1];

	if (sizeof(VALUE_T) == 1)
	{
		memset(_data, value, _length * sizeof(VALUE_T));
	}
	else 
	{
		for (int i = 0; i < _length; ++i)
		{
			_data[i] = value;
		}
	}

	_data[_length] = '\0';
}



Candidate::Candidate(const Candidate & other)
{
	copy(other);
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
	
	_data = new VALUE_T[_length + 1];
	memcpy(_data, other._data, (_length + 1) * sizeof(VALUE_T));
}


void Candidate::free()
{
	delete [] _data;
}



VALUE_T Candidate::value(LENGTH_T pos) const
{
	assert(pos >= 0 && pos < _length);
	
	return _data[pos];
}


LENGTH_T Candidate::length() const
{
	return _length;
}





/*
bool Candidate::operator==(const Line & rhs) const
{
	assert(_length == rhs.length());

	for (int i = 0; i < _length; ++i)
	{
		VALUE_T value = rhs.getPoint(i)->value();
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
*/

