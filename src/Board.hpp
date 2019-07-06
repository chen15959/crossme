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
	Board(const ParamListCollection & col_params, const ParamListCollection & row_params, int log_level, int display_level);
	//拷贝构造
	Board(const Board &);
	//析构
	virtual ~Board();
	
	//赋值运算符
	Board & operator=(const Board &);
	
private:
	//建立基本的Point矩阵和Line列表，并置于初始状态
	void init();

	//释放资源
	void free();
	
	//复制内容
	void copy(const Board &);
	
		
public:
	//使用参数来初始化
//	void install(const ParamListCollection & col_params, const ParamListCollection & row_params);
	
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
	VALUE_T value(LENGTH_T row, LENGTH_T col) const;

	//value的马甲
	inline
	VALUE_T getValue(LENGTH_T row, LENGTH_T col) const {
		return value(row, col);
	}
	

public:
	//点被改变的回调
	void point_change_callback(LENGTH_T row, LENGTH_T col, VALUE_T value);

	
private:
	Point **						_points;				//所有Point

	std::map<long, Line *>			_lines;					//所有行/列
	
	WeightQueue						_todo;					//待分析的行/列

	const ParamListCollection *		_params_of_cols;		//运行列参数
	const ParamListCollection *		_params_of_rows;		//运行行参数


private:
	//从行列号获得点的实际位置
	inline
	LENGTH2_T _index(LENGTH_T row, LENGTH_T col) const {
		return row * col_size() + col;
	}
	
	//归一化行号/列号
	inline
	long _col_id(LENGTH_T col) const {
		return -col - 1;
	}

	//归一化行号/列号
	inline
	long _row_id(LENGTH_T row) const {
		return row + 1;
	}


public:
	
	//行数量
	inline
	LENGTH_T row_size() const {
		return _params_of_rows->size();
	}

	//列数量
	inline
	LENGTH_T col_size() const {
		return _params_of_cols->size();
	}


public:
	//棋盘id
	inline
	const char * id() const {
		return _id.c_str();
	}


	//输出结果
	//	output		输出到哪个文件流 默认stdout
	//	head		是否输出棋盘标题 默认不输出
	void print(FILE * output = stdout, bool head = false) const;


	//日志等级
	inline 
	int log_level() const {
		return _log_level;
	}


	//显示等级
	inline
	int display_level() const {
		return _display_level;
	}

private:
	std::string			_id;					//棋盘id
	int					_log_level;				//日志等级
	int					_display_level;			//显示等级


public:
	//棋盘中有多少确定点
	SIZE_T known() const;




};


#endif
