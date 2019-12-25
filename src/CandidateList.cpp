#include "CandidateList.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

using namespace std;




CandidateList::CandidateList(LENGTH_T length)
{
	assert(length > 0);

	_length = length;
}



CandidateList::CandidateList(const CandidateList & other)
{
	copy(other);
}



CandidateList::~CandidateList()
{
	free();
}



CandidateList & CandidateList::operator=(const CandidateList & rhs)
{
	if (&rhs != this)
	{
		free();
		copy(rhs);
	}

	return *this;
}



void CandidateList::copy(const CandidateList & other)
{
	_length = other._length;

	for (map<int, Candidate *>::const_iterator it1 = other._candidates.begin(); it1 != other._candidates.end(); ++it1)
	{
		addCandidate(new Candidate(*(it1->second)));
	}
}



void CandidateList::free()
{
	for (map<int, Candidate *>::const_iterator it1 = _candidates.begin(); it1 != _candidates.end(); ++it1)
	{
		delete it1->second;
	}

	_candidates.clear();
}



void CandidateList::addCandidate(Candidate * c)
{
	assert(c->length() == _length);
	
	_candidates.insert(pair<int, Candidate *>(size(), c));
}



bool CandidateList::ruleBy(const Line & line)
{
	vector<int> to_del;
	
	//将和line不符合的可能性标记出来
	for (map<int, Candidate *>::const_iterator it1 = _candidates.begin(); it1 != _candidates.end(); ++it1)
	{
		if (*(it1->second) != line)
		{
			to_del.push_back(it1->first);
		}
	}
	
	//删除这些被标记的
	for (vector<int>::const_iterator it2 = to_del.begin(); it2 != to_del.end(); ++it2)
	{
		delete _candidates[*it2];
		_candidates.erase(*it2);
	}
	
	return to_del.size() > 0;
}



VALUE_T CandidateList::getValue(LENGTH_T pos) const
{
	WeightQueue result;
	
	getValues(pos, result);
	
	if (result.size() == 0)
	{
		return VAL_NONE;
	}
	else if (result.size() == 1)
	{
		return (VALUE_T)result.top();
	}
	else
	{
		return VAL_UNKNOWN;
	}
}





void CandidateList::getValues(LENGTH_T pos, WeightQueue & result) const
{
	assert(pos >= 0 && pos < _length);

	for (map<int, Candidate *>::const_iterator it = _candidates.begin(); it != _candidates.end(); ++it)
	{
		result.push(it->second->value(pos), 1);
	}
}
