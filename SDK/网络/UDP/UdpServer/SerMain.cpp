#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

//字符串缓冲区大小
#define MAX_TEXT_LEN 100

//1. 初始化套接字库
//2. 创建套接字
//3. 绑定套接字
//4. 发送接收数据
int main()
{
	WSADATA wsData;
	int nRet = WSAStartup(0x0202, &wsData);
	if (nRet)
	{
		printf("----WSAStartup初始化失败\n----");
	}

	//创建套接字(创建就知道了是什么协议的套接字)
	SOCKET sServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sServer == INVALID_SOCKET)
	{
		return -1;
	}
	printf("----UDP创建套接字成功!----\n");
	struct sockaddr_in serverAddr;			//保存客户端的信息
	int nSerAddrLen = sizeof(sockaddr_in);	//保存客户端信息字节数
	memset(&serverAddr, 0, nSerAddrLen);		//填充数据为0

	serverAddr.sin_family = AF_INET;			//家族网络族
	serverAddr.sin_port = htons(6000);		//端口
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY)/*inet_addr("127.0.0.1")*/;	//IP

	//套接字与服务器绑定(即系统知道端口 IP)
	if (bind(sServer, (sockaddr*)&serverAddr, nSerAddrLen))	//返回0时成功 否则失败或者错误
	{
		printf("----UDP绑定套接字失败----\n");
		closesocket(sServer);
		WSACleanup();
		return -1;
	}
	printf("----UDP绑定套接字成功----\n");

	struct sockaddr_in ClientAddr;	//保存客户端的信息
	int nClientAddrLen = sizeof(sockaddr_in);
	memset(&ClientAddr, 0, nClientAddrLen);		//保存客户端信息字节数

	char recBuffer[MAX_TEXT_LEN] = {0};
	char msgSend[] = "good job";
	while (true)
	{
		int nRetLen = recvfrom(sServer, recBuffer, MAX_TEXT_LEN, 0, (struct sockaddr*)&ClientAddr, &nClientAddrLen);

		recBuffer[nRetLen] = 0;
		printf("接受信息：%s 从IP:[%s] 端口：[%d]\n", recBuffer, inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

		//接收数据成功后发送给客户端
		sendto(sServer, msgSend, strlen(msgSend), 0, (sockaddr*)&ClientAddr, nClientAddrLen);
	}
	closesocket(sServer);
	WSACleanup();
	return 0;
}