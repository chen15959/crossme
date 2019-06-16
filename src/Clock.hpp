#ifndef Clock_hpp
#define Clock_hpp


//��ʱ��
//���ȵ�
class Clock
{
public:
	//����
	Clock();
	//����
	virtual ~Clock();

private:
	Clock(const Clock &);
	Clock & operator=(const Clock &);

public:
	//��ʼ��ʱ
	bool start();
	//ֹͣ��ʱ
	bool stop();

	//�Ƿ�������
	bool running() const;

	//��ʱ�����������룩
	long elapsed_ms() const;


private:
	//��ȡ��ǰʱ��
	static long long now();

private:
	//��ʼʱ��
	long long _start_time;
	//����ʱ��
	long long _stop_time;
};



#endif
