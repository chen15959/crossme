#include "def.hpp"
#include "Param.hpp"

#include <assert.h>



VALUE_T * reverse(const VALUE_T * value_array, LENGTH_T length)
{
	if (value_array)
	{
		VALUE_T * result = new VALUE_T[length];

		for (LENGTH_T i = 0; i < length; ++i)
		{
			result[i] = value_array[length - i - 1];
		}

		return result;
	}
	else
	{
		return NULL;
	}
}



VALUE_T * fill(VALUE_T value, LENGTH_T length)
{
	VALUE_T * result = new VALUE_T[length];
	for (LENGTH_T i = 0; i < length; ++i)
	{
		result[i] = value;
	}
	return result;
}



#if 0
VALUE_T * arrange(LENGTH_T total_length, const ParamList & params, const VALUE_T * ref_line, bool backward = false)
{
	assert(params.size() > 0);
	assert(total_length > 0);



	if (params.size() == 1)
	{
		if (params[0].size() == 0)
		{
			//kong hang
			return fill(VAL_EMPTY, total_length);
		}
		else if (params[0].size() == total_length)
		{
			//man hang
			return fill(params[0].type(), total_length);
		}
	}



	if (backward)
	{
		ParamList r_params;
		for (int i = params.size() - 1; i >= 0; ++i)
		{
			r_params.push_back(params[i]);
		}

		VALUE_T * r_ref_line = reverse(ref_line, total_length);

		VALUE_T * r_result = arrange(total_length, r_params, r_ref_line, false);

		delete [] r_ref_line;

		VALUE_T * result = reverse(r_result, total_length);
		
		delete [] r_result;

		return result;
	}




/*

			VALUE_T * buffer = new VALUE_T[length];

			//递归生成所有可能
			placeItem(retVal, length, buffer, 0, params_of_line, 0, ref_line);

			delete [] buffer;
*/

	return NULL;




}

#endif

#if 0

//放一个item到缓冲区
//result		放结果的
//length		总长度
//buffer		缓冲区
//buffer_offset	从缓冲区的什么位置可以开始放item，也就是上一个item最后一个位置+1 开始时当然是从0位
//parmas		所有需放置的item的信息
//params_ptr	当前应当放置第几个item 开始时当然是从0位
bool placeItem(LENGTH_T length, VALUE_T * buffer, LENGTH_T buffer_offset, const ParamList & params, LENGTH_T params_offset, const Line * ref_liine)
{
	LENGTH_T length_of_left_items = 0;

	LENGTH_T leading_space = 0;

	length_of_left_items = params[params_offset].size();

	for (LENGTH_T i = params_offset + 1; i < params.size(); ++i)
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
			if (!ref_line->getPoint(ptr)->allow(VAL_EMPTY))
			{
				return;
			}
			buffer[ptr++] = VAL_EMPTY;
		}

		//放下这个element
		for (LENGTH_T i = 0; i < params[params_ptr].size(); ++i)
		{
			if (ref_line)
			{
				if (!ref_line->getPoint(ptr)->allow(params[params_offset].type()))
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
			result->addCandidate(new Candidate(length, buffer));
		}
	}

	return false;
}

#endif


/*
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
			result->addCandidate(new Candidate(length, buffer));
		}
	}
}


*/