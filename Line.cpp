//
//	Line.cpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#include "Line.hpp"
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>



Line::Line(int len)
{
	assert(len > 0);
	
	this->_length = len;

	int mem_size = _length * sizeof(Point *);
	this->_points = (Point **)malloc(mem_size);
	memset(this->_points, 0, mem_size);
}



Line::Line(const Line & other)
{
	this->_length = other._length;
	int mem_size = _length * sizeof(Point *);
	this->_points = (Point **)malloc(mem_size);
	memset(this->_points, 0, mem_size);
}



Line::~Line()
{
	free(_points);
}



Line & Line::operator=(const Line & rhs)
{
	if (&rhs != this)
	{
		if (this->_length < rhs._length)
		{
			free(this->_points);
			
			int mem_size = rhs._length * sizeof(Point *);
			this->_points = (Point **)malloc(mem_size);
			memset(this->_points, 0, mem_size);
		}
		else
		{
			memset(this->_points, 0, _length * sizeof(Point *));
		}
		
		this->_length = rhs._length;
	}
	
	return *this;
}



const Point * Line::getPoint(int pos) const
{
	assert(pos >= 0 && pos <= this->_length);
	
	return this->_points[pos];
}



void Line::setPoint(Point * p, int pos)
{
	assert(pos >= 0 && pos <= this->_length);
	
	this->_points[pos] = p;
}

