#ifndef Result_hpp
#define Result_hpp

#include "Board.hpp"

#include <stdio.h>



//棋局的结果
//包括输出格式
class Result
{
public:
	//构造
	Result(const Board & board);
	//析构
	virtual ~Result();
	
	//拷贝构造
	Result(const Result & other);
	//赋值运算
	Result & operator=(const Result & other);
	
private:
	void copy(const Result & other);
	void free();
	

private:
	std::string		_id;				//棋局名称
	LENGTH_T		_col_size;			//列数
	LENGTH_T		_row_size;			//行数
	VALUE_T *		_data;				//内容（一维数组）
	
	
public:
	//获得id
	inline
	std::string id() const {
		return _id;
	}

	//获得某一点的值
	VALUE_T value(LENGTH_T row, LENGTH_T col) const;

	//获得某一点的值
	inline
	VALUE_T operator()(LENGTH_T row, LENGTH_T col) const {
		return value(row, col);
	}
	
private:
	//获得某一点对应的偏移量
	inline
	LENGTH2_T _index(LENGTH_T row, LENGTH_T col) const {
		return row * this->_col_size + col;
	}
	
public:
	//将内容输出到output流
	void print(FILE * output);

};

#endif



