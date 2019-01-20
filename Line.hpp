//
//	Line.hpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include "Point.hpp"
#include "Param.hpp"
#include <vector>


//class Point;
class Board;


class Line
{
	friend class Board;
public:
	Line(int len);
	Line(const Line &);
	~Line();
	
	Line & operator=(const Line &);
	
public:
	const Point * getPoint(int pos) const;
	
public:
	bool install(const std::vector<Param> & params);
	
	
private:
	void setPoint(Point * p, int pos);
	
	
private:
	Point **	_points;
	int			_length;
	
};

#endif /* Line_hpp */
