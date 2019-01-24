/*
棋盘
*/
#ifndef Board_hpp
#define Board_hpp

#include "Param.hpp"
#include "Point.hpp"
//#include "Line.hpp"



class Board
{
public:
	//构造函数
	//列数*行数
	Board(int col_size, int row_size);
	//拷贝构造
	Board(const Board &);
	//析构
	~Board();
	
	//赋值运算符
	Board & operator=(const Board &);
	
private:
	//释放资源
	void free();
	//复制内容
	void copy(const Board &);
	
		
public:
	//使用参数来初始化
	void install(const ParamsOfLines & col_params, const ParamsOfLines & row_params);
	
	//强行设定某Point
	void install(int row, int col, char value);
		
public:
	//获得特定位置的点的值
	char getValue(int row, int col) const;
#if 0
	//忽略不做
	int getPointRound(int row, int col) const;
#endif
	
public:
#if 0	
	inline
	int getRowSize() const
	{
		return this->row_size;
	}
	
	inline
	int getColSize() const
	{
		return this->col_size;
	}
#endif
	
private:
	//列数
	int			_col_size;
	//行数
	int			_row_size;
	
	//所有Point
	Point **	_points;

		
	//从行列号获得点的实际位置
	inline
	int getIndex(int row, int col) const
	{
		return row * this->_col_size + col;
	}
};


#endif
