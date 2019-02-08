#include "Board.hpp"

//#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>




Board::Board(unsigned long col_size, unsigned long row_size)
{
	assert(col_size > 0);
	assert(row_size > 0);
	
	this->_col_size = col_size;
	this->_row_size = row_size;
	
	//初始化Point空间
	this->_points = new Point*[this->_col_size * this->_row_size];

	for (unsigned long r = 0; r < this->_row_size; ++r)
	{
		for (unsigned long c = 0; c < this->_col_size; ++c)
		{
			Point * point = new Point(r, c, this);
			
			this->_points[this->getIndex(r, c)] = point;
		}
	}
	
	
}




Board::Board(const Board & other)
{
	this->copy(other);
}



Board::~Board()
{
	this->free();
}



Board & Board::operator=(const Board & rhs)
{
	if (&rhs != this)
	{
		//先删掉自己的，再用别人的替代
		this->free();
		this->copy(rhs);
	}
	
	return *this;
}



void Board::copy(const Board & other)
{
	this->_col_size = other._col_size;
	this->_row_size = other._row_size;
	
	//复制Point空间
	this->_points = new Point*[this->_col_size * this->_row_size];
	
	for (unsigned long r = 0; r < this->_row_size; ++r)
	{
		for (unsigned long c = 0; c < this->_col_size; ++c)
		{
			unsigned long idx = getIndex(r, c);
			this->_points[idx] = new Point(*(other._points[idx]));
		}
	}
}



void Board::free()
{

	//销毁每个Point
	for (unsigned long r = 0; r < this->_row_size; ++r)
	{
		for (unsigned long c = 0; c < this->_col_size; ++c)
		{
			delete this->_points[this->getIndex(r, c)];
		}
	}
	
	//销毁Point空间
	delete [] this->_points;
}



//棋局是否已经走完
bool Board::isDone() const
{
	for (unsigned long r = 0; r < this->_row_size; ++r)
	{
		for (unsigned long c = 0; c < this->_col_size; ++c)
		{
			if (this->_points[this->getIndex(r, c)]->getValue() == VAL_UNKNOWN)
			{
				return false;
			}
		}
	}

	return true;
}






char Board::getValue(unsigned long row, unsigned long col) const
{
	assert(row < this->_row_size);
	assert(col < this->_col_size);
	
	return this->_points[this->getIndex(row, col)]->getValue();
}




/*
row_size = 3
col_size = 4

* * * *
* * * *
* * * *

*/

//使用参数来初始化
void Board::install(const ParamsOfLines & col_params, const ParamsOfLines & row_params)
{
	//todo
}



//强行设定某Point
void Board::install(unsigned long row, unsigned long col, char value)
{
	assert(row < this->_row_size);
	assert(col < this->_col_size);
	
	this->_points[this->getIndex(row, col)]->setValue(value);
}



void Board::point_change_callback(unsigned long row, unsigned long col, char value)
{
	//todo
	
}
