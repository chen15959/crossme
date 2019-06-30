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
	return Line::play();
}