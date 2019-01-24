/*
解谜输入的参数
*/
#ifndef Param_hpp
#define Param_hpp

#include <vector>




class Param
{
public:
	//数量 即游戏中的 数字
	//类型代码（A~Z） 对应游戏中的 颜色
	//在单颜色模式下 只输入第一个参数就行
	
	//构造函数
	Param(int size, char type = 'A');
	//拷贝构造
	Param(const Param & other);
	//析构函数
	virtual ~Param();
	
	//赋值运算符
	Param & operator=(const Param & rhs);
	
public:
	//获得类型
	inline
	char getType() const
	{
		return _type;
	}
	
	//获得数量
	inline
	int getSize() const
	{
		return _size;
	}
	
	//是否为合法的参数
	inline
	bool isValid() const
	{
		return _size > -1;
	}
	
	
private:
	//类型，单色模式下长为A
	char _type;
	//数量
	int _size;
};


//一个Line上的参数
typedef std::vector<Param > ParamsOfLine;
//一组Line上的参数（所有行或所有列）
typedef std::vector<ParamsOfLine > ParamsOfLines;

#endif
