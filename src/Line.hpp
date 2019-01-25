/*
棋盘上的一行
 算法主要实现在这里
*/
#ifndef Line_hpp
#define Line_hpp

#include "Point.hpp"
#include "Param.hpp"

//#include "PossibleLine.hpp"

#include <vector>
#include <map>
#include <string>


class Board;




class Line
{
	friend class Board;
public:
	//构造函数
	//行的长度
	Line(int len);
	//拷贝构造
	Line(const Line &);
	//析构函数
	virtual ~Line();
	
	//赋值运算符
	Line & operator=(const Line &);
	
private:
	void copy(const Line &);
	void free();


public:
	//获得一个行中的点
	const Point * getPoint(int pos) const;

	//获得行的长度
	inline
	int getLength() const
	{
		return this->_length;
	}
	
public:
	//通过参数建立全部可能性
	bool install(const std::vector<Param> & params);

#if 0
	//是否已经完成全部分析
	inline
	bool isDone() const
	{
		return this->_possiblities.size() < 2;
	}
#endif
	
private:
	//将点赋给行
	//由Board调用
	void setPoint(Point * point, int pos);
	
#ifdef TODO
	//递归计算可能性树
	void makePossibleTree(char * buffer, int buffer_ptr, const std::vector<Param> & params, int params_ptr);
#endif
private:
	//所有点
	Point **								_points;
	//行的长度	
	int										_length;

#ifdef TODO
	//可能性列表
	std::map<std::string, PossibleLine>		_possiblities;
	
#endif
};

#endif
