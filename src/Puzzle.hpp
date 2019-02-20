#ifndef Puzzle_hpp
#define Puzzle_hpp

#include "Param.hpp"




/**
谜题
	支持从谜题文件读入
	支持从操作文件读入
*/
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
	//加载谜题文件
	bool load_puzzle_file(const char *);
	
	//加载解题文件
	bool load_installed_file(const char *);

public:
	//全部列的参数
	inline
	const ParamsOfLines & getParamsOnCols() const
	{
		return _params_of_cols;
	}

	//全部行的参数
	inline
	const ParamsOfLines & getParamsOnRows() const
	{
		return _params_of_rows;
	}


private:
	ParamsOfLines		_params_of_cols;
	ParamsOfLines		_params_of_rows;


};


#endif