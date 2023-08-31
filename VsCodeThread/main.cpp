#include"TestThread.h"

int main(int argc,char*argv[]){
    TestXThread Test;
    Test.name="This Thread is created!";
    Test.Start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    Test.Stop();
    getchar();


    return 0;
}