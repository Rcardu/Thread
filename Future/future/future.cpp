#include<thread>
#include<iostream>
#include<future>
#include<iostream>
#include<string>

using namespace std;

void TestFuture(promise<string>p) {

	cout << "begin TestFuture" << endl;
	this_thread::sleep_for(3s);
	cout << "begin set value" << endl;
	p.set_value("TestFuture value");
	this_thread::sleep_for(3s);
	cout << "end TestFuture" << endl;
}


int main(int argc, char* argv[]) {
	//�첽�������
	promise<string>p;
	//�߳��첽ֵ��ȡ
	auto future = p.get_future();
	auto th = thread(TestFuture, move(p));
	
	cout << "begin future.get()" << endl;
	cout << "future get() = " << future.get() << endl;
	cout << "end future.get()" << endl;

	th.join();



	getchar();
	return 0;
}