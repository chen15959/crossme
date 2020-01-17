#ifndef Matrix_hpp
#define Matrix_hpp

#include "def.hpp"

#include <string>
#include <vector>
#include <stdio.h>


#if 0
template<class T>
class Matrix
{
public:
	//构造
	Matrix(void);

	//拷贝构造
	Matrix(const Matrix & other)
		: _id(other._id), _col_size(other._col_size), _row_size(other._row_size)
	{
		for (std::vector<T>::const_iterator it1 = other._data.begin(); it1 != other._data.end(); ++it1)
		{
			_data.push_back(T(*it1));
		}
	}


	//赋值运算
	Matrix & operator=(const Matrix &);

	//析构
	virtual ~Matrix();


private:
	void copy(const Matrix & other)
	{
//		_data = new T[_row_size * _col_size];
//		for (LENGTH_T r = 0; r < _row_size; ++r)
//		{
//			for (LENGTH_T c = 0; c < _col_size; ++c)
//			{
//				_data[_index(r, c)] = T(other(r,c));
//			}
//		}
	}

	void free()
	{

	}


private:
	std::string		_id;				//名称
	LENGTH_T		_col_size;			//列数
	LENGTH_T		_row_size;			//行数
	std::vector<T>	_data;				//内容（一维数组）
	
public:	
	//获得id
	inline
	std::string id() const {
		return _id;
	}

	//行数量
	inline
	LENGTH_T row_size() const {
		return _row_size;
	}

	//列数量
	inline
	LENGTH_T col_size() const {
		return _col_size;
	}



	//获得某一点
	T value(LENGTH_T row, LENGTH_T col) const;

	//获得某一点
	inline
	T operator()(LENGTH_T row, LENGTH_T col) const {
		return value(row, col);
	}


	
private:
	//获得某一点对应的偏移量
	inline
	LENGTH2_T _index(LENGTH_T row, LENGTH_T col) const {
		return row * col_size() + col;
	}
	
public:
	//将内容输出到output流
	void print(FILE * output);




public:
	

public:


	//输出结果
	//	output		输出到哪个文件流 默认stdout
	//	head		是否输出棋盘标题 默认不输出
	void print(FILE * output = stdout, bool head = false) const;
};










Result::Result(const Board & board)
: _col_size(board.col_size()), _row_size(board.row_size()), _id(board.id())
{
	_data = new VALUE_T[_col_size * _row_size];
	
	for (LENGTH_T c = 0; c < _col_size; ++c)
	{
		for (LENGTH_T r = 0; r < _row_size; ++r)
		{
			_data[_index(r, c)] = board.getValue(r, c);
		}
	}
}



Result::~Result()
{
	free();
}



Result::Result(const Result & other)
{
	copy(other);
}



Result & Result::operator=(const Result & other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}



void Result::copy(const Result & other)
{
	assert(_data == NULL);

	_id = other._id;
	_row_size = other._row_size;
	_col_size = other._col_size;
	
	_data = new VALUE_T[_col_size * _row_size];
	memcpy(_data, other._data, sizeof(VALUE_T) * _col_size * _row_size);
}



void Result::free()
{
	delete [] _data;
	_data = NULL;
}



VALUE_T Result::value(LENGTH_T row, LENGTH_T col) const
{
	assert(0 <= row && row < _row_size);
	assert(0 <= col && col < _col_size);
	
	return _data[_index(row, col)];
}



void Result::print(FILE *output)
{
	//输出标题（若有）
	if (_id.length() > 0)
	{
		fprintf(output, "-= %s =-\n", _id.c_str());
	}
	
	//5行*5列为一小组
	for (LENGTH_T row = 0; row < _row_size; ++row)
	{
		if (row % 5 == 0)
		{
			fprintf(output, "\n");
		}
			
		for (LENGTH_T col = 0; col < _col_size; ++col)
		{
			if (col % 5 == 0 && col > 0)
			{
				fprintf(output, " ");
			}
			fprintf(output, "%c", value(row, col));
		}
		
		fprintf(output, "\n");
	}
		
	fprintf(output, "\n\n");
}





#endif









#endif




/*
class Board
{
public:
	//构造函数
	Board(const ParamListCollection & col_params, const ParamListCollection & row_params, int log_level, int display_level);
	//拷贝构造
	Board(const Board &);
	//析构
	virtual ~Board();
	
	//赋值运算符
	Board & operator=(const Board &);
	
private:
	//建立基本的Point矩阵和Line列表，并置于初始状态
	void init();

	//释放资源
	void free();
	
	//复制内容
	void copy(const Board &);
	
		
public:
	//使用参数来初始化
//	void install(const ParamListCollection & col_params, const ParamListCollection & row_params);
	
	//强行设定某Point
	void install(LENGTH_T row, LENGTH_T col, VALUE_T value);


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

private:
	//基于某点生成多种可能性
	std::vector<Board *> createCandidates(LENGTH_T row, LENGTH_T col) const;


	

public:
	//点被改变的回调
	void point_change_callback(LENGTH_T row, LENGTH_T col, VALUE_T value);

	
private:
	Point **						_points;				//所有Point

	std::map<long, Line *>			_lines;					//所有行/列
	
	WeightQueue						_todo;					//待分析的行/列

	const ParamListCollection *		_params_of_cols;		//运行列参数
	const ParamListCollection *		_params_of_rows;		//运行行参数


private:
	//从行列号获得点的实际位置
	inline
	LENGTH2_T _index(LENGTH_T row, LENGTH_T col) const {
		return row * col_size() + col;
	}
	
	//归一化行号/列号
	inline
	long _col_id(LENGTH_T col) const {
		return -col - 1;
	}

	//归一化行号/列号
	inline
	long _row_id(LENGTH_T row) const {
		return row + 1;
	}


public:
	
	//行数量
	inline
	LENGTH_T row_size() const {
		return _params_of_rows->size();
	}

	//列数量
	inline
	LENGTH_T col_size() const {
		return _params_of_cols->size();
	}


public:
	//棋盘id
	inline
	const char * id() const {
		return _id.c_str();
	}


	//输出结果
	//	output		输出到哪个文件流 默认stdout
	//	head		是否输出棋盘标题 默认不输出
	void print(FILE * output = stdout, bool head = false) const;


	//日志等级
	inline 
	int log_level() const {
		return _log_level;
	}


	//显示等级
	inline
	int display_level() const {
		return _display_level;
	}

private:
	std::string			_id;					//棋盘id
	int					_log_level;				//日志等级
	int					_display_level;			//显示等级


public:
	//棋盘中有多少确定点
	SIZE_T known() const;




};


#endif


*/

