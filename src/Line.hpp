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
	//	行的长度
	Line(unsigned long len);
	//拷贝构造
	//	不应当被调用
	Line(const Line &);
	//析构函数
	virtual ~Line();
	
	//赋值运算符
	//	不应当被调用
	Line & operator=(const Line &);
	
private:
	//从另一个Line复制
	//	不应当被调用
	void copy(const Line &);
	//释放资源
	void free();
	
public:
	//从另一个Line复制他的全部可能性
	void copyCandidates(const Line &);


public:
	//获得一个行中的点
	const Point * getPoint(unsigned long pos) const;
	//将点赋给行
	//	仅在初始化Board时由Board调用
	void setPoint(Point * point, unsigned long pos);


	std::map<char, int> getCandidateValue(unsigned long pos) const;




	//获得行的长度
	inline
	unsigned long getLength() const
	{
		return _length;
	}
	
public:
	//通过参数建立全部可能性
	//返回可能性的数量
	//-1代表出错了
	double install(const ParamsOfLine & params);

	//开始计算
	//	>0	这次确定了几个Point的值
	//	=0	这次没能确定任何Point的值
	//	=-1	发生了错误
	int play();


private:
	//通过综合所有的可能性，设置实际的值
	//	返回值是确定了几个point的值
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
	//输入参数
	ParamsOfLine							_params;
	//所有可能性
	CandidateList *							_candidates;


private:
	static CandidateFactory					__candidateFactory;

};

#endif
