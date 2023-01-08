#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <thread>
#include <stdint.h>
#include "CCHPlugin.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")//引用库文件

using namespace std;

class CCHPlugin;

class SocketClient
{
private:
	int _port;
	CCHPlugin* _pPlugin;
	SOCKET sockClient;
	static void Receive(SOCKET sockClient);

public:
	SocketClient(CCHPlugin* pPlugin);
	virtual ~SocketClient();

	void Start();
	void Send(char* data);
	void Send(string data);
	void Close();

	bool Connected = false;
};

