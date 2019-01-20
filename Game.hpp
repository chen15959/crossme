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


//游戏类
class Game
{
public:
	//
	Game(int row_size, int col_size);
	Game(const std::vector<std::vector<Param>> & col_params, const std::vector<std::vector<Param>> & row_params);
	


	Game(const Game &);
	~Game();
	
	Game & operator=(const Game &);
	
public:
	
	bool install(int row, int col, char val);
	
	

private:
	std::vector<Board *> m_boards;
	
};


#endif /* Game_hpp */
