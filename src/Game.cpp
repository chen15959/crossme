#include "Game.hpp"

#include <assert.h>

#ifdef game



Game::Game(const std::vector<std::vector<Param>> & col_params, const std::vector<std::vector<Param>> & row_params)
{
	assert(col_params.size() > 0);
	assert(row_params.size() > 0);
	
	this->_col_size = col_params.size();
	this->_row_size = row_params.size();
	
	this->_boardsTodo.push(new Board(this->_col_size, this->_row_size);
	
	this->_boardsTodo.top().install(col_params, row_params);
}
	
	

	//拷贝构造
Game::Game(const Game & other)
{
	copy(other);
}


Game::~Game()
{
	free();
}


void Game::free()
{
	while (!this->_boardsTodo.empty())
	{
		delete this->_boardsTodo.top();
		this->_boardsTodo.pop();
	}
	
	while (!this->_boardsDone.size() > 0)
	{
		delete this->_boardsDone.back();
		this->_boardsDone.pop_back();
	}
}


void Game::copy(const Game & other)
{
	//TODO
}
	
Game & Game::operator=(const Game & rhs)
{
	if (&rhs != this)
	{
		this->free();
		this->copy(rhs);
	}
	
	return *this;
}
	
private:
	//释放所有资源
	void free();
	//从另一个复制过来
	void copy(const Game &);
	
	
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
