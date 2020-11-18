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
		cout << "----WSAStartup��ʼ��ʧ��----" << endl;
	}

	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
	{
		return -1;
	}

	sockaddr_in sockAddr;					// �������˵���Ϣ
	int sockAddrLen = sizeof(sockaddr_in);	// ����������Ϣ�ֽ���
	memset(&sockAddr, 0, sizeof(sockAddr)); // �������Ϊ0

	sockAddr.sin_family = AF_INET;	// ����������
	//sockAddr.sin_addr.s_addr = inet_addr(pChIP);
	sockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);// INADDR_ANY��ʾ�κ�IP
	sockAddr.sin_port = htons(PORT);	// �˿�

	//�׽������������
	if (bind(servSock, (sockaddr*)&sockAddr, sockAddrLen))	//����0ʱ�ɹ� ����ʧ�ܻ��ߴ���
	{
		cout << "----���׽���ʧ��----" << endl;
		closesocket(servSock);
		WSACleanup();
		return -1;
	}
	listen(servSock, MAXCONNET);
	cout << "������������:\n������...\n" << endl;

	struct sockaddr_in clientAddr;			//����ͻ��˵���Ϣ
	int nClientArrLen = sizeof(clientAddr);	//����ͻ�����Ϣ�ֽ���

	SOCKET sClient = INVALID_SOCKET;
		//���ܵ����Ŀͻ���
	sClient = accept(servSock, (struct sockaddr*)&clientAddr, &nClientArrLen);

	cout << "----�ͻ���" << sClient << "����----"<< endl;
		
		// TODO
	FILE* fp = fopen("12.jpg", "rb");
	if (fp == nullptr)
	{
		return 0;
	}
	char buffer[BUF_SIZE] = { 0 };
	int nCount = 0;
	// ��ȡ�ļ�
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0)
	{
		// ��������
		send(sClient, buffer, nCount, 0);
	}

	// ���Źرգ���ֹ����δ�������
	shutdown(sClient, SD_SEND);
	// ����ס�����ͻ��˹ر��׽���closeSocket�󣬴˺�������
	recv(sClient, buffer, BUF_SIZE, 0);
		
	fclose(fp);
	closesocket(sClient);
	closesocket(servSock);
	WSACleanup();
	//system("pause");
	return 0;
}