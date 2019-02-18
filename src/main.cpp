#include "io.hpp"

#include <stdio.h>
#include <windows.h>

#include "Board.hpp"
#include "CandidateFactory.hpp"
#include "Game.hpp"



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

	ParamsOfLines col_param;
	ParamsOfLines row_param;

	read_puzzle_file(argv[1], col_param, row_param);

	Game game(col_param.size(), row_param.size());

	unsigned long t1 = ::GetTickCount();

	//Board board(col_param.size(), row_param.size());
	game.install(col_param, row_param);

	game.play();


	unsigned long t2 = ::GetTickCount();

	game.write(stdout);

	printf("\n\n\n\nit costs %lu ms.\n", t2 - t1);

	//board.write();





	return 0;
}
