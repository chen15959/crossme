#ifndef Puzzle_hpp
#define Puzzle_hpp

#include "Param.hpp"

#include <vector>




class Puzzle
{
public:
	Puzzle(bool col_params_first = true);
	virtual ~Puzzle();

	Puzzle(const Puzzle &);
	Puzzle & operator=(const Puzzle &);

private:
	void copy(const Puzzle &);
	void free();


public:
	bool load_puzzle_file(const char *);
	bool load_installed_file(const char *);

public:
	inline
	const ParamsOfLines & getParamsOnCols() const
	{
		return _params_of_cols;
	}

	inline
	const ParamsOfLines & getParamsOnRows() const
	{
		return _params_of_rows;
	}


private:
	ParamsOfLines		_params_of_cols;
	ParamsOfLines		_params_of_rows;


/*
private:

	class params_stream_handler
	{
	public:
		params_stream_handler(ParamsOfLines * params);
		virtual ~params_stream_handler();

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


private:
	params_stream_handler		_first;
	params_stream_handler		_second;
	params_stream_handler *		_current;



private:
	inline void put(char ch)
	{
		_current->put(ch);
	}

	inline void finishItem()
	{
		_current->finishItem();
	}


	inline void finishLine()
	{
		_current->finishLine();
	}


	inline void changeMode()
	{
		_current = &_second;
	}
*/

};


#endif