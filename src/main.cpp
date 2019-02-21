#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include "Board.hpp"
#include "CandidateFactory.hpp"
#include "Game.hpp"
#include "Puzzle.hpp"


unsigned long long now_ms()
{
#ifdef WIN32
	return GetTickCount();
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
#endif
}


int main(int argc, const char * argv[])
{

	Puzzle puzzle;
	puzzle.load_puzzle_file(argv[1]);


	Game game(puzzle.getParamsOnCols().size(), puzzle.getParamsOnRows().size(), OUTPUT_RESULT);

	unsigned long long t1 = now_ms();

	game.install(puzzle.getParamsOnCols(), puzzle.getParamsOnRows());

	game.play();


	unsigned long long t2 = now_ms();

	game.write(stdout);

	printf("\n\nit costs %lu ms.\n", (unsigned long)(t2 - t1));

	return 0;
}
	
