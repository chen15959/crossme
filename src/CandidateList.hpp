#ifndef CandidateList_hpp
#define CandidateList_hpp

#include "Candidate.hpp"
#include "Param.hpp"

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
	CandidateList(unsigned long length);
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


	char getValue(unsigned long pos);

	
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
	
	
#ifdef _DEBUG
	//输出
	inline
	void print(FILE * output = stdout) const
	{
		for (std::map<int, Candidate *>::const_iterator it1 = _candidates.begin(); it1 != _candidates.end(); ++it1)
		{
			fprintf(output, "%s\n", it1->second->getValue());
		}
	}
#endif	
    
private:
	//长度
	unsigned long					_length;
	//所有候选的可能
	std::map<int, Candidate *>     _candidates;
};


#endif
