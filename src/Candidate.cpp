#include "Candidate.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>



Candidate::Candidate(const char * data, int length)
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


void Candidate::free()
{
	if (this->_length > 0)
	{
		delete [] this->_data;
	}
}



char Candidate::getValue(int i) const
{
	assert(i >= 0 && i < this->_length);
	
	return this->_data[i];
}



Candidate & Candidate::operator+=(const Candidate & rhs)
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
	


Candidate Candidate::operator+(const Candidate & rhs) const
{
	Candidate ret(*this);
	ret += rhs;
	return ret;
}



bool Candidate::operator==(const Line & rhs) const
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



bool Candidate::operator!=(const Line & rhs) const
{
	return !(*this == rhs);
}



bool Candidate::operator==(const Candidate & rhs) const
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



bool Candidate::operator!=(const Candidate & rhs) const
{
	return !(*this == rhs);
}



