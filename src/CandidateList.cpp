#include "CandidateList.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

using namespace std;




CandidateList::CandidateList()
{
}



CandidateList::CandidateList(const CandidateList & other)
{
	this->copy(other);
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
	for (map<int, Candidate>::const_iterator it1 = other._candidates.begin(); it1 != other._candidates.end(); ++it1)
	{
		this->addCandidate(it1->second);
	}
}



void CandidateList::free()
{
	//do nothing
}



void CandidateList::addCandidate(const Candidate & c)
{
	assert(this->size() == 0 || (this->size() > 0 && c.getLength() == this->_candidates.begin()->second.getLength()));
	
	this->_candidates.insert(pair<int, Candidate>(this->size(), c));
}



bool CandidateList::ruleBy(const Line & line)
{
	vector<int> to_del;
	
	for (map<int, Candidate>::const_iterator it1 = this->_candidates.begin(); it1 != this->_candidates.end(); ++it1)
	{
		assert(line.getLength() == it1->second.getLength());

		for (int i = 0; i < line.getLength(); ++i)
		{
			char value = line.getPoint(i)->getValue();
			if (value != VAL_UNKNOWN)
			{
				if (value != it1->second.getValue(i))
				{
					to_del.push_back(it1->first);
					break;
				}
			}
		}
	}
	
	
	for (vector<int>::const_iterator it2 = to_del.begin(); it2 != to_del.end(); ++it2)
	{
		this->_candidates.erase(*it2);
	}
	
	return to_del.size() > 0;
}



Candidate CandidateList::getDivisor() const
{
	assert(this->size() > 0);
	size_t len = this->_candidates.begin()->second.getLength();
	char * buffer = new char[len];
	
	int a = 0;
	for (map<int, Candidate>::const_iterator it1 = this->_candidates.begin(); it1 != this->_candidates.end(); ++it1)
	{
		for (int i = 0; i < len; ++i)
		{
			if (a == 0)
			{
				buffer[i] = it1->second.getValue(i);
			}
			else
			{
				if (buffer[i] != it1->second.getValue(i))
				{
					buffer[i] = VAL_UNKNOWN;
				}
			}
		}
		a++;
	}

	Candidate retVal(buffer, len);
	delete [] buffer;
	
	return retVal;
}
	


/*
char Candidate::getValue(int i) const
{
	assert(i >= 0 && i < this->_length);
	
	return this->_data[i];
}



Candidate & Candidate::operator+=(const Candidate & rhs)
{
	assert(this->_length == rhs._length);

	for (int i = 0; i < this->_length; ++i)
	{
		if (this->_data[i] != rhs._data[i])
		{
			this->_data[i] = VAL_UNKNOWN;
		}
	}

	return *this;
}
	


Candidate Candidate::operator+(const Candidate & rhs) const
{
	Candidate ret(*this);
	ret += rhs;
	return ret;
}



bool Candidate::operator==(const Line & rhs) const
{
	assert(this->_length == rhs.getLength());

	for (int i = 0; i < this->_length; ++i)
	{
		char value = rhs.getPoint(i)->getValue();
		if (value != VAL_UNKNOWN)
		{
			if (this->_data[i] != value)
			{
				return false;
			}
		}
	}

	return true;
}



bool Candidate::operator!=(const Line & rhs) const
{
	return !(*this == rhs);
}



bool Candidate::operator==(const Candidate & rhs) const
{
	assert(this->_length == rhs._length);

	for (int i = 0; i < this->_length; ++i)
	{
		if (this->_data[i] != rhs._data[i])
		{
			return false;
		}
	}

	return true;
}



bool Candidate::operator!=(const Candidate & rhs) const
{
	return !(*this == rhs);
}



*/
