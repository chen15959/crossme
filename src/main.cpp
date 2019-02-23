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

	int log_level = 0; //default
	int display_level = 0;


	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "--log:step") == 0)
		{
			log_level = max(log_level, LOG_TRY);
		}

		if (strcmp(argv[i], "--log:round") == 0)
		{
			log_level = max(log_level, LOG_ROUND);
		}

		if (strcmp(argv[i], "--log:try") == 0)
		{
			log_level = max(log_level, LOG_TRY);
		}

		if (strcmp(argv[i], "--log:result") == 0)
		{
			log_level = max(log_level, LOG_RESULT);
		}

		if (strcmp(argv[i], "--display:round") == 0)
		{
			display_level = max(display_level, DIS_ROUND);
		}

		if (strcmp(argv[i], "--display:try") == 0)
		{
			display_level = max(display_level, DIS_TRY);
		}

		if (strcmp(argv[i], "--display:result") == 0)
		{
			display_level = max(display_level, DIS_RESULT);
		}
	}


	puzzle.load_puzzle_file(argv[1]);

	Game game(puzzle.getParamsOnCols().size(), puzzle.getParamsOnRows().size(), log_level, display_level);

	unsigned long long t1 = now_ms();

	game.install(puzzle.getParamsOnCols(), puzzle.getParamsOnRows());

	game.play();


	unsigned long long t2 = now_ms();

	game.write(stdout);

	printf("\n\nit costs %lu ms.\n", (unsigned long)(t2 - t1));

	return 0;
}
	
