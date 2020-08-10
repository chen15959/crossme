#ifndef Candidate_hpp
#define Candidate_hpp

#include "Array.hpp"




//行的候选可能
//
class Candidate : public Array
{
public:
	//构造函数
	//用数组初始化
	Candidate(const VALUE_T * buffer, LENGTH_T length);

	//初始化为全都是一个值
	Candidate(LENGTH_T length, VALUE_T value = '\0');

	//拷贝构造
	Candidate(const Candidate &);
	//析构函数
	virtual ~Candidate();
	//赋值运算符
	Candidate & operator=(const Candidate &);
	
	
private:
	void copy(const Candidate &);
	void free();


public:
	//获得某个位置上的值
	virtual
	VALUE_T value(LENGTH_T pos) const;

	//获得长度
	virtual
	LENGTH_T length() const;


private:
	//数据内容
	VALUE_T *		_data;
	//数据长度
	LENGTH_T		_length;
};


#endif
