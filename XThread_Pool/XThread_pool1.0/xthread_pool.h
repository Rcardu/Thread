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
		//�����ȴ�set_value
		return p_.get_future().get();
	}
	void SetValue(int v) {
		p_.set_value(v);
	}
private:
	//�������շ���ֵ
	std::promise<int> p_;
	
};

class XThreadPool
{
public:
	/// <summary>
	/// ��ʼ���̳߳�
	/// @para num�߳�����
	/// </summary>
	/// <param name="num"></param>
	void Init(int num);
	/// <summary>
	/// ���������̣߳������ȵ���Init
	/// </summary>
	void Start();

	//�̳߳ص��˳�
	void Stop();

	//void AddTask(XTask*task);
	void AddTask(std::shared_ptr<XTask> task);

	//XTask* GetTask();
	std::shared_ptr<XTask>GetTask();

	//�̳߳��Ƿ��˳�
	bool is_exit() { return is_exit_; }

	int task_run_count() { return task_run_count_; }
	~XThreadPool() { Stop(); }
private:
	//�̳߳��̵߳���ں���
	void Run();
	int thread_num_ = 0;//�߳�����
	std::mutex mux_;
	//std::vector<std::thread*>threads_;
	//�߳��б�����ָ��汾
	std::vector<std::shared_ptr<std::thread>>threads_;
	//std::list<XTask*>tasks_;
	std::list<std::shared_ptr<XTask>>tasks_;
	std::condition_variable cv_;
	bool is_exit_ = false;//�̳߳��˳�

	//�������е������������̰߳�ȫ
	std::atomic<int>task_run_count_ = { 0 };
};

