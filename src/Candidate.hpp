#ifndef Candidate_hpp
#define Candidate_hpp

#include "def.hpp"

class Line;




//行的候选可能
//
class Candidate
{
public:
	//构造函数
	//用数组初始化
	Candidate(LENGTH_T length, const VALUE_T * buffer);

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
	VALUE_T getValue(LENGTH_T pos) const;

	inline
	VALUE_T value(LENGTH_T pos) const {
		return getValue(pos);
	}

	inline
	LENGTH_T getLength() const {
		return _length;
	}

	inline
	LENGTH_T length() const {
		return getLength();
	}
	


public:
	//判断是否和已经存在的Line兼容
	bool operator==(const Line & rhs) const;

	inline
	bool operator!=(const Line & rhs) const {
		return !(*this == rhs);
	}



private:
	//数据内容
	VALUE_T *		_data;
	//数据长度
	LENGTH_T		_length;
};


#endif
