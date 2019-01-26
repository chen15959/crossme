//
//	Game.cpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/19.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#include "Game.hpp"

#include <assert.h>




Game::Game(const std::vector<std::vector<Param>> & col_params, const std::vector<std::vector<Param>> & row_params)
{
	assert(col_params.size() > 0);
	assert(row_params.size() > 0);
	
	this->_col_size = col_params.size();
	this->_row_size = row_params.size();
	
	this->_boards.push_back(new Board(this->_col_size, this->_row_size);
	
	this->_boards.begin().install
	
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
	for (list::<Board *>::const_iterator it1 = this->_boards.begin(); it1 != this->_boards.end(); ++it1)
	{
		delete *it1;
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
	
	//解谜 走一步
	bool solve();
	
	//解谜 走完所有凭逻辑能走的
	bool solveAllByLogic();
	
	//解谜 走完所有
	bool solveAll();

private:
	//board列表
	//每个board都是有可能的
	//等待剪枝
	std::list<Board *> m_boards;
