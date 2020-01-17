#include "Point.hpp"

#include "Board.hpp"




Point::Point(LENGTH_T row, LENGTH_T col, Board * board)
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
		_row = rhs._row;
		_col = rhs._col;
		_value = rhs._value;
		_board = rhs._board;
	}
	
	return *this;
}



//设置Point的值
//和Board联动
bool Point::setValue(VALUE_T value)
{
	if (_value == VAL_UNKNOWN)
	{
		//仅当从unknown变为确定值的时候
		_value = value;
		_candidates.clear();

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
	
