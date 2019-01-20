//
//	main.cpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#include <iostream>
#include "io.hpp"


int main(int argc, const char * argv[])
{
	vector<vector<Param>> col_param;
	vector<vector<Param>> row_param;
	read_puzzle_file(argv[1], col_param, row_param);
	
	output_param_vec(col_param);
	printf("/\n");
	output_param_vec(row_param);

	return 0;
}
