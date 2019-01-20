//
//	io.hpp
//	emssroc
//
//	Created by chen.zhang on 2019/1/13.
//	Copyright © 2019 chen.zhang. All rights reserved.
//

#ifndef io_hpp
#define io_hpp

#include <vector>
using namespace std;

#include "Param.hpp"
#include "Board.hpp"



bool read_puzzle_file(const char * filename, vector<vector<Param>> & col_param, vector<vector<Param>> & row_param);

void output_param_vec(const vector<vector<Param>> & param_vec, FILE * output = stdout);


#endif /* io_hpp */
