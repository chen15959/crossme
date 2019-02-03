#include "Point.hpp"

#include "Board.hpp"




Point::Point(int row, int col, Board * board)
{
	this->_row = row;
	this->_col = col;

	this->_value = VAL_UNKNOWN;
	
	this->_board = board;
}



Point::Point(const Point & other)
{
	this->_row = other._row;
	this->_col = other._col;
	this->_value = other._value;
	this->_board = other._board;
}



Point::~Point()
{
	// do nothing
}



Point & Point::operator=(const Point & rhs)
{
	if (&rhs != this)
	{
		this->_row = rhs._row;
		this->_col = rhs._col;
		this->_value = rhs._value;
		this->_board = rhs._board;
	}
	
	return *this;
}



//设置Point的值
//和Board联动
bool Point::setValue(char value)
{
	char old_value = _value;
	_value = value;
	
	if (old_value == VAL_UNKNOWN)
	{
		if (_board != NULL)
		{
			_board->point_change_callback(_row, _col, _value);
		}
		return true;
	}
	else
	{
		return false;
	}
}
	
