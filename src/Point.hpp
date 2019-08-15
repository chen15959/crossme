#ifndef Point_h
#define Point_h

#include "def.hpp"

class Board;




//棋盘上的一个点
//解谜场景：
//初始化的时候每个点都是不确定的（?）
//解完后每个点都有一个确定的值（A ~ Z）(单色模式下，只有A值)
//或者空（.）
//每个点都记录着自己被解出的信息
//
class Point
{
public:
	//构造 带自己的位置
	Point(LENGTH_T row, LENGTH_T col, Board * board);
	
	//拷贝构造
	Point(const Point & other);
	//析构
	virtual ~Point();
	
	//赋值运算符重载
	Point & operator=(const Point & rhs);
	
public:
	//点在哪行（0开始）
#if 0
	inline
	LENGTH_T getRow() const {
		return this->row();
	}
#endif

	inline
	LENGTH_T row() const {
		return _row;
	}
	
	//点在哪列（0开始）
#if 0
	inline
	LENGTH_T getCol() const {
		return this->col();
	}
#endif

	inline
	LENGTH_T col() const {
		return _col;
	}
	
	//获得点的值
#if 0
	inline
	VALUE_T getValue() const {
		return this->value();
	}
#endif

	inline
	VALUE_T value() const {
		return _value;
	}
	
	//设置点为空
	inline
	bool setEmpty() {
		return setValue(VAL_EMPTY);
	}
	
	//设置点的值
	bool setValue(VALUE_T value);
	
	
	//该点是否已经确定
	inline
	bool isDone() const {
		return (_value != VAL_UNKNOWN && _value != VAL_NONE);
	}
	
	
	
private:
	//行（0开始）
	LENGTH_T		_row;
	//列（0开始）
	LENGTH_T		_col;
	//值
	VALUE_T			_value;
	//所属的board
	Board *			_board;
	
};


#endif

