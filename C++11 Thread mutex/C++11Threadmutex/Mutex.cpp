#include<thread>
#include<iostream>
#include<string>
#include<mutex>

using namespace std;
static mutex mux;//互斥锁

void TestThread() {
	for(;;){
		//获取锁资源，如果没有阻塞则等待
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
		//直接释放会导致当前刚释放掉资源的线程会通过循环再一次申请资源
		//加上一个睡眠时间使每个线程能够交替使用资源
		this_thread::sleep_for(1ms);
	}
}
//等待尝试获取锁
//超时锁
timed_mutex tmux;
void THreadMainTime(int i) {
	for (;;) {
		if (!tmux.try_lock_for(chrono::milliseconds(500))) {
			//获取锁超时
			cout << i << "[Try_lock_for timeout]" << endl;
			continue;
		}
		//获取到锁之后开始运行
		cout << i << "[in]" << endl;
		this_thread::sleep_for(2000ms);
		//释放锁
		tmux.unlock();
		//等待1ms后重新获取
		this_thread::sleep_for(1ms);
	}
}
//可重入的锁
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