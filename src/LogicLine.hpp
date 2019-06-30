#ifndef LogicLine_hpp
#define LogicLine_hpp


#include "Line.hpp"



class LogicLine : public Line
{
public:
	LogicLine(LENGTH_T length, const ParamList * params, long id = 0);
	~LogicLine();


private:
	LogicLine(const LogicLine & other);
//	LogicLine(const Line & other);

	LogicLine & operator=(const LogicLine & other);
	LogicLine & operator=(const Line & other);



public:
	virtual int play();

};



#endif
