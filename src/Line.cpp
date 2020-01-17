#include "Line.hpp"

#include <assert.h>






Line::Line(LENGTH_T length, const ParamList * params, long id, long type)
{
	assert(length > 0);
	
	_length = length;
	_points = new Point*[_length];

	_params = params;
	_id = id;
	_type = type;
}



Line::Line(const Line & other)
{
	//不支持
	assert(0);
}



Line::~Line()
{
	//所有的点从Board删除
	//这里只要删除自己的Point存放区域就可以
	delete [] _points;
}



Line & Line::operator=(const Line & rhs)
{
	//不支持
	assert(0);
	
	return *this;
}



///void Line::copy(const Line & other)
///{
///	assert(0);
///}



///void Line::copyCandidates(const Line & other)
///{
///	if (_candidates)
///	{
///		delete _candidates;
///	}
	
///	if (other._candidates)
///	{
///		_candidates = new CandidateList(*(other._candidates));
///	}
///	else
///	{
///		_candidates = NULL;
///	}
///}




///void Line::free()
///{

///	if (_candidates)
///	{
///		delete _candidates;
///	}
///}



const Point * Line::getPoint(LENGTH_T pos) const
{
	assert(0 <= pos && pos < _length);
	
	return _points[pos];
}



void Line::setPoint(Point * point, LENGTH_T pos)
{
	assert(0 <= pos && pos < _length);
	
	_points[pos] = point;
}



double Line::install(const ParamList & params)
{
	assert(params.size() > 0);
//	assert(_candidates == NULL);

///	_params = &params;
	std::map<VALUE_T, int> t_map;

	for (ParamList::const_iterator it1 = params.begin(); it1 != params.end(); ++it1)
	{
		if (t_map.find(it1->type()) == t_map.end())
		{
			t_map[it1->type()] = 0;

			for (LENGTH_T i = 0; i < length(); ++i)
			{
				_points[i]->set_candidate(it1->type());
			}
		}
	}


	return 0.0;
///	return __candidateFactory.evaluateCandidateSize(_length, params, NULL);
}



int Line::play()
{
///	if (_candidates == NULL)
///	{
///		_candidates = __candidateFactory.createCandidateList(_length, *_params, NULL);
///	}

///	_candidates->ruleBy(*this);
///	int updated = setByCandidates();
///	if (_candidates->isError())
///	{
///		return -1;
///	}
///	else
///	{
///		return updated;
///	}
	return 0;
}



///int Line::setByCandidates()
///{
///	assert(_candidates);
///
///	int retVal = 0;
///
///	for (LENGTH_T i = 0; i < _length; ++i)
///	{
///		VALUE_T value = _candidates->getValue(i);
///		if (value != VAL_UNKNOWN && value != VAL_NONE)
///		{
///			retVal += (_points[i]->setValue(value) ? 1 : 0);
///		}
///	}
///
///	return retVal;
///}



int Line::set(LENGTH_T pos, VALUE_T value)
{
	assert(0 <= pos && pos < _length);

	return _points[pos]->setValue(value);
}



///void Line::getValues(LENGTH_T pos, WeightQueue & result) const
///{
///	assert(_candidates);
///	assert(0 <= pos && pos < _length);
///
///	_candidates->getValues(pos, result);
///
///}


