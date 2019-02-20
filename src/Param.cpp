#include "Param.hpp"

#include <assert.h>



const Param Param::INVALID(0, VAL_EMPTY);



Param::Param(unsigned long size, char type)
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
