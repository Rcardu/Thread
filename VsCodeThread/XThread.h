#pragma once
#include<iostream>
#include<thread>
class XThread{
public:
    //�����߳�
    void Start(){
        //�߳�������ʶ��ʼ��
        is_exit_=false;
        //�����߳�
        th_=std::thread(&XThread::Main,this);
    }
    //ֹͣ�߳�
    void Stop(){
        is_exit_=true;
        //ֹͣǰ�ȴ���ǰδ����߳����
        Wait();

    }
    //�ȴ���ǰδ����߳�
    void Wait(){
        if(!th_.joinable()){
            th_.join();
        }
    }
    //�߳̽�����ʶ
    bool is_exit(){return is_exit_;}

private:
    virtual void Main()=0;
    std::thread th_;
    bool is_exit_=false;
};

