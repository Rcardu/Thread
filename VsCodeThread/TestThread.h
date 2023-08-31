#pragma once
#include"XThread.h"
#include<string>
class TestXThread:public XThread{
public:
    //重载进入线程函数
    void Main()override{
        std::cout<<"TestXThread Main"<<std::endl;
        while(!is_exit()){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout<<"."<<std::flush;
        }std::cout<<"TestXThread Exit"<<std::endl;
    }
    std::string name;
};