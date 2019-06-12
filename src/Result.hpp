#ifndef Result_hpp
#define Result_hpp

#include "Board.hpp"

#include <stdio.h>




class Result
{
public:
	Result(const Board & board);
	virtual ~Result();
	
	Result(const Result & other);
	Result & operator=(const Result & other);
	
public:
	void copy(const Result & other);
	void free();
	

private:
	std::string	_id;
	short		_col_size;
	short		_row_size;
	VALUE_T *	_data;
	
	
public:
	inline
	std::string id() const {
		return _id;
	}

	VALUE_T getValue(short row, short col) const;
	
private:
	inline
	long getIndex(short row, short col) const {
		return row * this->_col_size + col;
	}
	
public:
	void print(FILE * output);

};

#endif



