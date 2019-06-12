#include "Param.hpp"

#include <assert.h>




Param::Param(short size, VALUE_T type)
: _type(type), _size(size)
{
}



Param::Param(const Param & other)
: _type(other._type), _size(other._size)
{
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
