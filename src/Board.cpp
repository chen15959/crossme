#include "Board.hpp"

#include "Line.hpp"
#include "util.hpp"

#include <assert.h>
#include <stdlib.h>
using namespace std;




Board::Board(unsigned long col_size, unsigned long row_size, int log_level, int display_level)
:_id("")
{
	init(col_size, row_size);
	_log_level = log_level;
	_display_level = display_level;
}



Board::Board(const Board & other)
{
	copy(other);
}



Board::~Board()
{
	free();
}



Board & Board::operator=(const Board & rhs)
{
	if (&rhs != this)
	{
		//先删掉自己的，再用别人的替代
		this->free();
		this->copy(rhs);
	}
	
	return *this;
}


void Board::init(unsigned long col_size, unsigned long row_size)
{
	assert(col_size > 0);
	assert(row_size > 0);
	
	_col_size = col_size;
	_row_size = row_size;
	
	//初始化行/列
	for (unsigned long r = 0; r < row_size; ++r)
	{
		_lines[row_id(r)] = new Line(col_size);
	}
	for (unsigned long c = 0; c < col_size; ++c)
	{
		_lines[col_id(c)] = new Line(row_size);
	}
	
	//初始化Point空间
	_points = new Point*[_col_size * _row_size];

	//生成所有Point
	for (unsigned long r = 0; r < _row_size; ++r)
	{
		for (unsigned long c = 0; c < _col_size; ++c)
		{
			Point * point = new Point((short)r, (short)c, this);
			
			_points[getIndex(r, c)] = point;
			
			_lines[row_id(r)]->setPoint(point, c);
			_lines[col_id(c)]->setPoint(point, r);
		}
	}
}



void Board::copy(const Board & other)
{
	//初始化
	init(other._col_size, other._row_size);

	//不要输出日志
	int old_log_level = _log_level;
	_log_level =	LOG_NOTHING;

	//复制Point的值
	for (unsigned long r = 0; r < _row_size; ++r)
	{
		for (unsigned long c = 0; c < _col_size; ++c)
		{
			unsigned long idx = getIndex(r, c);
			_points[idx]->setValue(other.getValue(r, c));
		}
	}

	//日志恢复
	_log_level = old_log_level;
	
	//复制Line的值
	for (map<long, Line *>::const_iterator it1 = other._lines.begin(); it1 != other._lines.end(); ++it1)
	{
		_lines[it1->first]->copyCandidates(*(it1->second));
	}

	_id = other._id;
	_log_level = other._log_level;
	_display_level = other._display_level;

	_todo.clear();
}



void Board::free()
{
	//销毁每个Point
	for (unsigned long r = 0; r < this->_row_size; ++r)
	{
		for (unsigned long c = 0; c < this->_col_size; ++c)
		{
			delete this->_points[this->getIndex(r, c)];
		}
	}
	
	//销毁Point空间
	delete [] this->_points;
	
	//销毁所有Line
	for (map<long, Line *>::const_iterator it1 = _lines.begin(); it1 != _lines.end(); ++it1)
	{
		delete it1->second;
	}
	
	//销毁Line空间
	_lines.clear();
}



//棋局是否已经走完
bool Board::isDone() const
{
	for (unsigned long r = 0; r < this->_row_size; ++r)
	{
		for (unsigned long c = 0; c < this->_col_size; ++c)
		{
			if (this->_points[this->getIndex(r, c)]->getValue() == VAL_UNKNOWN)
			{
				return false;
			}
		}
	}

	return true;
}



bool Board::isError() const
{
	for (map<long, Line *>::const_iterator it = _lines.begin(); it != _lines.end(); ++it)
	{
		if (it->second->isError())
		{
			return true;
		}
	}
	
	return false;
}



char Board::getValue(unsigned long row, unsigned long col) const
{
	assert(row < _row_size);
	assert(col < _col_size);
	
	return _points[getIndex(row, col)]->getValue();
}




/*
row_size = 3
col_size = 4

* * * *
* * * *
* * * *

*/

//使用参数来初始化
void Board::install(const ParamsOfLines & col_params, const ParamsOfLines & row_params)
{
	for (unsigned long r = 0; r < row_params.size(); ++r)
	{
		double v = _lines[row_id(r)]->install(row_params[r]);
		_todo.push(row_id(r), -v);
	}

	for (unsigned long c = 0; c < col_params.size(); ++c)
	{
		double v = _lines[col_id(c)]->install(col_params[c]);
		_todo.push(col_id(c), -v);
	}
}



//强行设定某Point
void Board::install(unsigned long row, unsigned long col, char value)
{
	assert(row < _row_size);
	assert(col < _col_size);
	
	_points[getIndex(row, col)]->setValue(value);
	
	//加入需计算列表
	_todo.push(row_id(row));
	_todo.push(col_id(col));
}



void Board::point_change_callback(unsigned long row, unsigned long col, char value)
{
	//加入需计算列表
	_todo.push(row_id(row));
	_todo.push(col_id(col));
	
	if (_log_level >= LOG_STEP)
	{
		printf("\t[%lu, %lu] = (%c)\n", row + 1, col + 1, value);
	}
}



