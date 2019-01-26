/*
游戏本体
所有外部功能最终都是通过调用本类完成
内部支持多颜色机制
*/
#ifndef Game_hpp
#define Game_hpp

#include "Point.hpp"
#include "Param.hpp"
#include "Board.hpp"

#include <vector>
#include <list>
#include <map>




//游戏类
class Game
{
public:
	//构造一个空的游戏
	//只有行和列，不含任何内容
	//Game(int row_size, int col_size);
	
	//从参数构建新游戏
	Game(const std::vector<std::vector<Param>> & col_params, const std::vector<std::vector<Param>> & row_params);
	

	//拷贝构造
	Game(const Game &);
	//析构
	~Game();
	
	//赋值运算符
	Game & operator=(const Game &);
	
private:
	//释放所有资源
	void free();
	//从另一个复制过来
	void copy(const Game &);
	
	
public:
	
	//设定一个点为具体值
	//影响到所有的board
	bool install(int row, int col, char val);
	
	//解谜 走一步
	bool solve();
	
	//解谜 走完所有凭逻辑能走的
	bool solveAllByLogic();
	
	//解谜 走完所有
	bool solveAll();

private:
	//列数
	int _col_size;
	//行数
	int _row_size;
	
	
	//board列表
	//每个board都是有可能的
	//等待剪枝
	std::list<Board *> _boards;
	
};


#endif
