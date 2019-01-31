#ifndef CandidateList_hpp
#define CandidateList_hpp

#include "Candidate.hpp"

#include <string>
#include <map>
class Line;


// 行的可行性的集合
// 本质上是一个map
//
class CandidateList
{
public:
	//构造函数
	CandidateList();
	//拷贝构造
	CandidateList(const CandidateList &);
	//析构函数
	virtual ~CandidateList();
	//赋值运算符
	CandidateList & operator=(const CandidateList &);
	
	
private:
	void copy(const CandidateList &);
	void free();

public:
	//添加一个Candidate
	void addCandidate(const Candidate &);
	
public:
	//将list中不符合Line的条目去掉
	bool ruleBy(const Line &);
	//获得所有条目的最大公约数
	Candidate getDivisor() const;
	
	//list中有多少条目
	inline
	size_t size() const
	{
		return this->_candidates.size();
	}
	
	inline
	bool isDone() const
	{
		return this->size() == 1;
	}
	
	inline
	bool isFail() const
	{
		return this->size() < 1;
	}
	
	
#if 0
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
#endif
    
private:
	std::map<int, Candidate>     _candidates;
};


#endif
