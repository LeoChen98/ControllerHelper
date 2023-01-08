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
		//��������
		recv(sockClient, buff, sizeof(buff), 0);
		
		//��������

	}
}

void SocketClient::Start()
{
	//�����׽���
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		_pPlugin->DisplayUserMessage("Message", "CHPlugin", "Unable to open socket: fail to initial socket.", true, true, true, true, true);
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(_port);//�˿ں�
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//IP��ַ

	//�����׽���
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == sockClient) {
		_pPlugin->DisplayUserMessage("Message", "CHPlugin", "Unable to open socket: " + WSAGetLastError(), true, true, true, true, true);
	}

	//�������������������
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
	//�ر��׽���
	closesocket(sockClient);
	WSACleanup();//�ͷų�ʼ��Ws2_32.dll���������Դ��
	Connected = false;
}

void SocketClient::Send(char* data) {
	send(sockClient, data, sizeof(data), 0);
}