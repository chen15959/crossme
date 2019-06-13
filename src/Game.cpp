#include "Game.hpp"

#include <assert.h>
using namespace std;




Game::Game(LENGTH_T col_size, LENGTH_T row_size, int log_level, int display_level)
{
	assert(col_size > 0);
	assert(row_size > 0);
	
	_col_size = col_size;
	_row_size = row_size;

	display_level = min(log_level, display_level);
	
	_todo.push_back(new Board(_col_size, _row_size, log_level, display_level));

	_installed = false;

	_stop_after = 0;
	_result_as_soon_as_possible = NULL;
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
	


bool Game::install(const ParamListCollection & col_params, const ParamListCollection & row_params)
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



bool Game::install(LENGTH_T row, LENGTH_T col, VALUE_T value)
{
	for (list<Board *>::const_iterator it1 = _todo.begin(); it1 != _todo.end(); ++it1)
	{
		(*it1)->install(row, col, value);
	}

	return true;
}
	


bool Game::play()
{
	while (!_todo.empty() && ((_stop_after > 0 && _done.size() < _stop_after) || _stop_after <= 0))
	{
		Board * board = *(_todo.begin());
		_todo.pop_front();

		board->play();
		if (board->isDone())
		{
			if (board->log_level() >= LOG_RESULT)
			{
				printf("#%s\tSUCCEEDED\n", board->id());
			}

			Result * result = new Result(*board);

			if (_result_as_soon_as_possible)
			{
				result->print(_result_as_soon_as_possible);
				delete result;
			}
			else if (board->display_level() >= DIS_RESULT)
			{
				_done.push_back(new Result(*board));
			}
			else
			{
				delete result;
			}
		}
		else if (board->isError())
		{
			if (board->log_level() >= LOG_PROGRESS)
			{
				printf("#%s\tFAILED\n", board->id());
			}
		}
		else
		{
			if (board->log_level() >= LOG_PROGRESS)
			{
				printf("#%s\t%lu/%lu\n", board->id(), board->known(), _col_size * _row_size);
			}
			if (board->display_level() >= DIS_TRY)
			{
				board->print(stdout, true);
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
