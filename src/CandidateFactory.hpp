#ifndef CandidateFactory_hpp
#define CandidateFactory_hpp

#include "CandidateList.hpp"
#include "Candidate.hpp"
#include "Param.hpp"

#include <string>
#include <map>
class CandidateList;


//根据参数创建可能性
//
class CandidateFactory
{
public:
	CandidateFactory();
	virtual ~CandidateFactory();

private:
	CandidateFactory(const CandidateFactory &);
	CandidateFactory & operator=(const CandidateFactory &);


public:
	//根据参数创建可能性
	//如果曾经创建过，那直接从已有的情况复制
	CandidateList * createCandidateList(size_t length, const ParamsOfLine & params_of_line);

private:
	//放置一个item到缓冲区
	void placeItem(CandidateList * result, size_t length, char * buffer, size_t buffer_offset, const ParamsOfLine & params, size_t params_ptr);

private:
	//根据参数生成关键字
	std::string createKeyword(size_t length, const ParamsOfLine & params_of_line);

private:
	//曾经算过的可能性，用参数关键字做索引
	std::map<std::string, CandidateList *> _knownCandidateList;

};


#endif