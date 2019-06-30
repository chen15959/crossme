#ifndef SifterLine_hpp
#define SifterLine_hpp


#include "Line.hpp"

#include "Point.hpp"
#include "Param.hpp"
#include "Candidate.hpp"
#include "CandidateList.hpp"
#include "CandidateFactory.hpp"
#include "WeightQueue.hpp"

#include <vector>
#include <map>
#include <string>



class SifterLine : public Line
{
public:
	SifterLine(LENGTH_T length, const ParamList * params, long id = 0);
	~SifterLine();


private:
	SifterLine(const SifterLine & other);

	SifterLine & operator=(const SifterLine & other);
	SifterLine & operator=(const Line & other);



public:
	virtual int play();



public:
	//从另一个Line复制他的candidates
	virtual
	void copyData(const Line * other);

	//must defined in base class
	virtual
	void getValues(LENGTH_T pos, WeightQueue &) const;

	//must defined in base class
	//通过参数建立全部可能性
	//返回可能性的数量
	//-1代表出错了
	virtual
	double install(const ParamList & params);




private:
	//通过综合所有的可能性，设置实际的值
	//	返回值是确定了几个point的值
	int setByCandidates();
public:
	virtual
	bool isDone() const;

	//是否产生逻辑错
	virtual
	bool isError() const;



private:
	//所有可能性
	CandidateList *							_candidates;


private:
	static CandidateFactory					__candidateFactory;


};





#endif


