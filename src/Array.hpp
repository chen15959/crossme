#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "def.hpp"



//数组类型接口
//只读
class Array
{
public:
	//获得数组某位置的值
	virtual VALUE_T value(LENGTH_T pos) const = 0;

	//获得数组总长度
	virtual LENGTH_T length() const = 0;


public:

	//数组访问方式（只读）
	inline
	VALUE_T operator[] (LENGTH_T pos) const 
	{
		return value(pos);
	}



	//判断是否和已经存在的Line兼容
	bool operator==(const Array & other) const;

	inline
	bool operator!=(const Array & other) const
	{
		return !(*this == other);
	}
};


#endif
