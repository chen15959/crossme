#include "Point.hpp"


Point::Point(int row, int col)
{
	this->_row = row;
	this->_col = col;
	this->_val = VAL_UNKNOWN;
	this->_round = -1;
}


Point::Point(const Point & other)
{
	this->_row = other._row;
	this->_col = other._col;
	this->_val = other._val;
	this->_round = other._round;
}


Point::~Point()
{
	// do nothing
}


Point & Point::operator=(const Point &rhs)
{
	if (&rhs != this)
	{
		this->_row = rhs._row;
		this->_col = rhs._col;
		this->_val = rhs._val;
		this->_round = rhs._round;
	}
	
	return *this;
}
