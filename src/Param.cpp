#include "Param.hpp"

#include <assert.h>




Param::Param(int size, char type)
{
	this->_type = type;
	this->_size = size;
}



Param::Param(const Param & other)
{
	this->_type = other._type;
	this->_size = other._size;
}



Param::~Param()
{
	//do nothing
}



Param & Param::operator=(const Param & rhs)
{
	if (&rhs != this)
	{
		this->_type = rhs._type;
		this->_size = rhs._size;
	}
	
	return *this;
}
