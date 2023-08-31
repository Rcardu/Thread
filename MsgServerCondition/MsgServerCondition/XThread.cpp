#include "XThread.h"
using namespace std;
//线程启动
void XThread::Start() {
	is_exit_ = false;
	th_ = thread(&XThread::Main, this);
}

//设置线程退出标志 并等待
void XThread::Stop() {
	is_exit_ = true;
	Wait();
}

//等待线程退出(阻塞)
void XThread::Wait() {
	if (th_.joinable())th_.join();
}

//判断线程是否结束
bool XThread::is_exit() {
	return is_exit_;
}
