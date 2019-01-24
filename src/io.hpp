/*
控制输入输出
 * 读取puzzle文件
*/
#ifndef io_hpp
#define io_hpp

#include <vector>


#include "Param.hpp"
//class Param;
//#include "Board.hpp"
class Board;




//从puzzle文件中读取游戏输入
// filename			puzzle文件名
// col_param		所有列的参数
// row_param		所有行的参数
bool read_puzzle_file(const char * filename, ParamsOfLines & col_param, ParamsOfLines & row_param);


//将一条边上的参数全部输出（全部列的参数，或全部行的参数）
// params_of_lines	全部的参数
// output			输出流
void output_param_of_lines(const ParamsOfLines & params_of_lines, FILE * output = stdout);


#endif
