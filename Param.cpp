//
//	Param.cpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#include "Param.hpp"
#include <assert.h>


Param::Param(int size, char type)
{
//	assert(size > 0);
	
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
