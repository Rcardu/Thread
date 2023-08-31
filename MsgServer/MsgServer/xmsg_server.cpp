#include "xmsg_server.h"
#include<mutex>
#include<iostream>
using namespace std;
using namespace this_thread;
//����ǰ�̷߳�����Ϣ
void XMsgServer::SendMsg(std::string msg) {
	unique_lock<mutex>lock(mux_);
	msgs_.push_back(msg);
}
//�����̵߳���ں���
void XMsgServer::Main() {
	while (!is_exit()) {

		sleep_for(10ms);
		unique_lock<mutex>lock(mux_);
		if (msgs_.empty())continue;
		while (!msgs_.empty()) {
			//��Ϣ����ҵ���߼�
			cout << "recv:" << msgs_.front() << endl;
			msgs_.pop_front();
		}
	}
}