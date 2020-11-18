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
			//��ʱ
			//printf("�ͻ���:��ʱ\n");
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
		printf("----WSAStartup��ʼ��ʧ��\n----");
	}

	//�����׽���(������֪������ʲôЭ����׽���)
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sServer == INVALID_SOCKET)
	{
		return -1;
	}
	//g_Socket[dwTotal] = sServer;
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

	//������ͻ������Ӵ�����߳�
	CreateThread(NULL, 0, ClientProcess, NULL, 0, NULL);

	struct sockaddr_in clientAddr;	//����ͻ��˵���Ϣ
	int nClientArrLen = sizeof(clientAddr);	//����ͻ�����Ϣ�ֽ���
	while (TRUE)
	{
		//���ܵ����Ŀͻ���
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