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
bool create_param(const char * str, ParamsOfLine & params)
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
			params.push_back(Param(d, t));
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
	_params_handler(ParamsOfLines * params);
	virtual ~_params_handler();

public:
	void put(char ch);
	void finishItem();
	void finishLine();
	
private:
	ParamsOfLines * pols;
	char buffer[1024];
	char * ptr;
	ParamsOfLine line;
};



//内部类
//一个状态机
//处理列/行切换问题
class params_handler
{
public:
	params_handler(ParamsOfLines * col_params, ParamsOfLines * row_params);
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



params_handler::params_handler(ParamsOfLines * col_params, ParamsOfLines * row_params)
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


_params_handler::_params_handler(ParamsOfLines * param)
{
	pols = param;
	ptr = buffer;
}


_params_handler::~_params_handler()
{
}


void _params_handler::put(char ch)
{
	*ptr++ = ch;
}


void _params_handler::finishItem()
{
	*ptr = '\0';
	create_param(buffer, line);
	ptr = buffer;
}


void _params_handler::finishLine()
{
	finishItem();
	
	if (line.size() > 0)
	{
		pols->push_back(line);
		line.clear();
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
		
		if (ch == '#' || ch == '%' || ch == '*') {
			ph.finishLine();
			in_comment = true;
		}
		else if (ch == '\n' || ch == '\r') {
			ph.finishLine();
			in_comment = false;
		}
		else if (!in_comment) {
			if (ch == '/' || ch == '+' || ch == '-') {
				ph.finishLine();
				ph.changeMode();

				if (ch == '-') {
					in_comment = true;
				}
			}
			else if (ch == ' ' || ch == '\t' || ch == '.') {
				ph.finishItem();
			}
			else if (ch != '\xFF'){
				ph.put(ch);
			}
		}
	}
	
	ph.finishLine();

	
	fclose(file);
	
	return true;

//	return -1;
}



bool Puzzle::load_installed_file(const char * filename)
{
	return false;
}





