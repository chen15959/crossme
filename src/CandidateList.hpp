#ifndef CandidateList_hpp
#define CandidateList_hpp

#include "Candidate.hpp"
#include "Param.hpp"
#include "WeightQueue.hpp"

#include <string>
#include <vector>
#include <map>
#include <stdio.h>
class Line;




// 行的可行性的集合
//
class CandidateList
{
public:
	//构造函数
	CandidateList(short length);
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
	void addCandidate(Candidate *);
	
public:
	//将list中不符合Line的条目去掉
	bool ruleBy(const Line &);

	inline
	bool setBy(const Line & line)
	{
		return ruleBy(line);
	}


	char getValue(short pos) const;


	inline
	char value(short pos) const
	{
		return getValue(pos);
	}

//	std::map<char, int> getCandidateValue(short pos) const;

	void getValues(short pos, WeightQueue & result) const;

	inline
	WeightQueue values(short pos) const
	{
		WeightQueue retVal;
		getValues(pos, retVal);
		return retVal;
	}

	
	//list中有多少条目
	inline
	unsigned long size() const
	{
		return this->_candidates.size();
	}

	//是否已经成功了（没有多种可能性了）
	inline
	bool isDone() const
	{
		return this->size() == 1;
	}

	//是否已经失败了（没有可能性了）
	inline
	bool isError() const
	{
		return this->size() < 1;
	}
	
	


private:
	//长度
	short							_length;
	//所有候选的可能
	std::map<int, Candidate *>		_candidates;
};


#endif
