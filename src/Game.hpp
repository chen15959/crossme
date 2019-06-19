#ifndef Game_hpp
#define Game_hpp

#include "Point.hpp"
#include "Param.hpp"
#include "Board.hpp"
#include "Result.hpp"

#include <vector>
#include <list>
#include <vector>
#include <queue>
#include <map>



//游戏本体
//所有外部功能最终都是通过调用本类完成
//内部支持多颜色机制(not yet)
//
class Game
{
public:
	//从参数构建新游戏
	Game(const ParamListCollection & col_params, const ParamListCollection & row_params, int log_level = 0, int display_level = 0);
	//析构
	virtual ~Game();

	//拷贝构造
	Game(const Game &);
	//赋值运算符
	Game & operator=(const Game &);
	
private:
	//从另一个复制过来
	void copy(const Game &);
	//释放所有资源
	void free();
	
	
public:
	//设定一个点为具体值
	//影响到所有的board
	bool install(LENGTH_T row, LENGTH_T col, VALUE_T val);
	

	//开始运行
	bool play();
	

private:
	//各列参数
	const ParamListCollection &		_params_of_cols;
	//各行参数
	const ParamListCollection &		_params_of_rows;
	
	//待执行的Board
	std::list<Board *>		_todo;
	//成功的Board
	std::list<Result *>		_done;

public:
	inline
	void setStopAfter(int value) {
		_stop_after = value;
	}
	
	inline
	void setResultAsSoonAsPosslbie(FILE * value) {
		_result_as_soon_as_possible = value;
	}
	
	
private:
	//在多解时，找到n个解就停止
	//小于1代表找到所有再停止
	int _stop_after;
	
	FILE * _result_as_soon_as_possible;

public:
	void write(FILE * output) const;
	
};

#endif

