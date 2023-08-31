#pragma once
#include<iostream>
#include<thread>
class XThread{
public:
    //启动线程
    void Start(){
        //线程启动标识初始化
        is_exit_=false;
        //进入线程
        th_=std::thread(&XThread::Main,this);
    }
    //停止线程
    void Stop(){
        is_exit_=true;
        //停止前等待当前未完成线程完成
        Wait();

    }
    //等待当前未完成线程
    void Wait(){
        if(!th_.joinable()){
            th_.join();
        }
    }
    //线程结束标识
    bool is_exit(){return is_exit_;}

private:
    virtual void Main()=0;
    std::thread th_;
    bool is_exit_=false;
};

