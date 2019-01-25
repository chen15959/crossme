/*
承载行的可行性

*/
#ifndef PossibleLine_hpp
#define PossibleLine_hpp

#include <string>
class Line;



class PossibleLine
{
public:
	//构造函数
	//用数组初始化
	PossibleLine(const char * data = NULL, int length = 0);
	//拷贝构造
	PossibleLine(const PossibleLine &);
	//析构函数
	virtual ~PossibleLine();
	//赋值运算符
	PossibleLine & operator=(const PossibleLine &);
	
	
private:
	void copy(const PossibleLine &);
	void free();

public:
	//获得某个位置上的值
	char getValue(int index) const;
	
	//产生一个摘要
	inline
	std::string getKey() const
	{
		return std::string(this->_data);
	}

public:
	//相当于两个做一次合并，相同的保留原值，不同的记为？
	PossibleLine & operator+=(const PossibleLine & rhs);
	PossibleLine operator+(const PossibleLine & rhs) const;

	//判断一个是否和已经存在的Line兼容
	bool operator==(const Line &) const;
	bool operator!=(const Line &) const;

	//判断一个是否和另一个相同
	bool operator==(const PossibleLine &) const;
	bool operator!=(const PossibleLine &) const;


private:
	//数据
	char *		_data;
	int			_length;	
};


#endif
