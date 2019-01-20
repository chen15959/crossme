//
//	Board.cpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#include "Board.hpp"

#include "Point.hpp"
#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>


Board::Board(int col_size, int row_size)
{
	assert(col_size > 0);
	assert(row_size > 0);
	
	this->col_size = col_size;
	this->row_size = row_size;
	
	points = (Point **)malloc(this->col_size * this->row_size * sizeof(Point *));
	
	for (int r = 0; r < this->row_size; ++r)
	{
		for (int c = 0; c < this->col_size; ++c)
		{
			points[getIndex(r, c)] = new Point(r, c);
		}
	}
}




Board::Board(const Board & other)
{
	this->col_size = other.col_size;
	this->row_size = other.row_size;
	
	this->points = (Point **)malloc(this->col_size * this->row_size * sizeof(Point *));
	
	for (int r = 0; r < this->row_size; ++r)
	{
		for (int c = 0; c < this->col_size; ++c)
		{
			int idx = getIndex(r, c);
			points[idx] = new Point(*(other.points[idx]));
		}
	}
}



Board::~Board()
{
	for (int r = 0; r < this->row_size; ++r)
	{
		for (int c = 0; c < this->col_size; ++c)
		{
			delete this->points[getIndex(r, c)];
		}
	}
	free(this->points);
}


Board & Board::operator=(const Board & rhs)
{
	if (&rhs != this)
	{
	
	}
	
	return *this;
}

char Board::getPointVal(int row, int col) const
{
	assert(row >= 0 && row < this->row_size);
	assert(col >= 0 && col < this->col_size);
	
	return this->points[getIndex(row, col)]->getVal();
}


int Board::getPointRound(int row, int col) const
{
	assert(row >= 0 && row < this->row_size);
	assert(col >= 0 && col < this->col_size);
	
	return this->points[getIndex(row, col)]->getRound();
}





/*
row_size = 3
col_size = 4

* * * *
* * * *
* * * *

*/
