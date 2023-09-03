#include<thread>
#include<iostream>
#include<barrier>

using namespace std;
void TestBar(int i, barrier<>* bar) {
	this_thread::sleep_for(chrono::seconds(i));
	cout << i << " begin wait " << endl;
	bar->wait(bar->arrive());//期待数-1阻塞等待，期待为0时返回
	cout << i << " end wait " << endl;

}

int main(int argc, char* argv[]) {
	

	int count = 3;
	barrier bar(count);//初始数量
	for (int i = 0; i < count; i++) {
		thread th(TestBar, i, &bar);
		th.detach();
	}
	getchar();
	return 0;
}