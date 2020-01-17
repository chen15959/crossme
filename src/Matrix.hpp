#ifndef Matrix_hpp
#define Matrix_hpp

#include "def.hpp"

#include <string>
#include <vector>
#include <stdio.h>


#if 0
template<class T>
class Matrix
{
public:
	//����
	Matrix(void);

	//��������
	Matrix(const Matrix & other)
		: _id(other._id), _col_size(other._col_size), _row_size(other._row_size)
	{
		for (std::vector<T>::const_iterator it1 = other._data.begin(); it1 != other._data.end(); ++it1)
		{
			_data.push_back(T(*it1));
		}
	}


	//��ֵ����
	Matrix & operator=(const Matrix &);

	//����
	virtual ~Matrix();


private:
	void copy(const Matrix & other)
	{
//		_data = new T[_row_size * _col_size];
//		for (LENGTH_T r = 0; r < _row_size; ++r)
//		{
//			for (LENGTH_T c = 0; c < _col_size; ++c)
//			{
//				_data[_index(r, c)] = T(other(r,c));
//			}
//		}
	}

	void free()
	{

	}


private:
	std::string		_id;				//����
	LENGTH_T		_col_size;			//����
	LENGTH_T		_row_size;			//����
	std::vector<T>	_data;				//���ݣ�һά���飩
	
public:	
	//���id
	inline
	std::string id() const {
		return _id;
	}

	//������
	inline
	LENGTH_T row_size() const {
		return _row_size;
	}

	//������
	inline
	LENGTH_T col_size() const {
		return _col_size;
	}



	//���ĳһ��
	T value(LENGTH_T row, LENGTH_T col) const;

	//���ĳһ��
	inline
	T operator()(LENGTH_T row, LENGTH_T col) const {
		return value(row, col);
	}


	
private:
	//���ĳһ���Ӧ��ƫ����
	inline
	LENGTH2_T _index(LENGTH_T row, LENGTH_T col) const {
		return row * col_size() + col;
	}
	
public:
	//�����������output��
	void print(FILE * output);




public:
	

public:


	//������
	//	output		������ĸ��ļ��� Ĭ��stdout
	//	head		�Ƿ�������̱��� Ĭ�ϲ����
	void print(FILE * output = stdout, bool head = false) const;
};










Result::Result(const Board & board)
: _col_size(board.col_size()), _row_size(board.row_size()), _id(board.id())
{
	_data = new VALUE_T[_col_size * _row_size];
	
	for (LENGTH_T c = 0; c < _col_size; ++c)
	{
		for (LENGTH_T r = 0; r < _row_size; ++r)
		{
			_data[_index(r, c)] = board.getValue(r, c);
		}
	}
}



Result::~Result()
{
	free();
}



Result::Result(const Result & other)
{
	copy(other);
}



Result & Result::operator=(const Result & other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}



void Result::copy(const Result & other)
{
	assert(_data == NULL);

	_id = other._id;
	_row_size = other._row_size;
	_col_size = other._col_size;
	
	_data = new VALUE_T[_col_size * _row_size];
	memcpy(_data, other._data, sizeof(VALUE_T) * _col_size * _row_size);
}



void Result::free()
{
	delete [] _data;
	_data = NULL;
}



VALUE_T Result::value(LENGTH_T row, LENGTH_T col) const
{
	assert(0 <= row && row < _row_size);
	assert(0 <= col && col < _col_size);
	
	return _data[_index(row, col)];
}



void Result::print(FILE *output)
{
	//������⣨���У�
	if (_id.length() > 0)
	{
		fprintf(output, "-= %s =-\n", _id.c_str());
	}
	
	//5��*5��ΪһС��
	for (LENGTH_T row = 0; row < _row_size; ++row)
	{
		if (row % 5 == 0)
		{
			fprintf(output, "\n");
		}
			
		for (LENGTH_T col = 0; col < _col_size; ++col)
		{
			if (col % 5 == 0 && col > 0)
			{
				fprintf(output, " ");
			}
			fprintf(output, "%c", value(row, col));
		}
		
		fprintf(output, "\n");
	}
		
	fprintf(output, "\n\n");
}





#endif









#endif




/*
class Board
{
public:
	//���캯��
	Board(const ParamListCollection & col_params, const ParamListCollection & row_params, int log_level, int display_level);
	//��������
	Board(const Board &);
	//����
	virtual ~Board();
	
	//��ֵ�����
	Board & operator=(const Board &);
	
private:
	//����������Point�����Line�б������ڳ�ʼ״̬
	void init();

	//�ͷ���Դ
	void free();
	
	//��������
	void copy(const Board &);
	
		
public:
	//ʹ�ò�������ʼ��
//	void install(const ParamListCollection & col_params, const ParamListCollection & row_params);
	
	//ǿ���趨ĳPoint
	void install(LENGTH_T row, LENGTH_T col, VALUE_T value);


public:
	//����
	//����true�������ߵĶ��Ѿ�������
	//����false�������߼���ͻ��
	bool play();


public:
	//�Ƿ��Ѿ����
	bool isDone() const;

	//�Ƿ��Ѿ�ʧ��
	bool isError() const;
	
	//�����һ����ȷ���㣬���ɶ��ֿ�����
	std::vector<Board *> createCandidates() const;

private:
	//����ĳ�����ɶ��ֿ�����
	std::vector<Board *> createCandidates(LENGTH_T row, LENGTH_T col) const;


	

public:
	//�㱻�ı�Ļص�
	void point_change_callback(LENGTH_T row, LENGTH_T col, VALUE_T value);

	
private:
	Point **						_points;				//����Point

	std::map<long, Line *>			_lines;					//������/��
	
	WeightQueue						_todo;					//����������/��

	const ParamListCollection *		_params_of_cols;		//�����в���
	const ParamListCollection *		_params_of_rows;		//�����в���


private:
	//�����кŻ�õ��ʵ��λ��
	inline
	LENGTH2_T _index(LENGTH_T row, LENGTH_T col) const {
		return row * col_size() + col;
	}
	
	//��һ���к�/�к�
	inline
	long _col_id(LENGTH_T col) const {
		return -col - 1;
	}

	//��һ���к�/�к�
	inline
	long _row_id(LENGTH_T row) const {
		return row + 1;
	}


public:
	
	//������
	inline
	LENGTH_T row_size() const {
		return _params_of_rows->size();
	}

	//������
	inline
	LENGTH_T col_size() const {
		return _params_of_cols->size();
	}


public:
	//����id
	inline
	const char * id() const {
		return _id.c_str();
	}


	//������
	//	output		������ĸ��ļ��� Ĭ��stdout
	//	head		�Ƿ�������̱��� Ĭ�ϲ����
	void print(FILE * output = stdout, bool head = false) const;


	//��־�ȼ�
	inline 
	int log_level() const {
		return _log_level;
	}


	//��ʾ�ȼ�
	inline
	int display_level() const {
		return _display_level;
	}

private:
	std::string			_id;					//����id
	int					_log_level;				//��־�ȼ�
	int					_display_level;			//��ʾ�ȼ�


public:
	//�������ж���ȷ����
	SIZE_T known() const;




};


#endif


*/

