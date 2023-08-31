#include "xmsg_server.h"
#include<mutex>
#include<iostream>
using namespace std;
using namespace this_thread;
//����ǰ�̷߳�����Ϣ
void XMsgServer::SendMsg(std::string msg) {
	unique_lock<mutex>lock(mux_);
	msgs_.push_back(msg);
	lock.unlock();
	cv_.notify_one();
}
//�����̵߳���ں���
void XMsgServer::Main() {
	while (!is_exit()) {

		//sleep_for(10ms);
		unique_lock<mutex>lock(mux_);
		cv_.wait(lock, [this] {
			if (is_exit())return true;
			return !msgs_.empty(); 
			});
		if (msgs_.empty())continue;
		while (!msgs_.empty()) {
			//��Ϣ����ҵ���߼�
			cout << "recv:" << msgs_.front() << endl;
			msgs_.pop_front();
		}
	}
}
void XMsgServer::Stop() {
	is_exit_ = true;
	cv_.notify_all();
	Wait();
}
