#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

WSAEVENT g_Event[20] = {0};
SOCKET g_Socket[20] = {0};
DWORD dwTotal = 0;
DWORD __stdcall ClientProcess( LPVOID lpThreadParameter);

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
	g_Socket[dwTotal] = sServer;
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

	g_Event[dwTotal] = WSACreateEvent();

	nRet  = WSAEventSelect(g_Socket[dwTotal], g_Event[dwTotal], FD_ACCEPT|FD_CLOSE);
	if ((nRet != 0) || (nRet == SOCKET_ERROR))
	{
		printf("----事件选择失败----\n");
		closesocket(sServer);
		WSACleanup();
		return -1;
	}

	//监听绑定的套接字
	printf("----监听套接字----\n");
	listen(sServer,SOMAXCONN);

	//创建与客户端连接处理的线程
	CreateThread(NULL, 0, ClientProcess, NULL, 0, NULL);

	system("pause");	//主线程暂停
	closesocket(sServer);
	WSACleanup();
	return 0;
}

DWORD __stdcall ClientProcess( LPVOID lpThreadParameter)
{
	WSANETWORKEVENTS entworkEv;
	while (TRUE)
	{
		DWORD dwRet = WSAWaitForMultipleEvents(dwTotal+1,g_Event,FALSE,100,0);
		if (dwRet == WSA_WAIT_TIMEOUT)
		{
			//超时
			//printf("客户端:超时\n");
			continue;
		}

		WSAEnumNetworkEvents(g_Socket[dwTotal],g_Event[dwTotal],&entworkEv);
		if (entworkEv.lNetworkEvents&FD_ACCEPT)	// 处理新客户到来
		{
			sockaddr_in ClientAddress;
			int nClientLength = sizeof(ClientAddress);

			SOCKET ClientSocket = accept(g_Socket[dwTotal], (SOCKADDR*)&ClientAddress, &nClientLength);

			if (INVALID_SOCKET == ClientSocket)
			{
				//printf("接受客户失败!%ld\n",WSAGetLastError());
				closesocket(ClientSocket);
				continue;
			}
			dwTotal++;
			g_Socket[dwTotal] = ClientSocket;


			g_Event[dwTotal] = WSACreateEvent();

			int nRet  =  WSAEventSelect(g_Socket[dwTotal], g_Event[dwTotal], FD_READ|FD_WRITE|FD_CLOSE);
			if ((nRet != 0) || (nRet == SOCKET_ERROR))
			{
				printf("----事件选择失败----\n");
				closesocket(g_Socket[dwTotal]);
				WSACleanup();
				return -1;
			}
		}
		if (entworkEv.lNetworkEvents&FD_READ)
		{
		// ...处理读的消息
			break;
		}
	}
	return 0;
}