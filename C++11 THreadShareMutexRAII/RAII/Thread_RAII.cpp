#include<thread>
#include<shared_mutex>
#include<iostream>
#include<mutex>
#include<string>

class XMutex {
public:
	XMutex(std::mutex& mux):mux_(mux) {
		
		std::cout << "Lock" << std::endl;
		mux.lock();
	}
	~XMutex() {
		std::cout << "UnLock" << std::endl;
		mux_.unlock();
	}
private:
	std::mutex& mux_;
};
static std::mutex mux;

void TestMutex(int staic) {
	XMutex lock(mux);
	if (staic == 1) {
		std::cout << "=1" << std::endl;
		return;
	}
	else {
		std::cout << "!=1" << std::endl;
		return;
	}
}

static std::mutex gmutex;
void TestLockGuard(int i) {

	gmutex.lock();
	{
		//��ͷ�Ѿ�ӵ����
		std::lock_guard<std::mutex>lock(gmutex,std::adopt_lock);
		//�����ͷ���
	}
	{
		std::lock_guard<std::mutex>lock(gmutex);
		std::cout << "begin thread" << i << std::endl;
	}
	for (;;) {

		{
			std::lock_guard<std::mutex>lock(gmutex);
			std::cout << "In" << i << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
static std::mutex mux1;
static std::mutex mux2;
void TestScope1() {
	//ģ��������ͣ100ms����һ���߳���mux2
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout <<std::this_thread::get_id()<< "\tbegin mux1 lock" << std::endl;
	//mux1.lock();
	std::cout << std::this_thread::get_id() << "\tbegin mux2 lock" << std::endl;
	//mux2.lock();//����
	//������ͬʱ��ס
	//lock(mux1, mux2);
	//C++17
	std::scoped_lock lock(mux1, mux2);
	std::cout << std::this_thread::get_id() << "\tget mux1 lock true!" << std::endl;
	std::cout << std::this_thread::get_id() << "\tget mux2 lock true!" << std::endl;
	std::cout << "TestScope1" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//mux1.unlock();
	//mux2.unlock();
}
void TestScope2() {
	std::cout << std::this_thread::get_id() << "\tbegin mux2 lock" << std::endl;
	//mux2.lock();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout <<std::this_thread::get_id()<< "\tbegin mux1 lock" << std::endl;
	//mux1.lock();
	std::scoped_lock lock(mux1, mux2);
	std::cout << std::this_thread::get_id() << "\tget mux2 lock true!" << std::endl;
	std::cout << std::this_thread::get_id() << "\tget mux1 lock true!" << std::endl;
	std::cout << "TestScope2" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	//mux1.unlock();
	//mux2.unlock();
}
int main(int argc, char* argv[]) {
	{
		//��ʾ�������
		{
			std::thread th(TestScope1);
			th.detach();
		}
		{
			std::thread th(TestScope2);
			th.detach();
		}
	}

	getchar();
	{
		//������
		static std::shared_timed_mutex tmux;
		//��ȡ�� ������
		{
			//���ù�����
			std::shared_lock<std::shared_timed_mutex>lock(tmux);
			std::cout << "read data" << std::endl;
			//�˳�ջ�� �ͷŹ�����
		}
		//д���� ������
		{
			std::unique_lock<std::shared_timed_mutex>lock(tmux);
			std::cout << "write data" << std::endl;
		}

	}

	{
		static std::mutex mux;
		{
			std::unique_lock<std::mutex>lock(mux);
			lock.unlock();
			//��ʱ�ͷ���
			lock.lock();
		}
		{
			//�Ѿ�ӵ���������������˳�����
			mux.lock();
			std::unique_lock<std::mutex>lock(mux, std::adopt_lock);
		}
		{
			//�Ӻ��������ӵ�У��˳�������
			std::unique_lock<std::mutex>lock(mux, std::defer_lock);
			//�������˳�ջ������
			lock.lock();

		}
		{
			mux.lock();
			//���Լ�������������ʧ�ܲ�ӵ����
			std::unique_lock<std::mutex>lock(mux, std::try_to_lock);
			if (lock.owns_lock()) {
				std::cout<<"owns_lock" << std::endl;
			}
			else {
				std::cout<<"not owns_lock" << std::endl;
			}
		}
	}
	getchar();
	for (int i = 0; i < 3; i++) {
		std::thread th(TestLockGuard, i + 1);
		th.detach();
	}
	

	getchar();
	TestMutex(1);
	TestMutex(2);


	getchar();
	return 0;
}