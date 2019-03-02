#include "Line.hpp"

#include <assert.h>



CandidateFactory Line::__candidateFactory;



Line::Line(short length)
{
	assert(length > 0);
	
	_length = length;
	_points = new Point*[_length];
	_candidates = NULL;
}



Line::Line(const Line & other)
{
	//不支持
	assert(0);
	copy(other);
}



Line::~Line()
{
	free();
}



Line & Line::operator=(const Line & rhs)
{
	//不支持
	assert(0);
	if (&rhs != this)
	{
		free();
		copy(rhs);
	}
	
	return *this;
}



void Line::copy(const Line & other)
{
	assert(0);
#if 0
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
#endif
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
	else
	{
		_candidates = NULL;
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



const Point * Line::getPoint(short pos) const
{
	assert(0 <= pos && pos < _length);
	
	return _points[pos];
}



void Line::setPoint(Point * point, short pos)
{
	assert(0 <= pos && pos < _length);
	
	_points[pos] = point;
}



double Line::install(const ParamsOfLine & params)
{
	assert(params.size() > 0);
	assert(_candidates == NULL);

	_candidates = __candidateFactory.createCandidateList(_length, params, NULL);

	if (_candidates->isError())
	{
		return -1;
	}
	else
	{
		return _candidates->size();
	}
}



int Line::play()
{
	assert(_candidates);

	_candidates->ruleBy(*this);
	int updated = setByCandidates();
	if (_candidates->isError())
	{
		return -1;
	}
	else
	{
		return updated;
	}
}



int Line::setByCandidates()
{
	assert(_candidates);

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


/*
WeightQueue Line::getCandidateValue(short pos) const
{
	assert(_candidates);
	assert(pos < _length);

	return _candidates->values(pos);
}
*/

void Line::getValues(short pos, WeightQueue & result) const
{
	assert(_candidates);
	assert(0 <= pos && pos < _length);

	_candidates->getValues(pos, result);

}