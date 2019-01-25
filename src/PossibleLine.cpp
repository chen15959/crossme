//
//	PossibleLine.cpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/20.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#include "PossibleLine.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>



PossibleLine::PossibleLine(const char * data, int length)
{
	assert(length >= 0);

	this->_length = length;
	
	if (this->_length > 0)
	{
		this->_data = new char[this->_length];
		memcpy(this->_data, data, this->_length);
	}
	else
	{
		this->_data = NULL;
	}
}



PossibleLine::PossibleLine(const PossibleLine & other)
{
	this->copy(other);
}



PossibleLine::~PossibleLine()
{
	free();
}



PossibleLine & PossibleLine::operator=(const PossibleLine & rhs)
{
	if (&rhs != this)
	{
		free();
		copy(rhs);
	}

	return *this;
}



void PossibleLine::copy(const PossibleLine & other)
{
	this->_length = other._length;
	
	if (this->_length > 0)
	{
		this->_data = new char[this->_length];
		memcpy(this->_data, other._data, this->_length);
	}
	else
	{
		this->_data = NULL;
	}
}


void PossibleLine::free()
{
	if (this->_length > 0)
	{
		delete [] this->_data;
	}
}



char PossibleLine::getValue(int i) const
{
	assert(i >= 0 && i < this->_length);
	
	return this->_data[i];
}



PossibleLine & PossibleLine::operator+=(const PossibleLine & rhs)
{
	assert(this->_length == rhs._length);

	for (int i = 0; i < this->_length; ++i)
	{
		if (this->_data[i] != rhs._data[i])
		{
			this->_data[i] = VAL_UNKNOWN;
		}
	}

	return *this;
}
	


PossibleLine PossibleLine::operator+(const PossibleLine & rhs) const
{
	PossibleLine ret(*this);
	ret += rhs;
	return ret;
}



bool PossibleLine::operator==(const Line & rhs) const
{
	assert(this->_length == rhs.getLength());

	for (int i = 0; i < this->_length; ++i)
	{
		char value = rhs.getPoint(i)->getValue();
		if (value != VAL_UNKNOWN)
		{
			if (this->_data[i] != value)
			{
				return false;
			}
		}
	}

	return true;
}



bool PossibleLine::operator!=(const Line & rhs) const
{
	return !(*this == rhs);
}



bool PossibleLine::operator==(const PossibleLine & rhs) const
{
	assert(this->_length == rhs._length);

	for (int i = 0; i < this->_length; ++i)
	{
		if (this->_data[i] != rhs._data[i])
		{
			return false;
		}
	}

	return true;
}



bool PossibleLine::operator!=(const PossibleLine & rhs) const
{
	return !(*this == rhs);
}



