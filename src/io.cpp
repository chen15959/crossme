#include "io.hpp"

#include "Param.hpp"
//#include "Board.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;


/*
 读入一个参数
 格式为“%c%d”，或“%d”
 */

Param fromStr(const char * str)
{
	assert(str);
	
	char ch;
	int val;
	char buf[256];
	
	if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'A' && str[0] <= 'Z'))
	{
		ch = str[0];
		val = atoi(str + 1);
		sprintf(buf, "%c%d", ch, val);
	}
	else
	{
		ch = 'A';
		val = atoi(str);
		sprintf(buf, "%d", val);
	}
	
	if (strcmp(buf, str) == 0)
	{
		return Param(val, ch);
	}
	else
	{
		return Param(-1);
	}

}



int read_line(const char * line, vector<Param> & output)
{
	
	
	

	return -1;
}









/*
从字符串中读取Param
 字符串格式应当为A123或123
 返回的Param调用isValid判断是否合法
 
 */
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
	return Param(-1);
}



bool send_param(const char * buffer, vector<Param> & vec_param)
{
	Param param = create_param_from_str(buffer);
	if (param.isValid())
	{
		vec_param.push_back(param);
		return true;
	}
	
	return false;
}



class params_handler
{
public:
	params_handler();
	~params_handler();
	
public:
	
	
};







bool read_puzzle_file(const char * filename, ParamsOfLines & col_param, ParamsOfLines & row_param)
{
	FILE * file = fopen(filename, "r");
	if (!file)
	{
		return false;
	}
	
	bool in_comment = false;
	bool col_mode = true;
	char buffer[1024];
	char * p = buffer;
	vector<Param> current;
	
	while (!feof(file))
	{
		char ch = (char)fgetc(file);
		if (ch == '#' || ch == '%')
		{
			*p = '\0';
			p = buffer;

			send_param(buffer, current);

			in_comment = true;
		}
		else if (ch == '\n' || ch == '\r')
		{
			*p = '\0';
			p = buffer;
			
			send_param(buffer, current);
			
			if (current.size() > 0)
			{
				if (col_mode)
				{
					col_param.push_back(current);
				}
				else
				{
					row_param.push_back(current);
				}
				current.clear();
			}

			in_comment = false;
		}
		else if (!in_comment)
		{
			if (ch == '/' || ch == '+' || ch == '-')
			{
				*p = '\0';
				p = buffer;
				
				send_param(buffer, current);
				
				if (current.size() > 0)
				{
					if (col_mode)
					{
						col_param.push_back(current);
					}
					else
					{
						row_param.push_back(current);
					}
					current.clear();
				}
				
				col_mode = false;
				
				if (ch == '-')
				{
					in_comment = true;
				}
			}
			else if (ch == ' ' || ch == '\t')
			{
				*p = '\0';
				p = buffer;
				
				send_param(buffer, current);
			}
			else
			{
				*p++ = ch;
			}
			
		}
		
		/*
		switch (ch)
		{
			case '#':
				in_comment = true;
				break;
				
			case '\n':
			case '\r':
				*p = '\0';
				send_param(buffer, current);
				p = buffer;

				if (current.size() > 0)
				{
					if (col_mode)
					{
						col_param.push_back(current);
					}
					else
					{
						row_param.push_back(current);
					}
					current.clear();
				}
				
				in_comment = false;
				break;
				
			case '/':
				col_mode = false;
				break;
				
				
			default:
				if (!in_comment)
				{
					if (ch == ' ' || ch == '\t')
					{
						*p = '\0';
						send_param(buffer, current);
						p = buffer;
					}
					else
					{
						*p++ = ch;
					}
				}
				break;
		}
		 */
	}
	
	*p = '\0';
	p = buffer;
	
	send_param(buffer, current);
	
	if (current.size() > 0)
	{
		if (col_mode)
		{
			col_param.push_back(current);
		}
		else
		{
			row_param.push_back(current);
		}
		current.clear();
	}
	

	
	fclose(file);
	
	return true;
}


#if 0

bool read_current_board_file(const char * filename, vector<pair<int, int>> & current_yes, vector<pair<int, int>> & current_no)
{
	
	
	
	
	return true;
}

#endif





void output_param_of_lines(const ParamsOfLines & param_vec, FILE * output)
{
	for (ParamsOfLines::const_iterator it1 = param_vec.begin(); it1 != param_vec.end(); ++it1)
	{
		for (ParamsOfLine::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
		{
			fprintf(output, "%d ", it2->getSize());
		}
		fprintf(output, "\n");
	}
}


#if 0

void output_board(const Board & board, FILE * output)
{
	for (int r = 0; r < board.getRowSize(); ++r)
	{
		for (int c = 0; c < board.getColSize(); ++c)
		{
			fprintf(output, "%c", board.getPointVal(r, c));
		}
		fprintf(output, "\n");
	}
}

#endif
