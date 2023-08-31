#include"xmsg_server.h"
#include<sstream>
#include<iostream>
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
	cout << "Server stoped!" << endl;

	getchar();
	return 0;
}