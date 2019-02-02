#include "CandidateList.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

using namespace std;




CandidateList::CandidateList(size_t length)
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
	assert(c->getLength() == _length);
	
	_candidates.insert(pair<int, Candidate *>(size(), c));
}



bool CandidateList::ruleBy(const Line & line)
{
	vector<int> to_del;
	
	for (map<int, Candidate *>::const_iterator it1 = _candidates.begin(); it1 != _candidates.end(); ++it1)
	{
		assert(line.getLength() == it1->second->getLength());

		for (int i = 0; i < line.getLength(); ++i)
		{
			char value = line.getPoint(i)->getValue();
			if (value != VAL_UNKNOWN)
			{
				if (value != it1->second->getValue(i))
				{
					to_del.push_back(it1->first);
					break;
				}
			}
		}
	}
	
	
	for (vector<int>::const_iterator it2 = to_del.begin(); it2 != to_del.end(); ++it2)
	{
		_candidates.erase(*it2);
	}
	
	return to_del.size() > 0;
}



Candidate CandidateList::getDivisor() const
{
	assert(size() > 0);
	size_t len = _candidates.begin()->second->getLength();
	char * buffer = new char[len];
	
	int a = 0;
	for (map<int, Candidate *>::const_iterator it1 = _candidates.begin(); it1 != _candidates.end(); ++it1)
	{
		for (int i = 0; i < len; ++i)
		{
			if (a == 0)
			{
				buffer[i] = it1->second->getValue(i);
			}
			else
			{
				if (buffer[i] != it1->second->getValue(i))
				{
					buffer[i] = VAL_UNKNOWN;
				}
			}
		}
		a++;
	}

	Candidate retVal(len, buffer);
	delete [] buffer;
	
	return retVal;
}
	
