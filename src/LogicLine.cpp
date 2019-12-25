#include "LogicLine.hpp"

#include <assert.h>


LogicLine::LogicLine(LENGTH_T length, const ParamList * params, long id)
:Line(length, params, id)
{
}



LogicLine::~LogicLine()
{
}


LogicLine::LogicLine(const LogicLine & other)
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

LogicLine & LogicLine::operator=(const LogicLine & other)
{
	//disabled
	assert(0);

	return *this;
}


LogicLine & LogicLine::operator=(const Line & other)
{
	//disabled
	assert(0);

	return *this;
}


int LogicLine::play()
{
	//目前所有逻辑都是基于单色的








	
	//所有内容的最小总长度（包括中间空格）
	LENGTH_T total = this->_params->size() - 1;
	for (ParamList::const_iterator it1 = this->_params->begin(); it1 != this->_params->end(); ++it1)
	{
		total += it1->size();
	}

	if (total > length())
	{
		return -1;
	}

	//刚好填满
	if (total == length())
	{
		LENGTH_T pos = 0;
		for (ParamList::const_iterator it1 = this->_params->begin(); it1 != this->_params->end(); ++it1)
		{
			for (LENGTH_T i = 0; i < it1->size(); ++i)
			{
				this->set(pos++, it1->type());
			}

			if (pos < _length)
			{
				this->set(pos++, VAL_EMPTY);
			}
		}

	}


	return 1;












	//return Line::play();
}