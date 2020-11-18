#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
WSAEVENT g_Event[20] = {0};
SOCKET g_Socket[20] = {0};
DWORD dwTotal = 0;

DWORD __stdcall ClientProcess( LPVOID lpThreadParameter)
{
	while (TRUE)
	{
		DWORD dwRet = WSAWaitForMultipleEvents(dwTotal+1,g_Event,FALSE,100,0);
		if (dwRet == WSA_WAIT_TIMEOUT)
		{
			//超时
			//printf("客户端:超时\n");
			continue;
		}
		
	}
	return 0;
}

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
	//g_Socket[dwTotal] = sServer;
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

	//创建与客户端连接处理的线程
	CreateThread(NULL, 0, ClientProcess, NULL, 0, NULL);

	struct sockaddr_in clientAddr;	//保存客户端的信息
	int nClientArrLen = sizeof(clientAddr);	//保存客户端信息字节数
	while (TRUE)
	{
		//接受到来的客户端
		g_Socket[dwTotal] = accept(sServer, (struct sockaddr*)&clientAddr, &nClientArrLen);	

		WSAOVERLAPPED wsaoverlapped = {0};
		g_Event[dwTotal] = WSACreateEvent();
		wsaoverlapped.hEvent = g_Event[dwTotal];
		dwTotal++;
		
		//	GetOverlappedResult()
	}

	closesocket(sServer);
	WSACleanup();
	return 0;
}