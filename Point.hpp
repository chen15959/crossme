//
//	Point.hpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#ifndef Point_h
#define Point_h


#define VAL_UNKNOWN	 '?'
#define VAL_NOTHING	 '.'


class Point
{
public:
	Point(int row, int col);
	Point(const Point & other);
	~Point();
	
	Point & operator=(const Point & rhs);
	
public:
	inline
	int getRow() const {
		return this->_row;
	}
	
	inline
	int getCol() const {
		return this->_col;
	}
	
	inline
	char getVal() const {
		return this->_val;
	}
	
	inline
	void setVal(char ch) {
		this->_val = ch;
	}
	
	inline
	int getRound() const {
		return this->_round;
	}
	
	inline
	void setRound(int v) {
		this->_round = v;
	}
	
	
	
	
	
private:
	int _row;
	int _col;
	char _val;
	int _round;
	
};


#endif /* Point_h */

