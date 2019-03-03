#include "Game.hpp"

#include <assert.h>
using namespace std;




Game::Game(unsigned long col_size, unsigned long row_size, int log_level, int display_level)
{
	assert(col_size > 0);
	assert(row_size > 0);
	
	_col_size = col_size;
	_row_size = row_size;

	display_level = min(log_level, display_level);
	
	_todo.push_back(new Board(_col_size, _row_size, log_level, display_level));

	_installed = false;
}
	
	

//拷贝构造
Game::Game(const Game & other)
{
	assert(0);
//	copy(other);
}


Game::~Game()
{
	free();
}


void Game::free()
{
	for (list<Board *>::const_iterator it1 = _todo.begin(); it1 != _todo.end(); ++it1)
	{
		delete *it1;
	}
	
	for (list<Result *>::const_iterator it2 = _done.begin(); it2 != _done.end(); ++it2)
	{
		delete *it2;
	}
}



void Game::copy(const Game & other)
{
	assert(0);
	//TODO
}


Game & Game::operator=(const Game & rhs)
{
	if (&rhs != this)
	{
		free();
		copy(rhs);
	}
	
	return *this;
}
	


bool Game::install(const ParamsOfLines & col_params, const ParamsOfLines & row_params)
{
	if (!_installed)
	{
		(*(_todo.begin()))->install(col_params, row_params);
		_installed = true;
		return true;
	}
	else
	{
		return false;
	}
}



bool Game::install(unsigned long row, unsigned long col, char value)
{
	for (list<Board *>::const_iterator it1 = _todo.begin(); it1 != _todo.end(); ++it1)
	{
		(*it1)->install(row, col, value);
	}

	return true;
}
	


bool Game::play()
{
	while (!_todo.empty())
	{
		Board * board = *(_todo.begin());
		_todo.pop_front();

		board->play();
		if (board->isDone())
		{
			_done.push_back(new Result(*board));

			if (board->log_level() >= LOG_TRY)
			{
				printf("#%s\tSUCCEEDED\n", board->id());
			}
		}
		else if (board->isError())
		{
			if (board->log_level() >= LOG_TRY)
			{
				printf("#%s\tFAILED\n", board->id());
			}
		}
		else
		{
			if (board->log_level() >= LOG_TRY)
			{
				printf("#%s\t%lu/%lu\n", board->id(), board->known(), _col_size * _row_size);
				if (board->display_level() >= DIS_TRY)
				{
					board->print(stdout, true);
				}
			}

			vector<Board *> newBoards = board->createCandidates();
			for (vector<Board *>::const_iterator it = newBoards.begin(); it != newBoards.end(); ++it)
			{
				_todo.push_back(*it);
			}
		}
		
		delete board;
	}

	return true;
}



void Game::write(FILE * output) const
{

	for (list<Result *>::const_iterator it = _done.begin(); it != _done.end(); ++it)
	{
		(*it)->print(output);
	}


}
