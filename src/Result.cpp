#include "Result.hpp"

#include <stdlib.h>
#include <string.h>
#include <assert.h>




Result::Result(const Board & board)
: _col_size(board.col_size()), _row_size(board.row_size()), _id(board.id())
{
	_data = new VALUE_T[_col_size * _row_size];
	
	for (LENGTH_T c = 0; c < _col_size; ++c)
	{
		for (LENGTH_T r = 0; r < _row_size; ++r)
		{
			_data[getIndex(r, c)] = board.getValue(r, c);
		}
	}
}



Result::~Result()
{
	free();
}



Result::Result(const Result & other)
{
	copy(other);
}



Result & Result::operator=(const Result & other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}



void Result::copy(const Result & other)
{
	_id = other._id;
	_row_size = other._row_size;
	_col_size = other._col_size;
	
	_data = new VALUE_T[_col_size * _row_size];
	memcpy(_data, other._data, sizeof(VALUE_T) * _col_size * _row_size);
}



void Result::free()
{
	delete [] _data;
}



VALUE_T Result::getValue(LENGTH_T row, LENGTH_T col) const
{
	assert(0 <= row && row < _row_size);
	assert(0 <= col && col < _col_size);
	
	return _data[getIndex(row, col)];
}



void Result::print(FILE *output)
{
	if (_id.length() > 0)
	{
		fprintf(output, "-= %s =-\n", _id.c_str());
	}
	
	for (LENGTH_T row = 0; row < _row_size; ++row)
	{
		if (row % 5 == 0)
		{
			fprintf(output, "\n");
		}
			
		for (LENGTH_T col = 0; col < _col_size; ++col)
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

