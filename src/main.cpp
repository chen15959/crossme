//#include "io.hpp"

#include <stdio.h>
#include <windows.h>

#include "Board.hpp"
#include "CandidateFactory.hpp"
#include "Game.hpp"
#include "Puzzle.hpp"



int main(int argc, const char * argv[])
{

	Puzzle puzzle;
	puzzle.load_puzzle_file(argv[1]);


	Game game(puzzle.getParamsOnCols().size(), puzzle.getParamsOnRows().size(), 10);

	unsigned long t1 = ::GetTickCount();

	game.install(puzzle.getParamsOnCols(), puzzle.getParamsOnRows());

	game.play();


	unsigned long t2 = ::GetTickCount();

	game.write(stdout);

	printf("\n\n\n\nit costs %lu ms.\n", t2 - t1);

	return 0;
}
	