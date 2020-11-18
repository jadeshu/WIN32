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
		printf("----WSAStartup��ʼ��ʧ��\n----");
	}

	//�����׽���(������֪������ʲôЭ����׽���)
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sServer == INVALID_SOCKET)
	{
		return -1;
	}
	g_Socket[dwTotal] = sServer;
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

	g_Event[dwTotal] = WSACreateEvent();

	nRet  = WSAEventSelect(g_Socket[dwTotal], g_Event[dwTotal], FD_ACCEPT|FD_CLOSE);
	if ((nRet != 0) || (nRet == SOCKET_ERROR))
	{
		printf("----�¼�ѡ��ʧ��----\n");
		closesocket(sServer);
		WSACleanup();
		return -1;
	}

	//�����󶨵��׽���
	printf("----�����׽���----\n");
	listen(sServer,SOMAXCONN);

	//������ͻ������Ӵ�����߳�
	CreateThread(NULL, 0, ClientProcess, NULL, 0, NULL);

	system("pause");	//���߳���ͣ
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
			//��ʱ
			//printf("�ͻ���:��ʱ\n");
			continue;
		}

		WSAEnumNetworkEvents(g_Socket[dwTotal],g_Event[dwTotal],&entworkEv);
		if (entworkEv.lNetworkEvents&FD_ACCEPT)	// �����¿ͻ�����
		{
			sockaddr_in ClientAddress;
			int nClientLength = sizeof(ClientAddress);

			SOCKET ClientSocket = accept(g_Socket[dwTotal], (SOCKADDR*)&ClientAddress, &nClientLength);

			if (INVALID_SOCKET == ClientSocket)
			{
				//printf("���ܿͻ�ʧ��!%ld\n",WSAGetLastError());
				closesocket(ClientSocket);
				continue;
			}
			dwTotal++;
			g_Socket[dwTotal] = ClientSocket;


			g_Event[dwTotal] = WSACreateEvent();

			int nRet  =  WSAEventSelect(g_Socket[dwTotal], g_Event[dwTotal], FD_READ|FD_WRITE|FD_CLOSE);
			if ((nRet != 0) || (nRet == SOCKET_ERROR))
			{
				printf("----�¼�ѡ��ʧ��----\n");
				closesocket(g_Socket[dwTotal]);
				WSACleanup();
				return -1;
			}
		}
		if (entworkEv.lNetworkEvents&FD_READ)
		{
		// ...���������Ϣ
			break;
		}
	}
	return 0;
}