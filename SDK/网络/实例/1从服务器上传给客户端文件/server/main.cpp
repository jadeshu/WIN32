//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
using namespace std;
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 6060
#define MAXCONNET 5
#define BUF_SIZE  1024
//const char* pChIP = "127.0.0.1";
int main()
{
	WSAData ws;
	int nRet = WSAStartup(MAKEWORD(2, 2), &ws);
	if (nRet)
	{
		cout << "----WSAStartup初始化失败----" << endl;
	}

	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
	{
		return -1;
	}

	sockaddr_in sockAddr;					// 保存服务端的信息
	int sockAddrLen = sizeof(sockaddr_in);	// 保存服务端信息字节数
	memset(&sockAddr, 0, sizeof(sockAddr)); // 填充数据为0

	sockAddr.sin_family = AF_INET;	// 家族网络族
	//sockAddr.sin_addr.s_addr = inet_addr(pChIP);
	sockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);// INADDR_ANY表示任何IP
	sockAddr.sin_port = htons(PORT);	// 端口

	//套接字与服务器绑定
	if (bind(servSock, (sockaddr*)&sockAddr, sockAddrLen))	//返回0时成功 否则失败或者错误
	{
		cout << "----绑定套接字失败----" << endl;
		closesocket(servSock);
		WSACleanup();
		return -1;
	}
	listen(servSock, MAXCONNET);
	cout << "服务器已启动:\n监听中...\n" << endl;

	struct sockaddr_in clientAddr;			//保存客户端的信息
	int nClientArrLen = sizeof(clientAddr);	//保存客户端信息字节数

	SOCKET sClient = INVALID_SOCKET;
		//接受到来的客户端
	sClient = accept(servSock, (struct sockaddr*)&clientAddr, &nClientArrLen);

	cout << "----客户端" << sClient << "进入----"<< endl;
		
		// TODO
	FILE* fp = fopen("12.jpg", "rb");
	if (fp == nullptr)
	{
		return 0;
	}
	char buffer[BUF_SIZE] = { 0 };
	int nCount = 0;
	// 读取文件
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0)
	{
		// 发送数据
		send(sClient, buffer, nCount, 0);
	}

	// 优雅关闭，防止数据未发送完毕
	shutdown(sClient, SD_SEND);
	// 阻塞住，当客户端关闭套接字closeSocket后，此函数返回
	recv(sClient, buffer, BUF_SIZE, 0);
		
	fclose(fp);
	closesocket(sClient);
	closesocket(servSock);
	WSACleanup();
	//system("pause");
	return 0;
}