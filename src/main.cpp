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


int max(int a, int b)
{
	return a > b ? a : b;
}



double factor_ax = -1;
double factor_bx = 0.5;
double factor_cx = 1.5;
double factor_ay = 0;
double factor_by = 0;
double factor_cy = 0;
//0,5,1,?,?,?


int main(int argc, const char * argv[])
{
	Puzzle puzzle;

	int log_level = LOG_PROGRESS;
	int display_level = DIS_RESULT;
	int stop_after_found_n = 10;
	FILE * result_asap = NULL;


	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "--log:step") == 0)
		{
			log_level = max(log_level, LOG_TRY);
			continue;
		}

		if (strcmp(argv[i], "--log:round") == 0)
		{
			log_level = max(log_level, LOG_ROUND);
			continue;
		}

		if (strcmp(argv[i], "--log:try") == 0)
		{
			log_level = max(log_level, LOG_TRY);
			continue;
		}

		if (strcmp(argv[i], "--log:progress") == 0)
		{
			log_level = max(log_level, LOG_PROGRESS);
			continue;
		}

		if (strcmp(argv[i], "--log:result") == 0)
		{
			log_level = max(log_level, LOG_RESULT);
			continue;
		}
		
		if (strcmp(argv[i], "--log:nothing") == 0)
		{
			log_level = max(log_level, LOG_NOTHING);
			continue;
		}

		if (strcmp(argv[i], "--display:round") == 0)
		{
			display_level = max(display_level, DIS_ROUND);
			continue;
		}

		if (strcmp(argv[i], "--display:try") == 0)
		{
			display_level = max(display_level, DIS_TRY);
			continue;
		}

		if (strcmp(argv[i], "--display:result") == 0)
		{
			display_level = max(display_level, DIS_RESULT);
			continue;
		}
		
		if (strcmp(argv[i], "--display:nothing") == 0)
		{
			display_level = max(display_level, DIS_NOTHING);
			continue;
		}


		if (sscanf(argv[i], "--factor-ax:%lf", &factor_ax) == 1)
		{
			continue;
		}

		if (sscanf(argv[i], "--factor-bx:%lf", &factor_bx) == 1)
		{
			continue;
		}

		if (sscanf(argv[i], "--factor-cx:%lf", &factor_cx) == 1)
		{
			continue;
		}

		if (sscanf(argv[i], "--factor-ay:%lf", &factor_ax) == 1)
		{
			continue;
		}

		if (sscanf(argv[i], "--factor-by:%lf", &factor_bx) == 1)
		{
			continue;
		}

		if (sscanf(argv[i], "--factor-cy:%lf", &factor_cx) == 1)
		{
			continue;
		}
		
		if (sscanf(argv[i], "--stop-after-found:%d", &stop_after_found_n) == 1)
		{
			continue;
		}
		
		if (strcmp(argv[i], "--result-asap") == 0)
		{
			result_asap = stdout;
			continue;
		}
	}


	puzzle.load_puzzle_file(argv[1]);

	Game game(puzzle.getParamsOnCols().size(), puzzle.getParamsOnRows().size(), log_level, display_level);
	
	game.setStopAfterFound(stop_after_found_n);
	game.setResultAsSoonAsPosslbie(result_asap);

	
	unsigned long long t1 = now_ms();

	game.install(puzzle.getParamsOnCols(), puzzle.getParamsOnRows());

	game.play();


	unsigned long long t2 = now_ms();

	game.write(stdout);

	printf("\n\nit costs %lu ms.\n", (unsigned long)(t2 - t1));

	return 0;
}
	
