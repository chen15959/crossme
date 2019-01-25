/*
棋盘上的一个点
	解谜场景：
	初始化的时候每个点都是不确定的（?）
	解完后每个点都有一个确定的值（A ~ Z）(单色模式下，只有A值)
	或者空（.）
	每个点都记录着自己被解出的信息
*/
#ifndef Point_h
#define Point_h

class Board;

//未解谜
#define VAL_UNKNOWN	 '?'
//已解谜，是空
#define VAL_EMPTY	 '.'


//点类
class Point
{
public:
	//构造 带自己的位置
	Point(int row, int col, Board * board);
	
	//拷贝构造
	Point(const Point & other);
	//析构
	virtual ~Point();
	
	//赋值运算符重载
	Point & operator=(const Point & rhs);
	
public:
	//点在哪行（0开始）
	inline
	int getRow() const {
		return this->_row;
	}
	
	//点在哪列（0开始）
	inline
	int getCol() const {
		return this->_col;
	}
	
	//获得点的值
	inline
	char getValue() const {
		return this->_value;
	}
	
	//设置点为空
	inline
	int setEmpty() {
		return setValue(VAL_EMPTY);
	}
	
	//设置点的值
	int setValue(char value);
	
	
	//该点是否已经确定
	inline
	bool isDone() const {
		return (_value != VAL_UNKNOWN);
	}
	
	
	
private:
	//行（0开始）
	int			_row;
	//列（0开始）
	int			_col;
	//值
	char		_value;
	//所属的board
	Board *		_board;
	
};


#endif

