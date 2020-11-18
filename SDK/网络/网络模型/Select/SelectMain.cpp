#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")


unsigned int nPerNum = 0;	//在线人数
struct fd_set fdClientSkt;	//文件描述集合 ---来自客户端信息
#define MAX_TEXT_LEN 100	//定义字符最大字节数


DWORD __stdcall ClientProcess( LPVOID lpThreadParameter)
{
	//转换参数值
	//fd_set *pFdClient = (fd_set*)(lpThreadParameter);

	char RecBuffer[MAX_TEXT_LEN] = {0};
	char tongzhi[] = "服务器已收到您的信息！";
	int nRet = 0;  //返回值	
	struct timeval tv = {0};
	tv.tv_sec = 2;

	fd_set fRead;

	while (true)
	{
		FD_ZERO(&fRead);
		//for (int i = 0; i < nPerNum; i++)     
		//{
		//	FD_SET(g_CliSocketArr, &fRead);     
		//} 
		fRead = fdClientSkt;
		nRet = select(0, &fRead, NULL, NULL, &tv);
		if (nRet != SOCKET_ERROR)
		{
			for (int i=0; i < (int)(fRead.fd_count); i++)
			{
				if (FD_ISSET(fRead.fd_array[i],&fdClientSkt))
				{
					nRet = recv(fRead.fd_array[i], RecBuffer, MAX_TEXT_LEN, 0);
					if (nRet == SOCKET_ERROR)
					{
						printf("客户端:%d出错，强制关闭\n", fRead.fd_array[i]);
						
						FD_CLR(fRead.fd_array[i],&fdClientSkt);
						closesocket(fRead.fd_array[i]);
						nPerNum--;
						printf("----共有:%d个客户----\n",nPerNum);
					}
					else if (nRet == 0)
					{
						printf("客户端:%d主动退出\n", fRead.fd_array[i]);
						
						FD_CLR(fRead.fd_array[i],&fdClientSkt);
						closesocket(fRead.fd_array[i]);
						nPerNum--;
					}
					else
					{
						RecBuffer[nRet] = '\0';
						printf("客户端:%d发来 %s\n", fRead.fd_array[i], RecBuffer);

						//发送通知给客户端
						/*nRet = */send(fRead.fd_array[i], tongzhi, strlen(tongzhi)*sizeof(char), 0);
						//if (nRet == SOCKET_ERROR)
						//{
						//	printf("客户端:%d出错，强制关闭\n", fdClientSkt.fd_array[i]);
						//	closesocket(fdClientSkt.fd_array[i]);
						//	return -1;
						//}
					}				
				}
			}
		}
	}
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
	CreateThread(NULL, 0, ClientProcess, NULL/*(void*)&fdClientSkt*/, 0, NULL);

	struct sockaddr_in clientAddr;	//保存客户端的信息
	int nClientArrLen = sizeof(clientAddr);	//保存客户端信息字节数
	while (true)
	{
		//接受到来的客户端
		SOCKET sClient = accept(sServer, (struct sockaddr*)&clientAddr, &nClientArrLen);	

		FD_SET(sClient,&fdClientSkt);
		++nPerNum;
		printf("----新客户:%d进入,共有:%d个客户----\n",sClient,nPerNum);

	}
	FD_ZERO(&fdClientSkt);
	closesocket(sServer);
	WSACleanup();
	return 0;
}