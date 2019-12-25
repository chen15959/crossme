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
	//评估可能性的数量
	double evaluateCandidateSize(LENGTH_T length, const ParamList & params_of_line, const Line * ref_line);


	//根据参数创建可能性
#ifdef _CANDIDATE_LIST_STORE
	//如果曾经创建过，那直接从已有的情况复制
#endif
	CandidateList * createCandidateList(LENGTH_T length, const ParamList & params_of_line, const Line * ref_line);

private:
	//放置一个item到缓冲区
	void placeItem(CandidateList * result, LENGTH_T length, VALUE_T * buffer, LENGTH_T buffer_offset, const ParamList & params, LENGTH_T params_ptr, const Line * ref_line);

#ifdef _CANDIDATE_LIST_STORE
private:
	//根据参数生成关键字
	std::string createKeyword(LENGTH_T length, const ParamList & params_of_line);

private:
	//曾经算过的可能性，用参数关键字做索引
	std::map<std::string, CandidateList *> _knownCandidateList;
#endif
};


#endif
