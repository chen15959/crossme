#ifndef Point_h
#define Point_h

#include "def.hpp"

class Board;

//啥都没有
#define VAL_NONE		'-'
//未解谜
#define VAL_UNKNOWN		'?'
//已解谜，是空
#define VAL_EMPTY		'.'


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
	Point(LINE_SIZE row, LINE_SIZE col, Board * board);
	
	//拷贝构造
	Point(const Point & other);
	//析构
	virtual ~Point();
	
	//赋值运算符重载
	Point & operator=(const Point & rhs);
	
public:
	//点在哪行（0开始）
	inline
	LINE_SIZE getRow() const {
		return this->_row;
	}

	inline
	LINE_SIZE row() const {
		return this->_row;
	}
	
	//点在哪列（0开始）
	inline
	LINE_SIZE getCol() const {
		return this->_col;
	}

	inline
	LINE_SIZE col() const {
		return this->_col;
	}
	
	//获得点的值
	inline
	VALUE_T getValue() const {
		return this->_value;
	}

	inline
	VALUE_T value() const {
		return this->_value;
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
	LINE_SIZE		_row;
	//列（0开始）
	LINE_SIZE		_col;
	//值
	VALUE_T		_value;
	//所属的board
	Board *			_board;
	
};


#endif

