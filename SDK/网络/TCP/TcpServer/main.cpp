#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

#define MAX_TEXT_LEN 100
DWORD __stdcall ClientProcess( LPVOID lpThreadParameter)
{
	SOCKET sClient = (SOCKET)lpThreadParameter;
	char RecBuffer[MAX_TEXT_LEN] = {0};
	char tongzhi[] = "已收到您发来的信息了！";

	while (true)
	{
		int nRetBufferLen = recv(sClient, RecBuffer, MAX_TEXT_LEN, 0);
		if (nRetBufferLen == SOCKET_ERROR)
		{
			printf("客户端%d发来:%s 出错，强制关闭\n", sClient);
			closesocket(sClient);
			return -1;

		}
		if (nRetBufferLen == 0)
		{
			printf("客户端%d发来:%s 已经退出\n", sClient);
			break;
		}

		RecBuffer[nRetBufferLen] = 0;
		printf("客户端%d发来:%s\n", sClient, RecBuffer);

		nRetBufferLen = send(sClient, tongzhi, strlen(tongzhi)*sizeof(char), 0);
		if (nRetBufferLen == SOCKET_ERROR)
		{
			printf("客户端%d发来:%s 出错，强制关闭\n", sClient);
			closesocket(sClient);
			return -1;
		}		
	}
	closesocket(sClient);
	return 0;
}

//1. 初始化套接字库
//2. 创建套接字
//3. 绑定套接字
//4. 监听套接字
//4. 接收客户端到来
int main()
{
	WSADATA wsData;
	int nRet = WSAStartup(0x0202, &wsData);
	if (nRet)
	{
		printf("----WSAStartup初始化失败\n----");
	}

	//创建套接字(创建就知道了是什么协议的套接字)
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sServer == INVALID_SOCKET)
	{
		return -1;
	}
	printf("----创建套接字成功!----\n");
	struct sockaddr_in serverAddr;			//保存客户端的信息
	int nSerAddrLen = sizeof(sockaddr_in);	//保存客户端信息字节数
	memset(&serverAddr, 0, nSerAddrLen);		//填充数据为0

	serverAddr.sin_family = AF_INET;			//家族网络族
	serverAddr.sin_port = htons(6000);		//端口
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY)/*inet_addr("127.0.0.1")*/;	//IP

	//套接字与服务器绑定(即系统知道端口 IP)
	if (bind(sServer, (sockaddr*)&serverAddr, nSerAddrLen))	//返回0时成功 否则失败或者错误
	{
		printf("----绑定套接字失败----\n");
		closesocket(sServer);
		WSACleanup();
		return -1;
	}
	printf("----绑定套接字成功----\n");
	//监听绑定的套接字
	printf("----监听套接字----\n");
	listen(sServer,SOMAXCONN);
	
	struct sockaddr_in clientAddr;	//保存客户端的信息
	int nClientArrLen = sizeof(clientAddr);	//保存客户端信息字节数
	while (true)
	{
		SOCKET sClient;
		//接受到来的客户端
		sClient = accept(sServer, (struct sockaddr*)&clientAddr, &nClientArrLen);	

		printf("----有个客户端%d进入----\n",sClient);
		CreateThread(NULL, 0, ClientProcess, (void*)sClient, 0, NULL);
		Sleep(5);
	}
	closesocket(sServer);
	WSACleanup();
	return 0;
}