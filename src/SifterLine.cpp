#include "SifterLine.hpp"


#include <assert.h>


CandidateFactory SifterLine::__candidateFactory;




SifterLine::SifterLine(LENGTH_T length, const ParamList * params, long id)
:Line(length, params, id, 1001)
{
	_candidates = NULL;
}



SifterLine::~SifterLine()
{
	if (_candidates)
	{
		delete _candidates;
	}
}


SifterLine::SifterLine(const SifterLine & other)
: Line(-1, other._params, 0)
{
	//disabled
	assert(0);
}

/*
LogicLine::LogicLine(const Line & other)
: Line(-1, other._params, 0)
{
	//disabled
	assert(0);
}
*/

SifterLine & SifterLine::operator=(const SifterLine & other)
{
	//disabled
	assert(0);

	return *this;
}


SifterLine & SifterLine::operator=(const Line & other)
{
	//disabled
	assert(0);

	return *this;
}


int SifterLine::play()
{
	if (_candidates == NULL)
	{
		_candidates = __candidateFactory.createCandidateList(_length, *_params, NULL);
	}

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

	return 0;
}





/*
void SifterLine::copyCandidates(const Line & other)
{
}
*/




double SifterLine::install(const ParamList & params)
{
	assert(params.size() > 0);
	assert(_candidates == NULL);

	return 0.0;
///	return __candidateFactory.evaluateCandidateSize(_length, params, NULL);
}



int SifterLine::setByCandidates()
{
	assert(_candidates);

	int retVal = 0;

	for (LENGTH_T i = 0; i < _length; ++i)
	{
		VALUE_T value = _candidates->getValue(i);
		if (value != VAL_UNKNOWN && value != VAL_NONE)
		{
			retVal += (_points[i]->setValue(value) ? 1 : 0);
		}
	}

	return retVal;
}




bool SifterLine::getValues(LENGTH_T pos, WeightQueue & result) const
{
	assert(0 <= pos && pos < _length);

	if (_candidates)
	{
		_candidates->getValues(pos, result);
		return true;
	}
	else
	{
		return false;
	}
}




	bool SifterLine::isDone() const
	{
		return _candidates->isDone();
	}

	//是否产生逻辑错
	bool SifterLine::isError() const
	{
		return _candidates ? _candidates->isError() : false;
	}


void SifterLine::copyData(const Line * other)
{
	if (_candidates)
	{
		delete _candidates;
	}

	if (other->type() == 1001)
	{
		const SifterLine * o = (const SifterLine *)other;
		if (o->_candidates)
		{
			_candidates = new CandidateList(*(o->_candidates));
			return;
		}
	}

	_candidates = NULL;

}
