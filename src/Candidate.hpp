/*
承载行的可行性

*/
#ifndef Candidate_hpp
#define Candidate_hpp

#include <string>
class Line;



class Candidate
{
public:
	//构造函数
	//用数组初始化
	Candidate(const char * data = NULL, int length = 0);
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
	char getValue(int index) const;
	
	//产生一个摘要
	inline
	std::string getKey() const
	{
		return std::string(this->_data);
	}

public:
	//相当于两个做一次合并，相同的保留原值，不同的记为？
	Candidate & operator+=(const Candidate & rhs);
	Candidate operator+(const Candidate & rhs) const;

	//判断一个是否和已经存在的Line兼容
	bool operator==(const Line &) const;
	bool operator!=(const Line &) const;

	//判断一个是否和另一个相同
	bool operator==(const Candidate &) const;
	bool operator!=(const Candidate &) const;


private:
	//数据
	char *		_data;
	int			_length;	
};


#endif
