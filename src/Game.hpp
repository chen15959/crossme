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


#ifdef game


//游戏本体
//所有外部功能最终都是通过调用本类完成
//内部支持多颜色机制
//
class Game
{
public:
	//从参数构建新游戏
	Game(const ParamsOfLines & col_params, const ParamsOfLines & row_params);
	//拷贝构造
	Game(const Game &);
	//析构
	virtual ~Game();
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
	bool install(int row, int col, char val);
	

	//开始运行
	bool play();
	

private:
	//列数
	size_t					_col_size;
	//行数
	size_t					_row_size;
	
	//待执行的Board
	std::queue<Board *>		_boardsTodo;
	//成功的Board
	std::vector<Board *>	_boardsDone;
	
};

#endif

#endif
