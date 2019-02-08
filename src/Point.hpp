#ifndef Point_h
#define Point_h

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
	Point(unsigned long row, unsigned long col, Board * board);
	
	//拷贝构造
	Point(const Point & other);
	//析构
	virtual ~Point();
	
	//赋值运算符重载
	Point & operator=(const Point & rhs);
	
public:
	//点在哪行（0开始）
	inline
	unsigned long getRow() const
	{
		return this->_row;
	}
	
	//点在哪列（0开始）
	inline
	unsigned long getCol() const
	{
		return this->_col;
	}
	
	//获得点的值
	inline
	char getValue() const 
	{
		return this->_value;
	}
	
	//设置点为空
	inline
	bool setEmpty()
	{
		return setValue(VAL_EMPTY);
	}
	
	//设置点的值
	bool setValue(char value);
	
	
	//该点是否已经确定
	inline
	bool isDone() const {
		return (_value != VAL_UNKNOWN && _value != VAL_NONE);
	}
	
	
	
private:
	//行（0开始）
	unsigned long	_row;
	//列（0开始）
	unsigned long	_col;
	//值
	char	    	_value;
	//所属的board
	Board *		    _board;
	
};


#endif

