#ifndef Param_hpp
#define Param_hpp

#include "def.hpp"

#include <vector>




//行/列上输入的参数
//
class Param
{
public:
	//数量 即游戏中的 数字
	//类型代码（A~Z） 对应游戏中的 颜色
	//在单颜色模式下 只输入第一个参数（size）就行
	
	//构造函数
	Param(LENGTH_T size, VALUE_T type = 'A');
	//拷贝构造
	Param(const Param & other);
	//析构函数
	virtual ~Param();
	
	//赋值运算符
	Param & operator=(const Param & rhs);
	
public:
	//获得类型
#if 0
	inline
	VALUE_T getType() const {
		return this->type();
	}
#endif

	inline
	VALUE_T type() const {
		return _type;
	}


	//获得数量
#if 0
	inline
	LENGTH_T getSize() const {
		return this->size();
	}
#endif

	inline
	LENGTH_T size() const {
		return _size;
	}
	
	
private:
	//类型，单色模式下常为A
	VALUE_T			_type;
	//数量
	LENGTH_T		_size;
};


//一个Line上的参数
//typedef std::vector<Param > ParamsOfLine;
typedef std::vector<Param > ParamList;
//一组Line上的参数（所有行或所有列）
//typedef std::vector<ParamsOfLine > ParamsOfLines;
//typedef std::vector<ParamList > ParamsOfLines;
//typedef std::vector<ParamList > ParamsOfLineCollection;
typedef std::vector<ParamList > ParamListCollection;

#endif
