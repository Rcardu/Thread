#pragma once
#include<thread>
#include<mutex>
#include<vector>
#include<list>
#include<functional>
#include<atomic>
#include<iostream>
#include<future>

class XTask {

public:
	virtual int Run() = 0;
	std::function<bool()>is_exit = nullptr;
	auto GetReturn() {
		//阻塞等待set_value
		return p_.get_future().get();
	}
	void SetValue(int v) {
		p_.set_value(v);
	}
private:
	//用来接收返回值
	std::promise<int> p_;
	
};

class XThreadPool
{
public:
	/// <summary>
	/// 初始化线程池
	/// @para num线程数量
	/// </summary>
	/// <param name="num"></param>
	void Init(int num);
	/// <summary>
	/// 启动所有线程，必须先调用Init
	/// </summary>
	void Start();

	//线程池的退出
	void Stop();

	//void AddTask(XTask*task);
	void AddTask(std::shared_ptr<XTask> task);

	//XTask* GetTask();
	std::shared_ptr<XTask>GetTask();

	//线程池是否退出
	bool is_exit() { return is_exit_; }

	int task_run_count() { return task_run_count_; }
	~XThreadPool() { Stop(); }
private:
	//线程池线程的入口函数
	void Run();
	int thread_num_ = 0;//线程数量
	std::mutex mux_;
	//std::vector<std::thread*>threads_;
	//线程列表，智能指针版本
	std::vector<std::shared_ptr<std::thread>>threads_;
	//std::list<XTask*>tasks_;
	std::list<std::shared_ptr<XTask>>tasks_;
	std::condition_variable cv_;
	bool is_exit_ = false;//线程池退出

	//正在运行的任务数量，线程安全
	std::atomic<int>task_run_count_ = { 0 };
};

