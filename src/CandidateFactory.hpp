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
	double evaluateCandidateSize(unsigned long length, const ParamList & params_of_line, const Line * ref_line);


	//根据参数创建可能性
	//如果曾经创建过，那直接从已有的情况复制
	CandidateList * createCandidateList(unsigned long length, const ParamList & params_of_line, const Line * ref_line);

private:
	//放置一个item到缓冲区
	void placeItem(CandidateList * result, unsigned long length, VALUE_T * buffer, unsigned long buffer_offset, const ParamList & params, unsigned long params_ptr, const Line * ref_line);

private:
	//根据参数生成关键字
	std::string createKeyword(unsigned long length, const ParamList & params_of_line);

private:
	//曾经算过的可能性，用参数关键字做索引
	std::map<std::string, CandidateList *> _knownCandidateList;

};


#endif
