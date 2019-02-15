#ifndef Board_hpp
#define Board_hpp

#include "Param.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "WeightQueue.hpp"



//棋盘
//
class Board
{
public:
	//构造函数
	//列数*行数
	Board(unsigned long col_size, unsigned long row_size);
	//拷贝构造
	Board(const Board &);
	//析构
	virtual ~Board();
	
	//赋值运算符
	Board & operator=(const Board &);
	
private:
	//建立基本的Point矩阵
	void init(unsigned long col_size, unsigned long row_size);
	//释放资源
	void free();
	//复制内容
	void copy(const Board &);
	
		
public:
	//使用参数来初始化
	void install(const ParamsOfLines & col_params, const ParamsOfLines & row_params);
	
	//强行设定某Point
	void install(unsigned long row, unsigned long col, char value);


public:
	//走棋
	//返回true代表能走的都已经走完了
	//返回false代表发现逻辑冲突了
	bool play();


public:
	//是否已经完成
	bool isDone() const;

	//是否已经失败
	bool isError() const;
	
	//随机找一个不确定点，生成多种可能性
	std::vector<Board *> createCandidates() const;


public:
	//获得特定位置的点的值
	char getValue(unsigned long row, unsigned long col) const;
	
	
public:
	void point_change_callback(unsigned long row, unsigned long col, char value);
	
private:
	//列数
	unsigned long				_col_size;
	//行数
	unsigned long				_row_size;
	
	//所有Point
	Point **					_points;

	//所有行/列
	std::map<long, Line *>		_lines;

	WeightQueue					_todo;


private:
	//从行列号获得点的实际位置
	inline
	unsigned long getIndex(unsigned long row, unsigned long col) const
	{
		return row * this->_col_size + col;
	}
	
	inline
	long col_id(long col)
	{
		return -col - 1;
	}

	inline
	long row_id(long row)
	{
		return row + 1;
	}


public:
	inline
	void setOutput(FILE * output)
	{
		this->output = output;
	}


	void write() const;


private:
	FILE * output;


};


#endif
