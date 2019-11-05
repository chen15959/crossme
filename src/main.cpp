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


// 程序主入口点

int main(int argc, const char * argv[])
{
	// 谜题
	Puzzle puzzle;

	//运行时参数及默认值
	int log_level = LOG_NOTHING;
	int display_level = DISPLAY_RESULT;
	int stop_after_n = 10, t_stop_after_n;
	bool find_all = false;
	bool show_clock = true;
	FILE * result_asap = NULL;


	for (int i = 2; i < argc; ++i)
	{

#ifndef 日志和显示
		//当同时有多个日志指令时，以其中最细那个为准
		//默认不显示日志

		//日志级别设为最细（每一步）
		if (strcmp(argv[i], "--log:step") == 0)
		{
			log_level = max(log_level, LOG_STEP);
			continue;
		}

		//日志级别设为次细（每一轮）
		if (strcmp(argv[i], "--log:round") == 0)
		{
			log_level = max(log_level, LOG_ROUND);
			continue;
		}

		//日志级别设为中等（每一次尝试）
		if (strcmp(argv[i], "--log:try") == 0)
		{
			log_level = max(log_level, LOG_TRY);
			continue;
		}

		//日志级别设为次粗（只有进度）
		if (strcmp(argv[i], "--log:progress") == 0)
		{
			log_level = max(log_level, LOG_PROGRESS);
			continue;
		}

		//日志级别设为最粗（只有成功信息）
		if (strcmp(argv[i], "--log:result") == 0)
		{
			log_level = max(log_level, LOG_RESULT);
			continue;
		}
		
		//禁用日志输出
		if (strcmp(argv[i], "--log:nothing") == 0)
		{
			log_level = max(log_level, LOG_NOTHING);
			continue;
		}


		//当同时存在多个显示配置时，以最细那个为准
		//默认只显示结果
		//如果存在--display:nothing的话，则以他为准

		//在每一轮结束的时候都显示一下盘面（最细）
		if (strcmp(argv[i], "--display:round") == 0)
		{
			display_level = max(display_level, DISPLAY_ROUND);
			continue;
		}

		//在每一次尝试结束的时候都显示一下盘面（一般）
		if (strcmp(argv[i], "--display:try") == 0)
		{
			display_level = max(display_level, DISPLAY_TRY);
			continue;
		}

		//只显示结果（最粗）
		if (strcmp(argv[i], "--display:result") == 0)
		{
			display_level = max(display_level, DISPLAY_RESULT);
			continue;
		}
		
		//什么都不显示
		if (strcmp(argv[i], "--display:nothing") == 0)
		{
			display_level = DISPLAY_NOTHING;
			continue;
		}
#endif

#ifdef _DEBUG
		//这里是莽的时候的寻优参数
		//一般不需要调整
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

#ifndef 谜题多结果控制

		//如果是多结果的谜题，找到多少个之后就停止
		//默认10个
		if (sscanf(argv[i], "--stop-after:%d", &t_stop_after_n) == 1)
		{
			if (t_stop_after_n > 0)
			{
				stop_after_n = max(stop_after_n, t_stop_after_n);
			}
			else
			{
				find_all = true;
			}
			continue;
		}
		
		//出现此参数时，强制找到所有结果
		//忽略--stop-after:n参数
		if (strcmp(argv[i], "--find-all") == 0)
		{
			find_all = true;
			continue;
		}

#endif

		//是否得到一个结果就马上输出
		if (strcmp(argv[i], "--result-asap") == 0)
		{
			result_asap = stdout;
			continue;
		}

		//显示计时（默认）
		if (strcmp(argv[i], "--show-clock") == 0)
		{
			show_clock = true;
			continue;
		}

		//不显示计时
		if (stricmp(argv[i], "--hide-clock") == 0)
		{
			show_clock = false;
			continue;
		}
	}
	

	//默认输出配置
	if (log_level < 0)
	{
		log_level = LOG_PROGRESS;
	}
	
	if (display_level < 0)
	{
		display_level = DISPLAY_RESULT;
	}


	//第一个参数必须是谜题文件
	puzzle.load_puzzle_file(argv[1]);

	//从谜题文件构建游戏
	Game game(puzzle.getParamsOnCols(), puzzle.getParamsOnRows(), log_level, display_level);
	
	//游戏的设置
	game.setStopAfter(find_all ? -1 : stop_after_n);
	game.setResultAsSoonAsPosslbie(result_asap);

	//开始计时
	Clock clock;
	clock.start();

	//游戏开始
	game.play();

	//计时结束
	clock.stop();

	//一次性输出所有结果（如果没选result-asap）
	game.write(stdout);

	//输出计时
	if (show_clock)
	{
		printf("\n\nit costs %lu ms.\n", clock.elapsed_ms());
	}

	return 0;
}
	
