#include<thread>
#include<iostream>
#include<string>
#include<mutex>

using namespace std;
static mutex mux;//������

void TestThread() {
	for(;;){
		//��ȡ����Դ�����û��������ȴ�
		//mux.lock();
		if (!mux.try_lock()) {
			cout << "." << flush;
			this_thread::sleep_for(100ms);
			continue;
		}
		cout << "==========================" << endl;
		cout << "test 001" << endl;
		cout << "test 002" << endl;
		cout << "test 003" << endl;
		cout << "==========================" << endl;
		mux.unlock();
		this_thread::sleep_for(1000ms);
	}
}
void ThreadMainMux(int i) {

	for (;;) {
		mux.lock();
		cout << i << "[in]" << endl;
		this_thread::sleep_for(1000ms);
		mux.unlock();
		//ֱ���ͷŻᵼ�µ�ǰ���ͷŵ���Դ���̻߳�ͨ��ѭ����һ��������Դ
		//����һ��˯��ʱ��ʹÿ���߳��ܹ�����ʹ����Դ
		this_thread::sleep_for(1ms);
	}
}
//�ȴ����Ի�ȡ��
//��ʱ��
timed_mutex tmux;
void THreadMainTime(int i) {
	for (;;) {
		if (!tmux.try_lock_for(chrono::milliseconds(500))) {
			//��ȡ����ʱ
			cout << i << "[Try_lock_for timeout]" << endl;
			continue;
		}
		//��ȡ����֮��ʼ����
		cout << i << "[in]" << endl;
		this_thread::sleep_for(2000ms);
		//�ͷ���
		tmux.unlock();
		//�ȴ�1ms�����»�ȡ
		this_thread::sleep_for(1ms);
	}
}
//���������
recursive_mutex rmux;
void Task1() {
	rmux.lock();
	cout << "task1 [in]" << endl;
	rmux.unlock();
}
void Task2() {
	rmux.lock();
	cout << "task2 [in]" << endl;
	rmux.unlock();
}
void ThreadMainRec(int i) {
	for (;;) {
		rmux.lock();
		Task1();
		cout << i << "[in]" << endl;
		this_thread::sleep_for(2000ms);
		Task2();
		rmux.unlock();
		this_thread::sleep_for(1ms);
	}
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < 3; i++) {
		thread th(ThreadMainRec, i + 1);
		th.detach();
	}

	getchar();
	for (int i = 0; i < 3; i++) {
		thread th(THreadMainTime, i + 1);
		th.detach();
	}


	getchar();
	for (int i = 0; i < 3; i++) {
		thread th(ThreadMainMux, i + 1);
		th.detach();
	}



	getchar();
	for (int i = 0; i < 10; i++) {
		thread th(TestThread);
		th.detach();
	}



	getchar();
	return 0;
}