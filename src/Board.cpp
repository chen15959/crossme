#include "Board.hpp"

//#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>




Board::Board(int col_size, int row_size)
{
	assert(col_size > 0);
	assert(row_size > 0);
	
	this->_col_size = col_size;
	this->_row_size = row_size;
	
	//初始化Point空间
	this->_points = (Point **)malloc(this->_col_size * this->_row_size * sizeof(Point *));
	
	for (int r = 0; r < this->_row_size; ++r)
	{
		for (int c = 0; c < this->_col_size; ++c)
		{
			this->_points[this->getIndex(r, c)] = new Point(r, c, this);
		}
	}
}




Board::Board(const Board & other)
{
	this->copy(other);
}



Board::~Board()
{
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
	this->_points = (Point **)malloc(this->_col_size * this->_row_size * sizeof(Point *));
	
	for (int r = 0; r < this->_row_size; ++r)
	{
		for (int c = 0; c < this->_col_size; ++c)
		{
			int idx = getIndex(r, c);
			this->_points[idx] = new Point(*(other._points[idx]));
		}
	}
}



void Board::free()
{

	//销毁每个Point
	for (int r = 0; r < this->_row_size; ++r)
	{
		for (int c = 0; c < this->_col_size; ++c)
		{
			delete this->_points[this->getIndex(r, c)];
		}
	}
	
	//销毁Point空间
	::free(this->_points);
}



char Board::getValue(int row, int col) const
{
	assert(row >= 0 && row < this->_row_size);
	assert(col >= 0 && col < this->_col_size);
	
	return this->_points[this->getIndex(row, col)]->getValue();
}

#if 0
int Board::getPointRound(int row, int col) const
{
	assert(row >= 0 && row < this->_row_size);
	assert(col >= 0 && col < this->_col_size);
	
	return this->points[getIndex(row, col)]->getRound();
}

#endif



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
void Board::install(int row, int col, char value)
{
	assert(row >= 0 && row < this->_row_size);
	assert(col >= 0 && col < this->_col_size);
	
	this->_points[this->getIndex(row, col)]->setValue(value);
}



