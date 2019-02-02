#include "CandidateFactory.hpp"

#include "Line.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

using namespace std;




CandidateFactory::CandidateFactory()
{
}



CandidateFactory::~CandidateFactory()
{
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



CandidateList * CandidateFactory::createCandidateList(size_t length, const ParamsOfLine & params_of_line)
{
	//生成略缩字
	string keyword = createKeyword(length, params_of_line);
	if (_knownCandidateList.find(keyword) == _knownCandidateList.end())
	{
		//用略缩字查不到
		//自己建立一下
		CandidateList * retVal = new CandidateList(length, params_of_line);

		//全0行的处理
		if (params_of_line.size() == 1 && params_of_line[0].getSize() == 0)
		{
			retVal->addCandidate(new Candidate(length, VAL_EMPTY));
		}
		else
		{
			char * buffer = new char[length];

			//递归生成所有可能
			placeItem(retVal, length, buffer, 0, params_of_line, 0);

			delete [] buffer;
		}

		_knownCandidateList.insert(pair<string, CandidateList *>(keyword, retVal));

		return new CandidateList(*retVal);
	}
	else
	{
		return new CandidateList(*(_knownCandidateList[keyword]));
	}
}



string CandidateFactory::createKeyword(size_t length, const ParamsOfLine & params_of_line)
{
	char buffer[1024];
	string retVal;

	sprintf(buffer, "%d:", length);
	retVal += buffer;
	
	for (ParamsOfLine::const_iterator it1 = params_of_line.begin(); it1 != params_of_line.end(); ++it1)
	{
		sprintf(buffer, "%c%d,", it1->getType(), it1->getSize());
		retVal += buffer;
	}

	return retVal;
}









//放一个item到缓冲区
//result		放结果的
//length		总长度
//buffer		缓冲区
//buffer_offset	从缓冲区的什么位置可以开始放item，也就是上一个item最后一个位置+1 开始时当然是从0位
//parmas		所有需放置的item的信息
//params_ptr	当前应当放置第几个item 开始时当然是从0位
void CandidateFactory::placeItem(CandidateList * result, size_t length, char * buffer, size_t buffer_offset, const ParamsOfLine & params, size_t params_ptr)
{
	//剩余未放置的项的最小总长度
	int length_of_left_items = 0;

	//在第一个未放置项前面是否需要一个前导分隔
	int leading_space = 0;
	
	//第一个未放置项的长度
	length_of_left_items = params[params_ptr].getSize();
	//其他未放置项的长度往上加
	for (size_t i = params_ptr + 1; i < params.size(); ++i)
	{
		//相同类型的项之间必须隔开一个位置，不同类型的可以挨着放
		if (params[i].getType() == params[i-1].getType())
		{
			length_of_left_items += (1 + params[i].getSize());
		}
		else
		{
			length_of_left_items += params[i].getSize();
		}
	}
	
	//当前面已经有放置的项的时候，比较第一个未放置项和最后一个已放置项的类型。如果类型相同需要在前面加一个间隔
	if (params_ptr > 0 && (params[params_ptr-1].getType() == params[params_ptr].getType()))
	{
		leading_space = 1;
	}
	
	//可放置element的第一个位置
	size_t first_pos = buffer_offset + leading_space;
	//可放置element的最后一个位置
	size_t last_pos = length - length_of_left_items;

	//循环处理这些位置
	for (size_t start_point = first_pos; start_point <= last_pos; ++start_point)
	{
		//开始点
		size_t ptr = buffer_offset;
		
		//填充上个element到这个element之间的空白
		while (ptr < start_point)
		{
			buffer[ptr++] = VAL_EMPTY;
		}

		//放下这个element
		for (int i = 0; i < params[params_ptr].getSize(); ++i)
		{
			buffer[ptr++] = params[params_ptr].getType();
		}

		//如果后面还有其他element，则去放他们
		if (params_ptr < params.size() - 1)
		{
			placeItem(result, length, buffer, ptr, params, params_ptr + 1);
		}
		else
		{
			//将后面都用VAL_EMPTY填充
			while (ptr < length)
			{
				buffer[ptr] = VAL_EMPTY;
			}

			//加入候选集合
			result->addCandidate(new Candidate(length, buffer));
		}
	}
}
