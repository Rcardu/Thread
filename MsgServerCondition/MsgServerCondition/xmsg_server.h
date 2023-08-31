#pragma once
#include "XThread.h"
#include<string>
#include<list>
#include<mutex>
class XMsgServer :public XThread
{
public:
	//����ǰ�̷߳�����Ϣ
	void SendMsg(std::string msg);

	void Stop()override;

private:
	//�����̵߳���ں���
	void Main()override;

	//��Ϣ���л���
	std::list<std::string>msgs_;

	//���������Ϣ����
	std::mutex mux_;
	
	//�ź���
	std::condition_variable cv_;
};

