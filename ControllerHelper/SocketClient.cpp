#include "pch.h"
#include "SocketClient.h"
#include "EuroScopePlugIn.h"


SocketClient::SocketClient(CCHPlugin* pPlugin) {
	_pPlugin = pPlugin;
	ifstream inFile;
	inFile.open(string(getenv("LOCALAPPDATA")) + "ControllerHelper\\socketport.txt", ios::in);
	if (!inFile.is_open()) // unable to open file
	{
		pPlugin->DisplayUserMessage("Message", "CHPlugin", ("Unable to open file: " + string(getenv("LOCALAPPDATA")) + "ControllerHelper\\socketport.txt").c_str(), true, true, true, true, true);
	}
	string port;
	getline(inFile, port);
	inFile.close();

	if (regex_match(port, std::regex("^[0-9]+$"))) {
		_port = strtol(port.c_str(), nullptr, 10);
	}
	else {
		pPlugin->DisplayUserMessage("Message", "CHPlugin", "Unable to open socket: bad port format.", true, true, true, true, true);
	}
}

SocketClient::~SocketClient()
{
	if (Connected) {
		Close();

	}
}

void SocketClient::Receive(SOCKET sockClient)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	while (true) {
		//接收数据
		recv(sockClient, buff, sizeof(buff), 0);
		
		//处理数据

	}
}

void SocketClient::Start()
{
	//加载套接字
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		_pPlugin->DisplayUserMessage("Message", "CHPlugin", "Unable to open socket: fail to initial socket.", true, true, true, true, true);
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(_port);//端口号
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//IP地址

	//创建套接字
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == sockClient) {
		_pPlugin->DisplayUserMessage("Message", "CHPlugin", "Unable to open socket: " + WSAGetLastError(), true, true, true, true, true);
	}

	//向服务器发出连接请求
	if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET) {
		_pPlugin->DisplayUserMessage("Message", "CHPlugin", "Socket connection fail: " + WSAGetLastError(), true, true, true, true, true);
	}
	else
	{
		Connected = true;
		thread t(Receive,ref(sockClient));
		t.join();
	}
}

void SocketClient::Close()
{
	//关闭套接字
	closesocket(sockClient);
	WSACleanup();//释放初始化Ws2_32.dll所分配的资源。
	Connected = false;
}

void SocketClient::Send(char* data) {
	send(sockClient, data, sizeof(data), 0);
}