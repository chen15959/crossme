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
//基类 不包括算法
//
class Line
{
public:
	//构造函数
	//	行的长度
	//	参数列表
	//	id 可选
	//	类型 内部
	Line(LENGTH_T length, const ParamList * params, long id = 0, long type=0);
private:
	//拷贝构造
	//	禁用
	Line(const Line &);
public:
	//析构函数
	virtual ~Line();
private:
	//赋值运算符
	//	禁用
	Line & operator=(const Line &);
	
public:
	//从另一个Line复制他的数据
	//	应当是同一类型的Line才行
	virtual
	void copyData(const Line *) = 0;


public:
	//获得一个行中的点
	const Point * getPoint(LENGTH_T pos) const;

	//将点赋给行
	//	仅在初始化Board时由Board调用
	void setPoint(Point * point, LENGTH_T pos);

	//获得某个点位上的所有可能值
	virtual
	bool getValues(LENGTH_T pos, WeightQueue &) const = 0;




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
	virtual
	double install(const ParamList & params);

	//开始计算
	//	>0	这次确定了几个Point的值
	//	=0	这次没能确定任何Point的值
	//	<0	发生了错误
	virtual int play();



protected:
	int set(LENGTH_T pos, VALUE_T value);


public:
	//是否已经完成全部分析
	virtual
	bool isDone() const = 0;

	//是否产生逻辑错
	virtual
	bool isError() const = 0;
	
	
protected:
	//所有点
	Point **								_points;
	//行的长度	
	LENGTH_T								_length;
	//输入参数
	const ParamList *						_params;

private:
	long									_id;
	long									_type;


public:
	inline
		long type()const {
			return _type;}

};

#endif
