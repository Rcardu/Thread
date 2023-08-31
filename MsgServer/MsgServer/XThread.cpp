#include "XThread.h"
using namespace std;
//�߳�����
void XThread::Start() {
	is_exit_ = false;
	th_ = thread(&XThread::Main, this);
}

//�����߳��˳���־ ���ȴ�
void XThread::Stop() {
	is_exit_ = true;
	Wait();
}

//�ȴ��߳��˳�(����)
void XThread::Wait() {
	if (th_.joinable())th_.join();
}

//�ж��߳��Ƿ����
bool XThread::is_exit() {
	return is_exit_;
}