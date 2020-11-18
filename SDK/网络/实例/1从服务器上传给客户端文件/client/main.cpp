//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
//#include <string>
#include <iostream>
using namespace std;
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//字符串缓冲区大小
#define PORT 6060
#define MAXCONNET 5
const char* pChIP = "127.0.0.1";
#define BUF_SIZE  1024
int main()
{
	WSAData ws;
	int nRet = WSAStartup(MAKEWORD(2, 2), &ws);
	if (nRet)
	{
		cout << "----WSAStartup初始化失败----" << endl;
	}

	SOCKET cSock = socket(AF_INET, SOCK_STREAM, 0);
	if (cSock == INVALID_SOCKET)
	{
		return -1;
	}

	sockaddr_in sockAddr;					// 保存服务端的信息
	int sockAddrLen = sizeof(sockaddr_in);	// 保存服务端信息字节数
	memset(&sockAddr, 0, sizeof(sockAddr)); // 填充数据为0

	sockAddr.sin_family = AF_INET;	// 家族网络族
	sockAddr.sin_addr.s_addr = inet_addr(pChIP);
	sockAddr.sin_port = htons(PORT);	// 端口
										//套接字与服务器绑定(即系统知道端口 IP)
	if (connect(cSock, (sockaddr*)&sockAddr, sockAddrLen))	//返回0时成功 否则失败或者错误
	{
		DWORD i = GetLastError();
		cout << "----连接服务器失败,错误码:" << i << "----" << endl;
		closesocket(cSock);
		WSACleanup();
		return -1;
	}
	
	cout << "----连接服务器成功----" << endl;

	// 新建二进制文件并写入
	FILE *fp = fopen("34.jpg", "wb");
	//循环接收数据，直到文件传输完毕
	char buffer[BUF_SIZE] = { 0 };  //文件缓冲区
	int nCount;
	// 从网络获取数据
	while ((nCount = recv(cSock, buffer, BUF_SIZE, 0)) > 0) {
		// 往文件写入数据
		fwrite(buffer,  1, nCount, fp);
	}
	puts("File transfer success!");
	//文件接收完毕后直接关闭套接字，无需调用shutdown()
	fclose(fp);
	closesocket(cSock);

	WSACleanup();
	//system("pause");
	return 0;
}

//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
using namespace std;

//#define BUF_SIZE  1024
//int main()
//{
//	FILE *fp = fopen("12.mp4", "rb");  //以二进制方式打开文件
//	if (fp == NULL) {
//		printf("Cannot open file, press any key to exit!\n");
//		system("pause");
//		exit(0);
//	}
//
//	FILE *fpW = fopen("34.mp4", "wb");  //以二进制方式打开文件
//	if (fpW == NULL) {
//		printf("Cannot open file, press any key to exit!\n");
//		system("pause");
//		exit(0);
//	}
//	//循环发送数据，直到文件结尾
//	char buffer[BUF_SIZE] = { 0 };  //缓冲区
//	int nCount;
//	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
//		fwrite(buffer, nCount, 1, fpW);
//	}
//
//	
//	system("pause");
//	return 0;
//}