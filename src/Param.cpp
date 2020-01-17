#include "Param.hpp"

#include <assert.h>




Param::Param(LENGTH_T size, VALUE_T type)
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
		_type = rhs._type;
		_size = rhs._size;
	}
	
	return *this;
}



LENGTH_T ParamList::countLength(LENGTH_T start) const
{
	LENGTH_T result = (*this)[start].size();
	VALUE_T last = (*this)[start].type();

	for (LENGTH_T i = start + 1; i < size(); ++i)
	{
		result += ((*this)[i].size() + (last == (*this)[i].type() ? 1 : 0));
	}

	return result;
}
