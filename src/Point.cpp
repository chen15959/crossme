#include "Point.hpp"

#include "Board.hpp"




Point::Point(LINE_SIZE row, LINE_SIZE col, Board * board)
: _row(row), _col(col), _value(VAL_UNKNOWN), _board(board)
{
}



Point::Point(const Point & other)
: _row(other._row), _col(other._col), _value(other._value), _board(other._board)
{
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
bool Point::setValue(VALUE_T value)
{
	VALUE_T old_value = this->_value;
	this->_value = value;
	
	if (old_value == VAL_UNKNOWN)
	{
		if (this->_board != NULL)
		{
			this->_board->point_change_callback(this->_row, this->_col, this->_value);
		}
		return true;
	}
	else
	{
		return false;
	}
}
	
