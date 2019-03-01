#include "CandidateList.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

using namespace std;




CandidateList::CandidateList(short length)
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
	
	for (map<int, Candidate *>::const_iterator it1 = _candidates.begin(); it1 != _candidates.end(); ++it1)
	{
		if (*(it1->second) != line)
		{
			to_del.push_back(it1->first);
		}
	}
	
	
	for (vector<int>::const_iterator it2 = to_del.begin(); it2 != to_del.end(); ++it2)
	{
		delete _candidates[*it2];
		_candidates.erase(*it2);
	}
	
	return to_del.size() > 0;
}



char CandidateList::getValue(short pos) const
{
//	assert(size() > 0);
	assert(pos >= 0 && pos < _length);

	char retVal = VAL_NONE;
	for (map<int, Candidate *>::const_iterator it1 = _candidates.begin(); it1 != _candidates.end(); ++it1)
	{
		if (retVal == VAL_NONE)
		{
			retVal = it1->second->getValue(pos);
		}
		else
		{
			if (retVal != it1->second->getValue(pos))
			{
				return VAL_UNKNOWN;
			}
		}
	}

	return retVal;
}



std::map<char, int> CandidateList::getCandidateValue(short pos) const
{
//	assert(size() > 0);
	assert(pos >= 0 && pos < _length);

	map<char, int> retVal;

	for (map<int, Candidate *>::const_iterator it1 = _candidates.begin(); it1 != _candidates.end(); ++it1)
	{
		char value = it1->second->getValue(pos);
		if (retVal.find(value) == retVal.end())
		{
			retVal.insert(pair<char, int>(value, 1));
		}
		else
		{
			retVal[value]++;
		}
	}

	return retVal;
}


