#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

//字符串缓冲区大小
#define MAX_TEXT_LEN 100


//1. 初始化套接字库
//2. 创建套接字
//3. 发送接收数据
int main()
{
	WSADATA wsData;
	int nRet = WSAStartup(0x0202, &wsData);
	if (nRet)
	{
		printf("----WSAStartup初始化失败\n----");
	}

	//创建套接字(创建就知道了是什么协议的套接字)
	SOCKET sClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sClient == INVALID_SOCKET)
	{
		return -1;
	}
	printf("----UDP创建套接字成功!----\n");

	struct sockaddr_in serverAddr;			//保存客户端的信息
	int nSerAddrLen = sizeof(sockaddr_in);	//保存客户端信息字节数
	memset(&serverAddr, 0, nSerAddrLen);		//填充数据为0

	serverAddr.sin_family = AF_INET;			//家族网络族
	serverAddr.sin_port = htons(6000);		//端口
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1")/*inet_addr("127.0.0.1")*/;	//IP

	char recBuffer[MAX_TEXT_LEN] = {0};
	char msgSend[] = "已接受到您发的信息";
	while (true)
	{
		printf("----请在下面输入您想跟服务器发送的内容 大小%d字节 逐行发送----\n",MAX_TEXT_LEN);
		//获取输入字符
		gets_s(recBuffer,MAX_TEXT_LEN);
		sendto(sClient, recBuffer, strlen(recBuffer), 0,(sockaddr*)&serverAddr, nSerAddrLen);
		
		int nRetLen = recvfrom(sClient, recBuffer, MAX_TEXT_LEN, 0, 0/*(struct sockaddr*)&serverAddr*/, 0/*&nSerAddrLen*/);
		recBuffer[nRetLen] = 0;
		printf("接受信息：%s 从IP:[%s] 端口：[%d]\n", recBuffer, inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
	}
	closesocket(sClient);
	WSACleanup();
	return 0;
}