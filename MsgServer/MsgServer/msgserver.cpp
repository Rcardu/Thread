#include"xmsg_server.h"
#include<sstream>
using namespace std;
int main(int argc, char* argv[]) {
	XMsgServer server;
	server.Start();
	for (int i = 0; i < 10; i++) {
		stringstream ss;
		ss << "msg:" << i + 1;
		server.SendMsg(ss.str());
		this_thread::sleep_for(500ms);
	}
	server.Stop();
	//1

	getchar();
	return 0;
}