#include "io.hpp"

#include <stdio.h>
#include <windows.h>

#include "Board.hpp"
#include "CandidateFactory.hpp"
#include "Game.hpp"
#include "Puzzle.hpp"



int main(int argc, const char * argv[])
{
/*
	ParamsOfLines col_param;
	ParamsOfLines row_param;

	read_puzzle_file(argv[1], col_param, row_param);
	
	Board board(col_param.size(), row_param.size());
	board.install(col_param, row_param);
	
	output_param_of_lines(col_param);
	printf("/\n");
	output_param_of_lines(row_param);
*/
/*
	ParamsOfLine pol;
	pol.push_back(Param(2));
	pol.push_back(Param(1));
	pol.push_back(Param(3));

	CandidateFactory cf;
	CandidateList * cl = cf.createCandidateList(10, pol);
	cl->print();
*/
	Puzzle puzzle;
	puzzle.load_puzzle_file(argv[1]);

//	ParamsOfLines col_param;
//	ParamsOfLines row_param;

//	read_puzzle_file(argv[1], col_param, row_param);

	Game game(puzzle.getParamsOnCols().size(), puzzle.getParamsOnRows().size());

	unsigned long t1 = ::GetTickCount();

	//Board board(col_param.size(), row_param.size());
	game.install(puzzle.getParamsOnCols(), puzzle.getParamsOnRows());
	//game.install(col_param, row_param);

	game.play();


	unsigned long t2 = ::GetTickCount();

	game.write(stdout);

	printf("\n\n\n\nit costs %lu ms.\n", t2 - t1);

	//board.write();





	return 0;
}
