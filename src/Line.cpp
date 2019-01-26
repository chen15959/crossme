#include "Line.hpp"

#include <assert.h>




Line::Line(int len)
{
	assert(len > 0);
	
	this->_length = len;
	this->_points = new Point*[this->_length];
}



Line::Line(const Line & other)
{
	copy(other);
}



Line::~Line()
{
	free();
}



Line & Line::operator=(const Line & rhs)
{
	if (&rhs != this)
	{
		this->free();
		this->copy(rhs);
	}
	
	return *this;
}



void Line::copy(const Line & other)
{
	this->_length = other._length;

	this->_points = new Point*[this->_length];

	for (int i = 0; i < this->_length; ++i)
	{
		this->_points[i] = other._points[i];
	}
}



void Line::free()
{
	//所有的点从Board删除
	//这里只要删除自己的Point存放区域就可以
	delete [] this->_points;
}



const Point * Line::getPoint(int pos) const
{
	assert(pos >= 0 && pos <= this->_length);
	
	return this->_points[pos];
}



void Line::setPoint(Point * point, int pos)
{
	assert(pos >= 0 && pos <= this->_length);
	
	this->_points[pos] = point;
}



bool Line::install(const std::vector<Param> & params)
{
	assert(params.size() > 0);
	
	
	if (params.size() == 1)
	{
		if (params[0].getSize() == 0)
		{
			//空行/列
			for (int i = 0; i < this->_length; ++i)
			{
				this->_points[i]->setEmpty();
			}
			//放一个占位置的
			this->_possiblities[std::string("")] = PossibleLine(NULL, 0);

			return true;
		}
	}
	
	//缓冲区
	char * buffer = new char[this->_length];

	//递归计算所有可行性
	this->makePossibleTree(buffer, 0, params, 0);

	delete [] buffer;

	return true;
}


//recursivePutElementAtAllPossiblePositions(char * buffer, int buffer_offset, )
//递归在所有的可能位置放置element
//buffer		缓冲区
//buffer_ptr	从缓冲区的什么位置可以开始放element，也就是上一个element最后一个位置+1 开始时当然是从0位
//parmas		所有需放置的element的信息
//params_ptr	当前应当放置第几个element 开始时当然是从0位
void Line::makePossibleTree(char * buffer, int buffer_offset, const std::vector<Param> & params, int params_ptr)
{
	//剩余未放置的元素的最小总长度
	int length_of_left_elements = 0;

	//在第一个可放置项前面是否需要一个前导分隔
	bool leading_space = false;
	
	//第一个未放置项的长度
	length_of_left_elements = params[params_ptr].getSize();
	//其他未放置项的长度往上加
	for (int i = params_ptr + 1; i < params.size(); ++i)
	{
		//相同类型的项之间必须隔开一个位置，不同类型的可以挨着放
		if (params[i].getType() == params[i-1].getType())
		{
			length_of_left_elements += (1 + params[i].getSize());
		}
		else
		{
			length_of_left_elements += params[i].getSize();
		}
	}
	
	//当前面已经有放置的项的时候，比较第一个未放置项和最后一个已放置项的类型。如果类型相同需要在前面加一个间隔
	if (params_ptr > 0 && (params[params_ptr-1].getType() == params[params_ptr].getType()))
	{
		leading_space = true;
	}
	
	

	//开始试放第一个未放置项
	//逻辑如下：
	//第一个可放置的位置，看leading space是否为True
	//当leading space==true的时候，第一个可放置位置是buffer ptr+1
	//当false的时候，第一个可放置位置是buffer ptr
	//然后从第一个可放置位置开始，尝试往后放
	//最后一个可放置位置，是总长度减去上面算出的未放置元素最小总长度

	//如下图
	//设length=10，params = 「2，1，3」
	//放置params【0】的时候
	//length_of_left_elements = (2) + 1 + (1) + 1 + (3) = 8
	//leading_space = false of course
	// [++ + +++	]
	// [..........]
	// at this time, the 1st pos is 0, and the last pos is 10 - 8 = 2
	
	// first
	// [++ * ***	]
	// [..........]
	
	// last
	// [	++ * ***]
	// [..........]
	// you can see in the last case it can not be put any righter because have to left enough space for the following elems

	// after put 1st elem in the first mode, then start to put the 2nd elem -> 1
	// now the buffer_ptr = 2, which is the following pos of the last elem
	//
	// [++ * ***	]
	// [++	 * ***]
	// [..........]
	//		 ^
	//			 ^
	// now the leading_space must be considered because they are all the same type, it is true
	// it shows that the 1st pos is 3, 2 + leading_space;
	// and the last pos is 5




	//可放置的缓冲区大小
	int buffer_len = this->_length - buffer_offset;
	//在这个缓冲区里可以做多少次放置
	int try_times = buffer_len - length_of_left_elements + 1;
	
	//在所有的可能性上试放第一个未放置项
	//所谓的开始点是从buffer_ptr开始算的
	for (int start_point = (leading_space ? 1 : 0); start_point < try_times; ++start_point)
	{
		int ptr = buffer_offset;
		
		for (int i = 0; i < start_point; ++i)
		{
			buffer[ptr++] = '.';
		}
		
		for (int i = 0; i < params[params_ptr].getSize(); ++i)
		{
			buffer[ptr++] = params[params_ptr].getType();
		}
		
		if (params_ptr < params.size() - 1)
		{
			makePossibleTree(buffer, ptr, params, params_ptr + 1);
		}
		else
		{
			while (ptr < _length)
			{
				buffer[ptr++] = '.';
			}
			
			buffer[ptr] = '\0';
			
			printf("%s\n", buffer);
		}
	}

}



//	void makePossibileTree(char * buffer, int buffer_ptr, const std::vector<Param> & params, int params_ptr);


