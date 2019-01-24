#include "io.hpp"

#include <stdio.h>

#include "Board.hpp"


int main(int argc, const char * argv[])
{
	ParamsOfLines col_param;
	ParamsOfLines row_param;

	read_puzzle_file(argv[1], col_param, row_param);
	
	Board board(col_param.size(), row_param.size());
	board.install(col_param, row_param);
	
	output_param_of_lines(col_param);
	printf("/\n");
	output_param_of_lines(row_param);

	return 0;
}
