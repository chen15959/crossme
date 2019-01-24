#include "Point.hpp"

#include "Board.hpp"




Point::Point(int row, int col, Board * board)
{
	this->_row = row;
	this->_col = col;

	this->_value = VAL_UNKNOWN;
	this->_round = -1;
	
	this->_board = board;
}



Point::Point(const Point & other)
{
	this->_row = other._row;
	this->_col = other._col;
	this->_value = other._value;
	this->_round = other._round;
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
		this->_round = rhs._round;
		this->_board = rhs._board;
	}
	
	return *this;
}


//设置Point的值
//和Board联动
int Point::setValue(char value)
{
	this->_value = value;
    
    if (this->_board)
    {
        this->_board->point_change_callback(this->_row, this->_col, this->_value);
    }

    return 0;
}
	
