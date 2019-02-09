#ifndef Line_hpp
#define Line_hpp

#include "Point.hpp"
#include "Param.hpp"
#include "Candidate.hpp"
#include "CandidateList.hpp"
#include "CandidateFactory.hpp"

#include <vector>
#include <map>
#include <string>



//棋盘上的一行/列
//
class Line
{
public:
	//构造函数
	//行的长度
	Line(unsigned long len);
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
	void copyCandidates(const Line &);


public:
	//获得一个行中的点
	const Point * getPoint(unsigned long pos) const;
	//将点赋给行
	//在初始化Board时由Board调用
	void setPoint(Point * point, unsigned long pos);

	//获得行的长度
	inline
	unsigned long getLength() const
	{
		return _length;
	}
	
public:
	//通过参数建立全部可能性
	bool install(const ParamsOfLine & params);

	//开始计算
	bool play();


private:
	int setByCandidates();




public:
	//是否已经完成全部分析
	inline
	bool isDone() const
	{
		return _candidates->isDone();
	}

	//是否产生逻辑错
	inline
	bool isError() const
	{
		return _candidates->isError();
	}
	
	
private:
	//所有点
	Point **								_points;
	//行的长度	
	unsigned long							_length;
	//所有可能性
	CandidateList *							_candidates;


private:
	static CandidateFactory					__candidateFactory;

};

#endif