bool Board::play()
{
	while (_todo.size() > 0)
	{
		long p = _todo.top();
		
		if (_log_level >= LOG_STEP)
		{
			if (p > 0)
			{
				printf("#%s\tROW: %ld\n", id(), p);
			}
			else
			{
				printf("#%s\tCOL: %ld\n", id(), -p);
			}
		}

		int ret = _lines[p]->play();

		if (_log_level == LOG_ROUND)
		{
			if (ret >= 0)
			{
				if (p > 0)
				{
					printf("#%s\tROW: %ld\t(%d)\n", id(), p, ret);
				}
				else
				{
					printf("#%s\tCOL: %ld\t(%d)\n", id(), -p, ret);
				}
			}
			else
			{
				if (p > 0)
				{
					printf("#%s\tROW: %ld\tERROR\n", id(), p);
				}
				else
				{
					printf("#%s\tCOL: %ld\tERROR\n", id(), -p);
				}

				return false;
			}
		}


		if (ret < 0)
		{
			if (_log_level >= LOG_STEP)
			{
				printf("\tFAILED\n");
			}
			return false;
		}

		if (_display_level >= DIS_ROUND)
		{
			print(stdout);
		}

		_todo.pop();
	}

	return true;
}



extern double factor_ax;
extern double factor_bx;
extern double factor_cx;
extern double factor_ay;
extern double factor_by;
extern double factor_cy;



std::vector<Board *> Board::createCandidates() const
{
	vector<Board *> retVal;

	WeightQueue weight;

	for (short r = 0; r < _row_size; r++)
	{
		for (short c = 0; c < _col_size; c++)
		{
			char v = getValue(r, c);
			if (v != VAL_UNKNOWN && v != VAL_NONE)
			{
/*
			    c
		      b a b 
		    c a * a c
	          b a b
				c
*/
				if (v != VAL_EMPTY)
				{
					weight.push(zip(r-2, c), factor_cx);

					weight.push(zip(r-1, c-1), factor_bx);
					weight.push(zip(r-1, c), factor_ax);
					weight.push(zip(r-1, c+1), factor_bx);

					weight.push(zip(r, c-2), factor_cx);
					weight.push(zip(r, c-1), factor_ax);
					weight.push(zip(r, c+1), factor_ax);
					weight.push(zip(r, c+2), factor_cx);

					weight.push(zip(r+1, c-1), factor_bx);
					weight.push(zip(r+1, c), factor_ax);
					weight.push(zip(r+1, c+1), factor_bx);

					weight.push(zip(r+2, c), factor_cx);
				}
				else
				{
					weight.push(zip(r-2, c), factor_cy);

					weight.push(zip(r-1, c-1), factor_by);
					weight.push(zip(r-1, c), factor_ay);
					weight.push(zip(r-1, c+1), factor_by);

					weight.push(zip(r, c-2), factor_cy);
					weight.push(zip(r, c-1), factor_ay);
					weight.push(zip(r, c+1), factor_ay);
					weight.push(zip(r, c+2), factor_cy);

					weight.push(zip(r+1, c-1), factor_by);
					weight.push(zip(r+1, c), factor_ay);
					weight.push(zip(r+1, c+1), factor_by);

					weight.push(zip(r+2, c), factor_cy);
				}
			}
		}
	}


	while (!weight.empty())
	{
		long pos0 = weight.top();
		short r, c;
		unzip(pos0, r, c);
		if (r >= 0 && r < _row_size && c >= 0 && c < _col_size)
		{
			if (getValue(r, c) == VAL_UNKNOWN)
			{
				return createCandidates(r, c);
			}
		}

		weight.pop();
	}

	assert(0);
	
	return retVal;
}



std::vector<Board *> Board::createCandidates(unsigned long row, unsigned long col) const
{
	vector<Board *> retVal;
	//map<char, int> candidates;
	WeightQueue candidates;


	_lines.find(row_id(row))->second->getValues(col, candidates);
	_lines.find(col_id(col))->second->getValues(row, candidates);

	while (!candidates.empty())
	{
		char value = (char)candidates.pop();

		Board * board = new Board(*this);

		board->_log_level = LOG_NOTHING;
		board->install(row, col, value);
		board->_log_level = _log_level;

		char buf[16];
		sprintf(buf, "%c", value);
		board->_id += buf;

		if (_log_level >= LOG_TRY)
		{
			printf("#%s\tTRY [%lu, %lu] = (%c) -> #%s\n", id(), row + 1, col + 1, value, board->id());
		}
			
		retVal.push_back(board);
	}


	return retVal;
}



void Board::print(FILE * output, bool head) const
{
	if (_id.length() > 0 || head)
	{
		fprintf(output, "-= %s =-\n", id());
	}

	for (unsigned long row = 0; row < row_size(); ++row)
	{
		if (row % 5 == 0)
		{
			fprintf(output, "\n");
		}

		for (unsigned long col = 0; col < col_size(); ++col)
		{
			if (col % 5 == 0 && col > 0)
			{
				fprintf(output, " ");
			}
			fprintf(output, "%c", getValue(row, col));
		}
		fprintf(output, "\n");
	}

	fprintf(output, "\n\n");



}




unsigned long Board::known() const
{
	unsigned long ret = 0;

	for (unsigned long r = 0; r < _row_size; r++)
	{
		for (unsigned long c = 0; c < _col_size; c++)
		{
			if (getValue(r, c) != VAL_UNKNOWN)
			{
				ret++;
			}
		}
	}

	return ret;

}
