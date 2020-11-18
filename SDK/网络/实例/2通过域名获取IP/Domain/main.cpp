//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
using namespace std;
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


int main()
{
	WSAData ws;
	int nRet = WSAStartup(MAKEWORD(2, 2), &ws);
	if (nRet)
	{
		cout << "----WSAStartup初始化失败----" << endl;
	}

	//gethostbyname();
	char buf[32] = { 0 };
	gethostname(buf, 512);

	HOSTENT *phost =  gethostbyname("www.youku.com");
	if (!phost) {
		puts("Get IP address error!");
		system("pause");
		exit(0);
	}
	cout << phost->h_name << endl;
	cout << phost->h_length << endl;
	
	//别名
	for (int i = 0; phost->h_aliases[i]; i++)
	{
		printf("Aliases %d: %s\n", i + 1, phost->h_aliases[i]);
	}

	//地址类型
	printf("Address type: %s\n", (phost->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

	//IP地址
	for (int i = 0; phost->h_addr_list[i]; i++)
	{
		printf("IP addr %d: %s\n", i + 1, inet_ntoa(*(struct in_addr*)(phost->h_addr_list[i])));
	}

	WSACleanup();
	system("pause");
	return 0;
}