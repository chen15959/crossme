#ifndef Candidate_hpp
#define Candidate_hpp

class Line;




//行的候选可能
//
class Candidate
{
public:
	//构造函数
	//用数组初始化
	Candidate(short length, const char * buffer);

	//初始化为全都是一个值
	Candidate(short length, char value = '\0');

	//拷贝构造
	Candidate(const Candidate &);
	//析构函数
	virtual ~Candidate();
	//赋值运算符
	Candidate & operator=(const Candidate &);
	
	
private:
	void copy(const Candidate &);
	void free();

public:
	//获得某个位置上的值
	//inline
	char getValue(short pos) const;

	//以字符串形式获得内容
	inline
	const char * getValue() const
	{
		return _data;
	}
	
	inline
	short getLength() const
	{
		return _length;
	}

	inline
	short length() const
	{
		return _length;
	}
	


public:
	//相当于两个做一次合并，相同的保留原值，不同的记为VAL_UNKNOWN
	Candidate & operator+=(const Candidate & rhs);
	Candidate operator+(const Candidate & rhs) const;

	//判断一个是否和已经存在的Line兼容
	bool operator==(const Line &) const;
	bool operator!=(const Line &) const;

	//判断一个是否和另一个相同
	bool operator==(const Candidate &) const;
	bool operator!=(const Candidate &) const;


private:
	//数据内容
	char *			_data;
	//数据长度
	short			_length;
};


#endif
