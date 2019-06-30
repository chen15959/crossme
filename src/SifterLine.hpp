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
	//����һ��Line��������candidates
	virtual
	void copyData(const Line * other);

	//must defined in base class
	virtual
	void getValues(LENGTH_T pos, WeightQueue &) const;

	//must defined in base class
	//ͨ����������ȫ��������
	//���ؿ����Ե�����
	//-1���������
	virtual
	double install(const ParamList & params);




private:
	//ͨ���ۺ����еĿ����ԣ�����ʵ�ʵ�ֵ
	//	����ֵ��ȷ���˼���point��ֵ
	int setByCandidates();
public:
	virtual
	bool isDone() const;

	//�Ƿ�����߼���
	virtual
	bool isError() const;



private:
	//���п�����
	CandidateList *							_candidates;


private:
	static CandidateFactory					__candidateFactory;


};





#endif


