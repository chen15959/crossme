#include <stdio.h>

#include "Board.hpp"
#include "CandidateFactory.hpp"
#include "Game.hpp"
#include "Puzzle.hpp"
#include "Clock.hpp"
#include "util.hpp"





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

	int log_level = -1;
	int display_level = -1;
	int stop_after_n = 10;
	FILE * result_asap = NULL;


	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "--log:step") == 0)
		{
			log_level = max(log_level, LOG_STEP);
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
			display_level = max(display_level, DISPLAY_ROUND);
			continue;
		}

		if (strcmp(argv[i], "--display:try") == 0)
		{
			display_level = max(display_level, DISPLAY_TRY);
			continue;
		}

		if (strcmp(argv[i], "--display:result") == 0)
		{
			display_level = max(display_level, DISPLAY_RESULT);
			continue;
		}
		
		if (strcmp(argv[i], "--display:nothing") == 0)
		{
			display_level = max(display_level, DISPLAY_NOTHING);
			continue;
		}

#ifdef _DEBUG
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
#endif		

		if (sscanf(argv[i], "--stop-after:%d", &stop_after_n) == 1)
		{
			continue;
		}
		
		if (strcmp(argv[i], "--find-all") == 0)
		{
			stop_after_n = -1;
			continue;
		}
		
		if (strcmp(argv[i], "--result-asap") == 0)
		{
			result_asap = stdout;
			continue;
		}
	}
	

	//Ä¬ÈÏÊä³öÅäÖÃ
	if (log_level < 0)
	{
		log_level = LOG_PROGRESS;
	}
	
	if (display_level < 0)
	{
		display_level = DISPLAY_RESULT;
	}


	puzzle.load_puzzle_file(argv[1]);

	Game game(puzzle.getParamsOnCols().size(), puzzle.getParamsOnRows().size(), log_level, display_level);
	
	game.setStopAfter(stop_after_n);
	game.setResultAsSoonAsPosslbie(result_asap);

	Clock clock;
	clock.start();
//	unsigned long long t1 = now_ms();

	game.install(puzzle.getParamsOnCols(), puzzle.getParamsOnRows());

	game.play();


//	unsigned long long t2 = now_ms();
	clock.stop();

	game.write(stdout);

	printf("\n\nit costs %lu ms.\n", clock.elapsed_ms());

	return 0;
}
	
