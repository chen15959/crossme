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
	char getValue(short pos) const;

	inline
	char value(short pos) const
	{
		return getValue(pos);
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
	//判断是否和已经存在的Line兼容
	bool operator==(const Line & rhs) const;
	inline
	bool operator!=(const Line & rhs) const
	{
		return !(*this == rhs);
	}



private:
	//数据内容
	char *			_data;
	//数据长度
	short			_length;
};


#endif
