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
		//可能当前线程需要先读取资料
		//根据资料来判断是否要修改
		stmux.lock_shared();
		//读取数据
		//读取完成后释放掉共享锁
		stmux.unlock_shared();
		//需要对内容进行修改时，使用互斥锁进行修改
		//但当其他线程还在读取时则等待
		stmux.lock();//互斥锁 写入
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