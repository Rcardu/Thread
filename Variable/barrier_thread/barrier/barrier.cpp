#include<thread>
#include<iostream>
#include<barrier>

using namespace std;
void TestBar(int i, barrier<>* bar) {
	this_thread::sleep_for(chrono::seconds(i));
	cout << i << " begin wait " << endl;
	bar->wait(bar->arrive());//�ڴ���-1�����ȴ����ڴ�Ϊ0ʱ����
	cout << i << " end wait " << endl;

}

int main(int argc, char* argv[]) {
	

	int count = 3;
	barrier bar(count);//��ʼ����
	for (int i = 0; i < count; i++) {
		thread th(TestBar, i, &bar);
		th.detach();
	}
	getchar();
	return 0;
}