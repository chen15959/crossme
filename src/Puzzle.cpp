#include "Puzzle.hpp"

#include <assert.h>
using namespace std;




Puzzle::Puzzle(bool col_params_first)
//: _first(col_params_first ? &_params_of_cols : &_params_of_rows), _second(col_params_first ? &_params_of_rows : &_params_of_cols)
{
//	_current = &_first;
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
 字符串格式应当为A123或123
 返回的Param调用isValid判断是否合法
 
 */
/*
Param create_param_from_str(const char * str)
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
			return Param(d, t);
		}
	}

	//格式不符合要求
	return Param(-1, VAL_EMPTY);
}
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
	ParamsOfLines * pol;
	char buffer[1024];
	char * ptr;
	ParamsOfLine line;
};




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
	inline void changeMode() {
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
	_handler = &_first;
}


params_handler::~params_handler()
{
}


_params_handler::_params_handler(ParamsOfLines * param)
{
	pol = param;
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
		pol->push_back(line);
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







/*
	int load_puzzle_file(const char *);
	int load_installed_file(const char *);


private:
	ParamsOfLines		_params_of_cols;
	ParamsOfLines		_params_of_rows;

*/