#include "CandidateFactory.hpp"

#include "Line.hpp"
#include "util.hpp"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

using namespace std;




CandidateFactory::CandidateFactory()
{
}



CandidateFactory::~CandidateFactory()
{
#ifdef _CANDIDATE_LIST_STORE
	for (map<string, CandidateList *>::const_iterator it = _knownCandidateList.begin(); it != _knownCandidateList.end(); ++it)
	{
		delete it->second;
	}

	_knownCandidateList.clear();
#endif
}




CandidateFactory::CandidateFactory(const CandidateFactory &)
{
	assert(0);
}



CandidateFactory & CandidateFactory::operator=(const CandidateFactory &)
{
	assert(0);

	return *this;
}



//将C1....Cm放到N里，求共有多少种放法
/*
固定格为 cc ＝ sum（c1 cm）+m-1
活动格为N-cc
可放置空位m+1

将n-cc放到m+1，有多少种放法



//（m+1）乘方（n-cc）除以（n-cc）！

n＝110
n-cc＝24
28乘方24
*/
double CandidateFactory::evaluateCandidateSize(LENGTH_T length, const ParamList & params_of_line, const Line * ref_line)
{
	assert(params_of_line.size() > 0);
	
	if (params_of_line.size() == 1 && params_of_line[0].size() == 0)
	{
		//全空行
		return 1;
	}
	
	//确定的Point（包括必须的间隔）
	LENGTH_T size_of_certain = params_of_line[0].size();
	for (LENGTH_T i = 1; i < params_of_line.size(); ++i)
	{
		size_of_certain += (params_of_line[i].size() + (params_of_line[i-1].type() == params_of_line[i].type() ? 1 : 0));
	}
	
	//待分配的Point
	LENGTH_T to_be_put = length - size_of_certain;
	
	if (to_be_put == 0)
	{
		//刚好放满了
		return 1;
	}
	
	//可放置的位置
	LENGTH_T space_to_put = params_of_line.size() + 1;
	
	//求将to_be_put放到space_to_put中，有多少种放法
	//C(to_be_put+space_to_put-1 , space_to_put-1)

	return factorial_stirling(to_be_put + space_to_put - 1) / (factorial_stirling(space_to_put - 1) * factorial_stirling(to_be_put));
}



CandidateList * CandidateFactory::createCandidateList(LENGTH_T length, const ParamList & params_of_line, const Line * ref_line)
{
#ifdef _CANDIDATE_LIST_STORE
	//生成略缩字
	string keyword = createKeyword(length, params_of_line);
	if (_knownCandidateList.find(keyword) == _knownCandidateList.end())
	{
		//用略缩字查不到
		//自己建立一下
#endif
		CandidateList * retVal = new CandidateList(length);

		//全0行的处理
		if (params_of_line.size() == 1 && params_of_line[0].size() == 0)
		{
			retVal->addCandidate(new Candidate(length, VAL_EMPTY));
			return retVal;
		}
		else
		{
			VALUE_T * buffer = new VALUE_T[length];

			//递归生成所有可能
			placeItem(retVal, length, buffer, 0, params_of_line, 0, ref_line);

			delete [] buffer;
		}

#ifdef _CANDIDATE_LIST_STORE
		if (ref_line == NULL)
		{
			_knownCandidateList.insert(pair<string, CandidateList *>(keyword, retVal));
			return new CandidateList(*retVal);
		}
		else
#endif
		{
			return retVal;
		}
#ifdef _CANDIDATE_LIST_STORE
	}
	else
	{
		CandidateList * retVal = new CandidateList(*(_knownCandidateList[keyword]));
		if (ref_line != NULL)
		{
			retVal->ruleBy(*ref_line);
		}
		return retVal;
	}
#endif
}



#ifdef _CANDIDATE_LIST_STORE

string CandidateFactory::createKeyword(LENGTH_T length, const ParamList & params_of_line)
{
	char buffer[1024];
	string retVal;

	sprintf(buffer, "%lu:", length);
	retVal += buffer;
	
	for (ParamList::const_iterator it1 = params_of_line.begin(); it1 != params_of_line.end(); ++it1)
	{
		sprintf(buffer, "%c%lu,", it1->type(), it1->size());
		retVal += buffer;
	}

	return retVal;
}

#endif








//放一个item到缓冲区
//result		放结果的
//length		总长度
//buffer		缓冲区
//buffer_offset	从缓冲区的什么位置可以开始放item，也就是上一个item最后一个位置+1 开始时当然是从0位
//parmas		所有需放置的item的信息
//params_ptr	当前应当放置第几个item 开始时当然是从0位
void CandidateFactory::placeItem(CandidateList * result, LENGTH_T length, VALUE_T * buffer, LENGTH_T buffer_offset, const ParamList & params, LENGTH_T params_ptr, const Line * ref_line)
{
	//剩余未放置的项的最小总长度
	LENGTH_T length_of_left_items = 0;

	//在第一个未放置项前面是否需要一个前导分隔
	LENGTH_T leading_space = 0;
	
	//第一个未放置项的长度
	length_of_left_items = params[params_ptr].size();
	//其他未放置项的长度往上加
	for (LENGTH_T i = params_ptr + 1; i < params.size(); ++i)
	{
		//相同类型的项之间必须隔开一个位置，不同类型的可以挨着放
		if (params[i].type() == params[i-1].type())
		{
			length_of_left_items += (1 + params[i].size());
		}
		else
		{
			length_of_left_items += params[i].size();
		}
	}
	
	//当前面已经有放置的项的时候，比较第一个未放置项和最后一个已放置项的类型。如果类型相同需要在前面加一个间隔
	if (params_ptr > 0 && (params[params_ptr-1].type() == params[params_ptr].type()))
	{
		leading_space = 1;
	}
	
	//可放置element的第一个位置
	LENGTH_T first_pos = buffer_offset + leading_space;
	//可放置element的最后一个位置
	LENGTH_T last_pos = length - length_of_left_items;

	//循环处理这些位置
	for (LENGTH_T start_point = first_pos; start_point <= last_pos; ++start_point)
	{
		//开始点
		LENGTH_T ptr = buffer_offset;
		
		//填充上个element到这个element之间的空白
		while (ptr < start_point)
		{
			if (ref_line)
			{
				VALUE_T ref_value = ref_line->getPoint(ptr)->value();
				if (ref_value != VAL_UNKNOWN && ref_value != VAL_EMPTY)
				{
					return;
				}
			}
			buffer[ptr++] = VAL_EMPTY;
		}

		//放下这个element
		for (LENGTH_T i = 0; i < params[params_ptr].size(); ++i)
		{
			if (ref_line)
			{
				VALUE_T ref_value = ref_line->getPoint(ptr)->value();
				if (ref_value != VAL_UNKNOWN && params[params_ptr].type())
				{
					return;
				}
			}
			buffer[ptr++] = params[params_ptr].type();
		}

		//如果后面还有其他element，则去放他们
		if (params_ptr < params.size() - 1)
		{
			placeItem(result, length, buffer, ptr, params, params_ptr + 1, ref_line);
		}
		else
		{
			//将后面都用VAL_EMPTY填充
			while (ptr < length)
			{
				if (ref_line)
				{
					VALUE_T ref_value = ref_line->getPoint(ptr)->value();
					if (ref_value != VAL_UNKNOWN && ref_value != VAL_EMPTY)
					{
						return;
					}
				}

				buffer[ptr++] = VAL_EMPTY;
			}

			//加入候选集合
			result->addCandidate(new Candidate(buffer, length));
		}
	}
}
