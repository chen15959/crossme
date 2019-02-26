#include "Param.hpp"

#include <assert.h>




Param::Param(short size, char type)
{
	_type = type;
	_size = size;
}



Param::Param(const Param & other)
{
	_type = other._type;
	_size = other._size;
}



Param::~Param()
{
	//do nothing
}



Param & Param::operator=(const Param & rhs)
{
	if (&rhs != this)
	{
		_type = rhs._type;
		_size = rhs._size;
	}
	
	return *this;
}
