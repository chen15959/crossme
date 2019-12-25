#include "Game.hpp"

#include <assert.h>
using namespace std;




Game::Game(const ParamListCollection & col_params, const ParamListCollection & row_params)
: _params_of_cols(col_params), _params_of_rows(row_params)
{
	assert(col_params.size() > 0);
	assert(row_params.size() > 0);
	
	//默认参数
	_log_level = LOG_NOTHING;
	_display_level = DISPLAY_RESULT;
	_stop_after = 0;
	_result_as_soon_as_possible = NULL;
}
	
	

//拷贝构造
//禁用
Game::Game(const Game & other)
: _params_of_cols(other._params_of_cols), _params_of_rows(other._params_of_rows)
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



//禁用
void Game::copy(const Game & other)
{
	assert(0);
	//TODO
}


//禁用
Game & Game::operator=(const Game & rhs)
{
	if (&rhs != this)
	{
		free();
		copy(rhs);
	}
	
	return *this;
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
	//生成第一个棋盘
	//放到待处理队列中
	Board * board = new Board(_params_of_cols, _params_of_rows, _log_level,  min(_log_level, _display_level));
	
	_todo.push_back(board);



	while (!_todo.empty() && ((_stop_after > 0 && _done.size() < _stop_after) || _stop_after <= 0))
	{
		//抓出一个棋盘
		Board * board = *(_todo.begin());
		_todo.pop_front();

		//在棋盘层面上走一轮
		board->play();

		if (board->isDone())
		{
			//成功了
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
			else if (board->display_level() >= DISPLAY_RESULT)
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
			//失败了
			if (board->log_level() >= LOG_PROGRESS)
			{
				printf("#%s\tFAILED\n", board->id());
			}
		}
		else
		{
			//僵局了，莽一波
			if (board->log_level() >= LOG_PROGRESS)
			{
				printf("#%s\t%lu/%lu\n", board->id(), board->known(), _params_of_rows.size() * _params_of_cols.size());
			}
			if (board->display_level() >= DISPLAY_TRY)
			{
				board->print(stdout, true);
			}
						
			vector<Board *> newBoards = board->createCandidates();
			for (vector<Board *>::const_iterator it = newBoards.begin(); it != newBoards.end(); ++it)
			{
				_todo.push_back(*it);
			}
		}
		
		//删除旧的
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
