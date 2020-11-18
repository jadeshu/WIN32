#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

#define MAX_TEXT_LEN 100
DWORD __stdcall ClientProcess( LPVOID lpThreadParameter)
{
	SOCKET sClient = (SOCKET)lpThreadParameter;
	char RecBuffer[MAX_TEXT_LEN] = {0};
	char tongzhi[] = "���յ�����������Ϣ�ˣ�";

	while (true)
	{
		int nRetBufferLen = recv(sClient, RecBuffer, MAX_TEXT_LEN, 0);
		if (nRetBufferLen == SOCKET_ERROR)
		{
			printf("�ͻ���%d����:%s ����ǿ�ƹر�\n", sClient);
			closesocket(sClient);
			return -1;

		}
		if (nRetBufferLen == 0)
		{
			printf("�ͻ���%d����:%s �Ѿ��˳�\n", sClient);
			break;
		}

		RecBuffer[nRetBufferLen] = 0;
		printf("�ͻ���%d����:%s\n", sClient, RecBuffer);

		nRetBufferLen = send(sClient, tongzhi, strlen(tongzhi)*sizeof(char), 0);
		if (nRetBufferLen == SOCKET_ERROR)
		{
			printf("�ͻ���%d����:%s ����ǿ�ƹر�\n", sClient);
			closesocket(sClient);
			return -1;
		}		
	}
	closesocket(sClient);
	return 0;
}

//1. ��ʼ���׽��ֿ�
//2. �����׽���
//3. ���׽���
//4. �����׽���
//4. ���տͻ��˵���
int main()
{
	WSADATA wsData;
	int nRet = WSAStartup(0x0202, &wsData);
	if (nRet)
	{
		printf("----WSAStartup��ʼ��ʧ��\n----");
	}

	//�����׽���(������֪������ʲôЭ����׽���)
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sServer == INVALID_SOCKET)
	{
		return -1;
	}
	printf("----�����׽��ֳɹ�!----\n");
	struct sockaddr_in serverAddr;			//����ͻ��˵���Ϣ
	int nSerAddrLen = sizeof(sockaddr_in);	//����ͻ�����Ϣ�ֽ���
	memset(&serverAddr, 0, nSerAddrLen);		//�������Ϊ0

	serverAddr.sin_family = AF_INET;			//����������
	serverAddr.sin_port = htons(6000);		//�˿�
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY)/*inet_addr("127.0.0.1")*/;	//IP

	//�׽������������(��ϵͳ֪���˿� IP)
	if (bind(sServer, (sockaddr*)&serverAddr, nSerAddrLen))	//����0ʱ�ɹ� ����ʧ�ܻ��ߴ���
	{
		printf("----���׽���ʧ��----\n");
		closesocket(sServer);
		WSACleanup();
		return -1;
	}
	printf("----���׽��ֳɹ�----\n");
	//�����󶨵��׽���
	printf("----�����׽���----\n");
	listen(sServer,SOMAXCONN);
	
	struct sockaddr_in clientAddr;	//����ͻ��˵���Ϣ
	int nClientArrLen = sizeof(clientAddr);	//����ͻ�����Ϣ�ֽ���
	while (true)
	{
		SOCKET sClient;
		//���ܵ����Ŀͻ���
		sClient = accept(sServer, (struct sockaddr*)&clientAddr, &nClientArrLen);	

		printf("----�и��ͻ���%d����----\n",sClient);
		CreateThread(NULL, 0, ClientProcess, (void*)sClient, 0, NULL);
		Sleep(5);
	}
	closesocket(sServer);
	WSACleanup();
	return 0;
}