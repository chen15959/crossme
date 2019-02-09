#include "Line.hpp"

#include <assert.h>



CandidateFactory Line::__candidateFactory;



Line::Line(unsigned long length)
{
	assert(length > 0);
	
	_length = length;
	_points = new Point*[_length];
	_candidates = NULL;
}



Line::Line(const Line & other)
{
	copy(other);
}



Line::~Line()
{
	free();
}



Line & Line::operator=(const Line & rhs)
{
	if (&rhs != this)
	{
		free();
		copy(rhs);
	}
	
	return *this;
}



void Line::copy(const Line & other)
{
	_length = other._length;
	_points = new Point*[_length];

//	for (unsigned long i = 0; i < _length; ++i)
//	{
//		_points[i] = other._points[i];
//	}

	if (other._candidates)
	{
		_candidates = new CandidateList(*(other._candidates));
	}
}


void Line::copyCandidates(const Line & other)
{
	if (_candidates)
	{
		delete _candidates;
	}
	
	if (other._candidates)
	{
		_candidates = new CandidateList(*(other._candidates));
	}
}


void Line::free()
{
	//所有的点从Board删除
	//这里只要删除自己的Point存放区域就可以
	delete [] _points;

	if (_candidates)
	{
		delete _candidates;
	}
}



const Point * Line::getPoint(unsigned long pos) const
{
	assert(pos < _length);
	
	return _points[pos];
}



void Line::setPoint(Point * point, unsigned long pos)
{
	assert(pos < _length);
	
	_points[pos] = point;
}



bool Line::install(const ParamsOfLine & params)
{
	assert(params.size() > 0);

	_candidates = __candidateFactory.createCandidateList(_length, params);

	return !_candidates->isError();
}



bool Line::play()
{
	if (_candidates->ruleBy(*this))
	{
		return setByCandidates() > 0;
	}

	return false;
}



int Line::setByCandidates()
{
	int retVal = 0;

	for (unsigned long i = 0; i < _length; ++i)
	{
		char value = _candidates->getValue(i);
		if (value != VAL_UNKNOWN && value != VAL_NONE)
		{
			retVal += (_points[i]->setValue(value) ? 1 : 0);
		}
	}

	return retVal;
}

