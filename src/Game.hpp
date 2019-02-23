#ifndef Game_hpp
#define Game_hpp

#include "Point.hpp"
#include "Param.hpp"
#include "Board.hpp"

#include <vector>
#include <list>
#include <vector>
#include <queue>
#include <map>



//游戏本体
//所有外部功能最终都是通过调用本类完成
//内部支持多颜色机制
//
class Game
{
public:
	//从参数构建新游戏
	Game(unsigned long col_size, unsigned long row_size, int log_level = 0, int display_level = 0);
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

	bool install(const ParamsOfLines & col_params, const ParamsOfLines & row_params);
	
	//设定一个点为具体值
	//影响到所有的board
	bool install(unsigned long row, unsigned long col, char val);
	

	//开始运行
	bool play();
	

private:
	//列数
	unsigned long			_col_size;
	//行数
	unsigned long			_row_size;
	
	//待执行的Board
	std::list<Board *>		_todo;
	//成功的Board
	std::list<Board *>		_done;

	bool					_installed;


public:
	void write(FILE * output) const;
	
};

#endif

