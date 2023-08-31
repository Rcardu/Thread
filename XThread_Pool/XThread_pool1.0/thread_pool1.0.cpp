#include"xthread_pool.h"
#include"xvideo_task.h"
#include<iostream>
#include<string>
using namespace std;
//测试部分
/*
class MyTask :public XTask {

public:
	int Run() {
		cout << "==========================================" << endl;
		cout << this_thread::get_id() << " MyTask " << name << endl;
		cout << "==========================================" << endl;
		for (int i = 0; i < 10; i++) {
			if (is_exit())break;
			cout << "." << flush;
			this_thread::sleep_for(500ms);
		}
		return 100;
	}
	string name = "";
};
*/
///视频转码工具
///ffmpeg工具
///用户输入视频源，输出视频尺寸
///在线程池中执行转码任务
///转码任务调用ffmpeg
/// ffmpeg -y -i test.mp4 -s 400x300 400.mp4 >log.txt 2>&1
int main(int argc, char* argv[]) {
	XThreadPool pool;
	pool.Init(16);
	pool.Start();
	this_thread::sleep_for(200ms);
	for (;;) {
		cout << "\n============================================================================================\n";
		auto task = make_shared<XVideoTask>();
		cout << "请输入命令(v e l):";
		string cmd;
		cin >> cmd;
		if (cmd == "e")break;
		else if (cmd == "l") {
			cout << "task run count = " << pool.task_run_count() << endl;
			continue;
		}
		cout << "视频源: ";
		cin >> task->in_path;
		cout << "目标：";
		cin >> task->out_path;
		cout << "输出宽：";
		cin >> task->width;
		cout << "输出高：";
		cin >> task->height;
		pool.AddTask(task);
	}
	pool.Stop();
	/*
	auto vtask1 = make_shared<XVideoTask>();
	vtask1->in_path = "test.mp4";
	vtask1->out_path = "640.mp4";
	vtask1->width = 640;
	vtask1->height = 480;
	pool.AddTask(vtask1);

	vtask1->GetReturn();
	*/
//测试实例
/*
	//MyTask task1;
	//task1.name = "task name 001";
	//pool.AddTask(&task1);
	//MyTask task2;
	//task2.name = "task name 002";
	//pool.AddTask(&task2);

	{
		auto task3 = make_shared<MyTask>();
		task3->name = "tase name 003";
		pool.AddTask(task3);

		auto task4 = make_shared<MyTask>();
		task4->name = "tase name 004";
		pool.AddTask(task4);
		auto re = task3->GetReturn();
		cout << "task4->GetReturn() = " << re<< endl;
	}


	this_thread::sleep_for(100ms);
	cout << "Task run count = " << pool.task_run_count() << endl;

	this_thread::sleep_for(1s);
	pool.Stop();
	cout << "Task run count = " << pool.task_run_count() << endl;
*/
	return 0;
}
