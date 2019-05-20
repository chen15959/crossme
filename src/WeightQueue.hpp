#ifndef WeightQueue_hpp
#define WeightQueue_hpp

#include <map>



//Ȩ�ض���
//���ΰ�Ȩ�س���
class WeightQueue
{
public:
	//����
	WeightQueue();
	//����
	virtual ~WeightQueue();
	
	//��������
	WeightQueue(const WeightQueue &);
	//��ֵ�����
	WeightQueue & operator=(const WeightQueue &);
	
private:
	//����
	void copy(const WeightQueue &);
	//�ͷ�
	void free();
	
public:
	//���Ȩ�������
	long	top();
	//����һ����������
	//��������Ѿ����ڣ���Ȩ�ؼ���ȥ
	void	push(long value, double weight = 1);
	//Ȩ������߳���
	long	pop();


	//���г���
	inline	
	unsigned long	size() const
	{
		return _data.size();
	}
	
	//�����Ƿ�Ϊ��
	inline
	bool			empty() const
	{
		return size() == 0;
	}
	
	//��ն���
	void			clear()
	{
		_data.clear();
	}
	
	
	
	
private:
	std::map<long, double>	_data;		//�����е�����
	long					_top;		//������Ȩ�������
	bool					_ready;		//�Ѿ��������
};


#endif
