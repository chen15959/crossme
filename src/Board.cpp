#include "Board.hpp"

#include "Line.hpp"
#include "util.hpp"
#include "LogicLine.hpp"
#include "SifterLine.hpp"

#include <assert.h>
#include <stdlib.h>
using namespace std;




Board::Board(const ParamListCollection & col_params, const ParamListCollection & row_params, int log_level, int display_level)
:_id(""), _params_of_cols(&col_params), _params_of_rows(&row_params)
{
	assert(!col_params.empty());
	assert(!row_params.empty());

	init();

	_log_level = log_level;
	_display_level = display_level;


	for (LENGTH_T r = 0; r < row_params.size(); ++r)
	{
		double v = _lines[_row_id(r)]->install(row_params[r]);
		_todo.push(_row_id(r), -v);
	}

	for (LENGTH_T c = 0; c < col_params.size(); ++c)
	{
		double v = _lines[_col_id(c)]->install(col_params[c]);
		_todo.push(_col_id(c), -v);
	}


}



Board::Board(const Board & other)
//: _params_of_cols(other._params_of_cols), _params_of_rows(other._params_of_rows)
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
		free();
		copy(rhs);
	}
	
	return *this;
}


void Board::init()
{
//	assert(col_size > 0);
//	assert(row_size > 0);
	
//	_col_size = col_size;
//	_row_size = row_size;
	
	//初始化行/列
	for (LENGTH_T r = 0; r < row_size(); ++r)
	{
		_lines[_row_id(r)] = new SifterLine(col_size(), &(*_params_of_rows)[r], _row_id(r));
	}
	for (LENGTH_T c = 0; c < col_size(); ++c)
	{
		_lines[_col_id(c)] = new SifterLine(row_size(), &(*_params_of_cols)[c], _col_id(c));
	}
	
	//初始化Point空间
	_points = new Point*[col_size() * row_size()];

	//生成所有Point
	for (LENGTH_T r = 0; r < row_size(); ++r)
	{
		for (LENGTH_T c = 0; c < col_size(); ++c)
		{
			Point * point = new Point(r, c, this);
			
			_points[_index(r, c)] = point;
			
			_lines[_row_id(r)]->setPoint(point, c);
			_lines[_col_id(c)]->setPoint(point, r);
		}
	}
}



void Board::copy(const Board & other)
{
	//复制参数
	_params_of_cols = other._params_of_cols;
	_params_of_rows = other._params_of_rows;


	//初始化
	init();

	//不要输出日志
	int old_log_level = _log_level;
	_log_level = LOG_NOTHING;

	//复制Point的值
	for (LENGTH_T r = 0; r < row_size(); ++r)
	{
		for (LENGTH_T c = 0; c < col_size(); ++c)
		{
			LENGTH2_T idx = _index(r, c);
			_points[idx]->setValue(other.getValue(r, c));
		}
	}

	//日志恢复
	_log_level = old_log_level;
	
	//复制Line的内容
	for (map<long, Line *>::const_iterator it1 = other._lines.begin(); it1 != other._lines.end(); ++it1)
	{
		_lines[it1->first]->copyData(it1->second);
	}

	_id = other._id;
	_log_level = other._log_level;
	_display_level = other._display_level;

	_todo.clear();
}



