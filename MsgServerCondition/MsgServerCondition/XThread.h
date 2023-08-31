#pragma once
#include<thread>
class XThread
{
public:
	//�߳�����
	virtual void Start();

	//�����߳��˳���־ ���ȴ�
	virtual void Stop();

	//�ȴ��߳��˳�(����)
	virtual void Wait();

	//�ж��߳��Ƿ����
	bool is_exit();
private:
	//�߳����
	virtual void Main() = 0;
	std::thread th_;
protected:
	bool is_exit_ = false;
};

