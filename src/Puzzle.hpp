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
	//先读列参数
	//不支持
	Puzzle(bool col_params_first = true);
	virtual ~Puzzle();

	Puzzle(const Puzzle &);
	Puzzle & operator=(const Puzzle &);

private:
	void copy(const Puzzle &);
	void free();


public:
	//加载谜题文件
	bool load_puzzle_file(const char * filename);
	
	//加载解题文件
	//未实现
	bool load_installed_file(const char * filename);

public:
	//全部列的参数
	inline
	const ParamListCollection & getParamsOnCols() const {
		return _params_of_cols;
	}

	//全部行的参数
	inline
	const ParamListCollection & getParamsOnRows() const {
		return _params_of_rows;
	}


private:
	ParamListCollection		_params_of_cols;
	ParamListCollection		_params_of_rows;
};


#endif