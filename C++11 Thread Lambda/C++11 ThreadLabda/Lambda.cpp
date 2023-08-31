#include<iostream>
#include<thread>
#include<string>

using namespace std;

//lambda ���ʽ
//[�����б�](����)mutable->����ֵ����{������}

class TestLambda {
public:
	void Start() {
		thread th([this]() {cout << "name = " << name << endl; });
		th.join();
	}

	string name = "test lambda";
};
int main(int argc, char* argv[]) {

	thread th(
		[](int i) {cout << "test lambda " << i << endl; },
		123
	);
	th.join();
	TestLambda test;
	test.Start();

	return 0;
}