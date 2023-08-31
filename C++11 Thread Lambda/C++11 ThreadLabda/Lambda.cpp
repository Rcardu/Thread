#include<iostream>
#include<thread>
#include<string>

using namespace std;

//lambda 表达式
//[捕获列表](参数)mutable->返回值类型{函数体}

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