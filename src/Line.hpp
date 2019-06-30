#ifndef Line_hpp
#define Line_hpp

#include "Point.hpp"
#include "Param.hpp"
#include "Candidate.hpp"
#include "CandidateList.hpp"
#include "CandidateFactory.hpp"
#include "WeightQueue.hpp"

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
	Line(LENGTH_T length, const ParamList * params, long id = 0);
private:
	//拷贝构造
	//	不应当被调用
	Line(const Line &);
public:
	//析构函数
	virtual ~Line();
private:
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
	//从另一个Line复制他的candidates
	void copyCandidates(const Line &);


public:
	//获得一个行中的点
	const Point * getPoint(LENGTH_T pos) const;

	//将点赋给行
	//	仅在初始化Board时由Board调用
	void setPoint(Point * point, LENGTH_T pos);



	void getValues(LENGTH_T pos, WeightQueue &) const;




	//获得行的长度
	inline
	LENGTH_T getLength() const
	{
		return this->length();
	}

	inline
	LENGTH_T length() const {
		return _length;
	}
	
public:
	//通过参数建立全部可能性
	//返回可能性的数量
	//-1代表出错了
	double install(const ParamList & params);

	//开始计算
	//	>0	这次确定了几个Point的值
	//	=0	这次没能确定任何Point的值
	//	<0	发生了错误
	virtual int play();


private:
	//通过综合所有的可能性，设置实际的值
	//	返回值是确定了几个point的值
	int setByCandidates();



protected:
	int set(LENGTH_T pos, VALUE_T value);


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
	
	
protected:
	//所有点
	Point **								_points;
	//行的长度	
	LENGTH_T								_length;
	//输入参数
	const ParamList *						_params;
private:
	//所有可能性
	CandidateList *							_candidates;


private:
	static CandidateFactory					__candidateFactory;


private:
	long									_id;

};

#endif
