#include "Puzzle.hpp"

#include <assert.h>
using namespace std;




Puzzle::Puzzle(bool col_params_first)
{
}



Puzzle::~Puzzle()
{
}



Puzzle::Puzzle(const Puzzle & other)
{
	copy(other);
}


Puzzle & Puzzle::operator =(const Puzzle & rhs)
{
	if (this != &rhs)
	{
		free();
		copy(rhs);
	}

	return *this;
}



void Puzzle::copy(const Puzzle & other)
{
	_params_of_cols = other._params_of_cols;
	_params_of_rows = other._params_of_rows;
}



void Puzzle::free()
{
	_params_of_cols.clear();
	_params_of_rows.clear();
}



/*
从字符串中读取Param
 并附加到params的结尾
 字符串格式应当为A123或123
 返回值为true代表字符串是有效的格式，生成的Param已经附加到params的结尾
*/
static
bool create_param(const char * str, ParamList & param_list)
{
	assert(str);
	
	char t = 'A';
	const char * p;
	
	//有类型字母
	if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z'))
	{
		t = str[0];
		str++;
	}
	
	//检查是否为全数字
	p = str;
	while (*p)
	{
		if (*p < '0' || *p > '9')
		{
			p = NULL;
			break;
		}
		++p;
	}
	
	
	if (p)
	{
		int d;
		if (sscanf(str, "%d", &d) == 1)
		{
			//格式符合要求
			param_list.push_back(Param(d, t));
			return true;
		}
	}

	//格式不符合要求
	return false;
}




//内部类
//处理所有列的参数，或者所有行的参数
class _params_handler
{
public:
	_params_handler(ParamListCollection * param_list_collection);
	virtual ~_params_handler();

public:
	void put(char ch);
	void finishItem();
	void finishLine();
	
private:
	ParamListCollection *	_param_list_collection;
	char					_buffer[1024];
	char *					_ptr;
	ParamList				_param_list;
};



//内部类
//一个状态机
//处理列/行切换问题
class params_handler
{
public:
	params_handler(ParamListCollection * col_params, ParamListCollection * row_params);
	virtual ~params_handler();
	
public:
	inline void put(char ch) {
		_handler->put(ch);
	}
	inline void finishItem() {
		_handler->finishItem();
	}
	inline void finishLine() {
		_handler->finishLine();
	}
	//切换列/行模式
	inline void changeMode() {
		//强制检查 必须是未切换状态 即不能两次调用
		assert(_handler == &_first);
		_handler = &_second;
	}
	

private:
	_params_handler		_first;
	_params_handler		_second;
	_params_handler *	_handler;
};



params_handler::params_handler(ParamListCollection * col_params, ParamListCollection * row_params)
: _second(row_params), _first(col_params)
{
	//先指向列
	_handler = &_first;
}


params_handler::~params_handler()
{
	//强制检查 必须已经切换过一次
	assert(_handler == &_second);
}


_params_handler::_params_handler(ParamListCollection * param_list_collection)
{
	//初始化
	_param_list_collection = param_list_collection;
	//字符指针指向缓冲区头
	_ptr = _buffer;
}


_params_handler::~_params_handler()
{
}


void _params_handler::put(char ch)
{
	//普通字符写入缓冲区
	*_ptr++ = ch;
}


void _params_handler::finishItem()
{
	bool ret;
	//结束了一个item
	*_ptr = '\0';
	ret = create_param(_buffer, _param_list);
	_ptr = _buffer;
	//未处理对item的解析结果
}


void _params_handler::finishLine()
{
	//结束了一行
	finishItem();
	
	if (_param_list.size() > 0)
	{
		_param_list_collection->push_back(_param_list);
		_param_list.clear();
	}
}























bool Puzzle::load_puzzle_file(const char * filename)
{
	assert(_params_of_cols.size() == 0);
	assert(_params_of_rows.size() == 0);



	FILE * file = fopen(filename, "r");
	if (!file)
	{
		return false;
	}
	
	bool in_comment = false;

	params_handler ph(&_params_of_cols, &_params_of_rows);
	
	while (!feof(file)) {
		char ch = (char)fgetc(file);
		
		//'#' '%' '*' 开启行注释
		if (ch == '#' || ch == '%' || ch == '*') {
			ph.finishLine();
			in_comment = true;
		}
		//换行则自动结束行注释
		else if (ch == '\n' || ch == '\r') {
			ph.finishLine();
			in_comment = false;
		}
		else if (!in_comment) {
			//非注释状态下 '/' '+'代表模式切换
			if (ch == '/' || ch == '+') {
				ph.finishLine();
				ph.changeMode();
			}
			//非注释状态下 '-'代表模式切换加行注释 (为处理-1作为切换符)
			else if (ch == '-') {
				ph.finishLine();
				ph.changeMode();
				in_comment = true;
			}
			//非注释状态下 ' ' '\t' '.' 代表一个item结束
			else if (ch == ' ' || ch == '\t' || ch == '.') {
				ph.finishItem();
			}
			//其他的非EOF就是合法字符
			else if (ch != '\xFF') {
				ph.put(ch);
			}
		}
	}
	
	ph.finishLine();

	
	fclose(file);
	
	return true;
}



bool Puzzle::load_installed_file(const char * filename)
{
	return false;
}





