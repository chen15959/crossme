#include "Board.hpp"

#include "Line.hpp"
//#include "io.hpp"
#include <assert.h>
#include <stdlib.h>
using namespace std;




Board::Board(unsigned long col_size, unsigned long row_size, int id, int output_level)
{
	init(col_size, row_size);
	_id = id;
	_output_level = output_level;
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
			Point * point = new Point(r, c, this);
			
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

	int old_output_level = _output_level;
	_output_level = OUTPUT_RESULT;
	//复制Point的值
	for (unsigned long r = 0; r < _row_size; ++r)
	{
		for (unsigned long c = 0; c < _col_size; ++c)
		{
			unsigned long idx = getIndex(r, c);
			_points[idx]->setValue(other.getValue(r, c));
		}
	}
	_output_level = old_output_level;
	
	//复制Line的值
	for (map<long, Line *>::const_iterator it1 = other._lines.begin(); it1 != other._lines.end(); ++it1)
	{
		_lines[it1->first]->copyCandidates(*(it1->second));
	}

	_id = other._id;
	_output_level = other._output_level;

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
	
	if (_output_level >= OUTPUT_STEPS)
	{
		printf("\t[%lu, %lu] = (%c)\n", row + 1, col + 1, value);
	}
}

bool output_every_step = false;


bool Board::play()
{
	while (_todo.size() > 0)
	{
		long p = _todo.top();
		
		if (_output_level >= OUTPUT_STEPS)
		{
			if (p > 0)
			{
				printf("#%d\tROW: %d\n", _id, p);
			}
			else
			{
				printf("#%d\tCOL: %d\n", _id, -p);
			}
		}

		int ret = _lines[p]->play();

		if (_output_level == OUTPUT_ROUNDS || _output_level == OUTPUT_ROUNDS_EFF)
		{
			if (ret > 0)
			{
				if (p > 0)
				{
					printf("#%d\tROW: %d\t(%d)\n", _id, p, ret);
				}
				else
				{
					printf("#%d\tCOL: %d\t(%d)\n", _id, -p, ret);
				}
			}
			else if (ret < 0)
			{
				if (p > 0)
				{
					printf("#%d\tROW: %d\tERROR\n", _id, p);
				}
				else
				{
					printf("#%d\tCOL: %d\tERROR\n", _id, -p);
				}

				return false;
			}
			else if (ret == 0)
			{
				if (_output_level == OUTPUT_ROUNDS)
				{
					if (p > 0)
					{
						printf("#%d\tROW: %d\t(0)\n", _id, p);
					}
					else
					{
						printf("#%d\tCOL: %d\t(0)\n", _id, -p);
					}
				}
			}
		}


		if (ret < 0)
		{
			if (_output_level >= OUTPUT_STEPS)
			{
				printf("\tFAILED\n");
			}
			return false;
		}

		_todo.pop();
	}

	return true;
}





std::vector<Board *> Board::createCandidates() const
{
	vector<Board *> retVal;

	//TODO
	//找到最合适的点
	for (unsigned long r = 0; r < _row_size; r++)
	{
		for (unsigned long c = 0; c < _col_size; c++)
		{
			if (getValue(r, c) == VAL_UNKNOWN)
			{
				return createCandidates(r, c);
			}
		}
	}
}



std::vector<Board *> Board::createCandidates(unsigned long row, unsigned long col) const
{
	vector<Board *> retVal;
	map<char, int> candidates;

	//long a = row_id(row);
//	map<long, Line *>::const_iterator tttr = _lines.find(row_id(row));
//	Line * l = _lines[row_id(row)];
//	map<char, int> ttt = tttr->second->getCandidateValue(col);
	//map<char, int> tr = _lines[row_id(row)]->getCandidateValue(col);
	map<char, int> tr = _lines.find(row_id(row))->second->getCandidateValue(col);

	for (map<char, int>::const_iterator it1 = tr.begin(); it1 != tr.end(); ++it1)
	{
		if (candidates.find(it1->first) == candidates.end())
		{
			candidates.insert(pair<char, int>(it1->first, it1->second));
		}
		else
		{
			candidates[it1->first] += it1->second;
		}
	}

	map<char, int> tc = _lines.find(col_id(col))->second->getCandidateValue(row);
	//map<char, int> tc = _lines[col_id(col)]->getCandidateValue(row);
	for (map<char, int>::const_iterator it2 = tc.begin(); it2 != tc.end(); ++it2)
	{
		if (candidates.find(it2->first) == candidates.end())
		{
			candidates.insert(pair<char, int>(it2->first, it2->second));
		}
		else
		{
			candidates[it2->first] += it2->second;
		}
	}

	int v = 1;
	for (map<char, int>::const_iterator it = candidates.begin(); it != candidates.end(); ++it)
	{
		Board * board = new Board(*this);
		board->_output_level = OUTPUT_RESULT;
		board->install(row, col, it->first);
		board->_output_level = _output_level;

		board->_id = _id * 10 + v++;

		if (_output_level >= OUTPUT_TRIES)
		{
			printf("#%d\tTRY [%lu, %lu] = (%c) -> #%d\n", _id, row + 1, col + 1, it->first, board->_id);
		}
			
		retVal.push_back(board);
	}

	return retVal;

}


void Board::print(FILE * output) const
{
	if (_id > 1)
	{
		fprintf(output, "-= %d =-\n", _id);
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
