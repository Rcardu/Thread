#include<mutex>
#include<thread>
#include<iostream>
#include<string>
#include<shared_mutex>

//C++14
std::shared_timed_mutex stmux;


void ThreadRead(int i) {
	for (;;) {
		stmux.lock_shared();
		std::cout << i << "Read" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		stmux.unlock_shared();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		
	}
}
void ThreadWrite(int i) {
	for (;;) {
		//���ܵ�ǰ�߳���Ҫ�ȶ�ȡ����
		//�����������ж��Ƿ�Ҫ�޸�
		stmux.lock_shared();
		//��ȡ����
		//��ȡ��ɺ��ͷŵ�������
		stmux.unlock_shared();
		//��Ҫ�����ݽ����޸�ʱ��ʹ�û����������޸�
		//���������̻߳��ڶ�ȡʱ��ȴ�
		stmux.lock();//������ д��
		std::cout << i << "Write" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		stmux.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
int main(int argc, char* argv[]) {
	
	for (int i = 0; i < 3; i++) {
		std::thread th(ThreadWrite, i + 1);
		th.detach();
	}
	for (int i = 0; i < 3; i++) {
		std::thread th(ThreadRead, i + 1);
		th.detach();
	}


	getchar();
	return 0;
}