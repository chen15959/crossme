#ifndef Board_hpp
#define Board_hpp

#include "Param.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "WeightQueue.hpp"

#include <string>


#define LOG_NOTHING				0		//什么都不输出
#define LOG_RESULT				1		//只输出结果
#define LOG_PROGRESS			2		//输出进度
#define LOG_TRY					3		//输出每一次尝试
#define LOG_ROUND				4		//输出每一轮的情况
#define LOG_STEP				5		//输出每一个点的改变

#define DISPLAY_NOTHING			0		//从不输出结果盘面
#define DISPLAY_RESULT			1		//只输出结果盘面
#define DISPLAY_TRY				2		//在每次莽之前都输出盘面
#define	DISPLAY_ROUND			3		//每行/列上运算成功之后都输出盘面


/**
棋盘
*/
class Board
{
public:
	//构造函数
	//列数*行数
	Board(LENGTH_T col_size, LENGTH_T row_size, int log_level, int display_level);
	//拷贝构造
	Board(const Board &);
	//析构
	virtual ~Board();
	
	//赋值运算符
	Board & operator=(const Board &);
	
private:
	//建立基本的Point矩阵
	void init(LENGTH_T col_size, LENGTH_T row_size);
	//释放资源
	void free();
	//复制内容
	//此时不复制line上的可能性
	void copy(const Board &);
	
		
public:
	//使用参数来初始化
	void install(const ParamListCollection & col_params, const ParamListCollection & row_params);
	
	//强行设定某Point
	void install(LENGTH_T row, LENGTH_T col, VALUE_T value);


public:
	//走棋
	//返回true代表能走的都已经走完了
	//返回false代表发现逻辑冲突了
	bool play();


public:
	//是否已经完成
	bool isDone() const;

	//是否已经失败
	bool isError() const;
	
	//随机找一个不确定点，生成多种可能性
	std::vector<Board *> createCandidates() const;

private:
	//基于某点生成多种可能性
	std::vector<Board *> createCandidates(LENGTH_T row, LENGTH_T col) const;


public:
	//获得特定位置的点的值
	VALUE_T getValue(LENGTH_T row, LENGTH_T col) const;
	
	
public:
	//点被改变的回调
	void point_change_callback(LENGTH_T row, LENGTH_T col, VALUE_T value);
	
private:
	//列数
	LENGTH_T					_col_size;
	//行数
	LENGTH_T					_row_size;
	
	//所有Point
	Point **					_points;

	//所有行/列
	std::map<long, Line *>		_lines;

	//待分析的行/列
	WeightQueue					_todo;

	//运行参数
	ParamListCollection			_params_of_lines;


private:
	//从行列号获得点的实际位置
	inline
	LENGTH2_T _index(LENGTH_T row, LENGTH_T col) const {
		return row * _col_size + col;
	}
	
	inline
	long _col_id(LENGTH_T col) const {
		return -col - 1;
	}

	inline
	long _row_id(LENGTH_T row) const {
		return row + 1;
	}


public:

	inline
	const char * id() const {
		return _id.c_str();
	}

	inline
	LENGTH_T row_size() const {
		return _row_size;
	}


	inline
	LENGTH_T col_size() const {
		return _col_size;
	}


private:
	std::string			_id;


public:
	//输出结果
	void print(FILE * output, bool head = false) const;


	//输出等级
	inline 
	int log_level() const {
		return _log_level;
	}

	inline
	int display_level() const {
		return _display_level;
	}


private:
	int		_log_level;
	int		_display_level;


public:
	SIZE_T known() const;




};


#endif
