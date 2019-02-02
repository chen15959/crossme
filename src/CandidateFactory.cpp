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
	//����������
	string keyword = createKeyword(length, params_of_line);
	if (_knownCandidateList.find(keyword) == _knownCandidateList.end())
	{
		//�������ֲ鲻��
		//�Լ�����һ��
		CandidateList * retVal = new CandidateList(length, params_of_line);

		//ȫ0�еĴ���
		if (params_of_line.size() == 1 && params_of_line[0].getSize() == 0)
		{
			retVal->addCandidate(new Candidate(length, VAL_EMPTY));
		}
		else
		{
			char * buffer = new char[length];

			//�ݹ��������п���
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









//��һ��item��������
//result		�Ž����
//length		�ܳ���
//buffer		������
//buffer_offset	�ӻ�������ʲôλ�ÿ��Կ�ʼ��item��Ҳ������һ��item���һ��λ��+1 ��ʼʱ��Ȼ�Ǵ�0λ
//parmas		��������õ�item����Ϣ
//params_ptr	��ǰӦ�����õڼ���item ��ʼʱ��Ȼ�Ǵ�0λ
void CandidateFactory::placeItem(CandidateList * result, size_t length, char * buffer, size_t buffer_offset, const ParamsOfLine & params, size_t params_ptr)
{
	//ʣ��δ���õ������С�ܳ���
	int length_of_left_items = 0;

	//�ڵ�һ��δ������ǰ���Ƿ���Ҫһ��ǰ���ָ�
	int leading_space = 0;
	
	//��һ��δ������ĳ���
	length_of_left_items = params[params_ptr].getSize();
	//����δ������ĳ������ϼ�
	for (size_t i = params_ptr + 1; i < params.size(); ++i)
	{
		//��ͬ���͵���֮��������һ��λ�ã���ͬ���͵Ŀ��԰��ŷ�
		if (params[i].getType() == params[i-1].getType())
		{
			length_of_left_items += (1 + params[i].getSize());
		}
		else
		{
			length_of_left_items += params[i].getSize();
		}
	}
	
	//��ǰ���Ѿ��з��õ����ʱ�򣬱Ƚϵ�һ��δ����������һ���ѷ���������͡����������ͬ��Ҫ��ǰ���һ�����
	if (params_ptr > 0 && (params[params_ptr-1].getType() == params[params_ptr].getType()))
	{
		leading_space = 1;
	}
	
	//�ɷ���element�ĵ�һ��λ��
	size_t first_pos = buffer_offset + leading_space;
	//�ɷ���element�����һ��λ��
	size_t last_pos = length - length_of_left_items;

	//ѭ��������Щλ��
	for (size_t start_point = first_pos; start_point <= last_pos; ++start_point)
	{
		//��ʼ��
		size_t ptr = buffer_offset;
		
		//����ϸ�element�����element֮��Ŀհ�
		while (ptr < start_point)
		{
			buffer[ptr++] = VAL_EMPTY;
		}

		//�������element
		for (int i = 0; i < params[params_ptr].getSize(); ++i)
		{
			buffer[ptr++] = params[params_ptr].getType();
		}

		//������滹������element����ȥ������
		if (params_ptr < params.size() - 1)
		{
			placeItem(result, length, buffer, ptr, params, params_ptr + 1);
		}
		else
		{
			//�����涼��VAL_EMPTY���
			while (ptr < length)
			{
				buffer[ptr] = VAL_EMPTY;
			}

			//�����ѡ����
			result->addCandidate(new Candidate(length, buffer));
		}
	}
}