void Board::free()
{
	//销毁每个Point
	for (LENGTH_T r = 0; r < row_size(); ++r)
	{
		for (LENGTH_T c = 0; c < col_size(); ++c)
		{
			delete _points[_index(r, c)];
		}
	}
	
	//销毁Point空间
	delete [] _points;
	
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
	for (LENGTH_T r = 0; r < row_size(); ++r)
	{
		for (LENGTH_T c = 0; c < col_size(); ++c)
		{
			if (getValue(r, c) == VAL_UNKNOWN)
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



VALUE_T Board::getValue(LENGTH_T row, LENGTH_T col) const
{
	assert(0 <= row && row < row_size());
	assert(0 <= row && col < col_size());
	
	return _points[_index(row, col)]->value();
}




/*
row_size = 3
col_size = 4

* * * *
* * * *
* * * *

*/



//强行设定某Point
void Board::install(LENGTH_T row, LENGTH_T col, VALUE_T value)
{
	assert(0 <= row && row < row_size());
	assert(0 <= col && col < col_size());
	
	_points[_index(row, col)]->setValue(value);
	
	//加入需计算列表
	_todo.push(_row_id(row));
	_todo.push(_col_id(col));
}



void Board::point_change_callback(LENGTH_T row, LENGTH_T col, VALUE_T value)
{
	//加入需计算列表
	_todo.push(_row_id(row));
	_todo.push(_col_id(col));
	
	if (_log_level >= LOG_STEP)
	{
		printf("\t[%lu, %lu] = (%c)\n", row + 1, col + 1, value);
	}
}



bool Board::play()
{
#ifdef _SHOW_PARAMS
	for (map<long, Line *>::const_iterator it1 = _lines.begin(); it1 != _lines.end(); ++it1)
	{
		printf("%s\t%d\t", this->id(), it1->first);

		for (ParamList::const_iterator it2 = it1->second->_params->begin(); it2 != it1->second->_params->end(); ++it2)
		{
			printf("%c%lu,", it2->type(), it2->size());
		}

		printf("\n");
	}
#endif

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

		if (_display_level >= DISPLAY_ROUND && ret > 0)
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

	for (LENGTH_T r = 0; r < row_size(); r++)
	{
		for (LENGTH_T c = 0; c < col_size(); c++)
		{
			VALUE_T v = getValue(r, c);
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
					weight.push(zip((short)(r-2), (short)(c)), factor_cx);

					weight.push(zip((short)(r-1), (short)(c-1)), factor_bx);
					weight.push(zip((short)(r-1), (short)(c)), factor_ax);
					weight.push(zip((short)(r-1), (short)(c+1)), factor_bx);

					weight.push(zip((short)(r), (short)(c-2)), factor_cx);
					weight.push(zip((short)(r), (short)(c-1)), factor_ax);
					weight.push(zip((short)(r), (short)(c+1)), factor_ax);
					weight.push(zip((short)(r), (short)(c+2)), factor_cx);

					weight.push(zip((short)(r+1), (short)(c-1)), factor_bx);
					weight.push(zip((short)(r+1), (short)(c)), factor_ax);
					weight.push(zip((short)(r+1), (short)(c+1)), factor_bx);

					weight.push(zip((short)(r+2), (short)(c)), factor_cx);
				}
				else
				{
					weight.push(zip((short)(r-2), (short)(c)), factor_cy);

					weight.push(zip((short)(r-1), (short)(c-1)), factor_by);
					weight.push(zip((short)(r-1), (short)(c)), factor_ay);
					weight.push(zip((short)(r-1), (short)(c+1)), factor_by);

					weight.push(zip((short)(r), (short)(c-2)), factor_cy);
					weight.push(zip((short)(r), (short)(c-1)), factor_ay);
					weight.push(zip((short)(r), (short)(c+1)), factor_ay);
					weight.push(zip((short)(r), (short)(c+2)), factor_cy);

					weight.push(zip((short)(r+1), (short)(c-1)), factor_by);
					weight.push(zip((short)(r+1), (short)(c)), factor_ay);
					weight.push(zip((short)(r+1), (short)(c+1)), factor_by);

					weight.push(zip((short)(r+2), (short)(c)), factor_cy);
				}
			}
		}
	}


	while (!weight.empty())
	{
		long pos0 = weight.top();
		short r, c;
		unzip(pos0, r, c);
		if (r >= 0 && (LENGTH_T)r < row_size() && c >= 0 && (LENGTH_T)c < col_size())
		{
			if (getValue((LENGTH_T)r, (LENGTH_T)c) == VAL_UNKNOWN)
			{
				return createCandidates((LENGTH_T)r, (LENGTH_T)c);
			}
		}

		weight.pop();
	}

	assert(0);
	
	return retVal;
}



std::vector<Board *> Board::createCandidates(LENGTH_T row, LENGTH_T col) const
{
	vector<Board *> retVal;
	WeightQueue candidates;


	_lines.find(_row_id(row))->second->getValues(col, candidates);
	_lines.find(_col_id(col))->second->getValues(row, candidates);

	while (!candidates.empty())
	{
		VALUE_T value = (VALUE_T)candidates.pop();

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

	for (LENGTH_T row = 0; row < row_size(); ++row)
	{
		if (row % 5 == 0)
		{
			fprintf(output, "\n");
		}

		for (LENGTH_T col = 0; col < col_size(); ++col)
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




SIZE_T Board::known() const
{
	SIZE_T ret = 0;

	for (LENGTH_T r = 0; r < row_size(); r++)
	{
		for (LENGTH_T c = 0; c < col_size(); c++)
		{
			if (getValue(r, c) != VAL_UNKNOWN)
			{
				ret++;
			}
		}
	}

	return ret;

}
