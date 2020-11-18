#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

//�ַ�����������С
#define MAX_TEXT_LEN 100

//1. ��ʼ���׽��ֿ�
//2. �����׽���
//3. ���׽���
//4. ���ͽ�������
int main()
{
	WSADATA wsData;
	int nRet = WSAStartup(0x0202, &wsData);
	if (nRet)
	{
		printf("----WSAStartup��ʼ��ʧ��\n----");
	}

	//�����׽���(������֪������ʲôЭ����׽���)
	SOCKET sServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sServer == INVALID_SOCKET)
	{
		return -1;
	}
	printf("----UDP�����׽��ֳɹ�!----\n");
	struct sockaddr_in serverAddr;			//����ͻ��˵���Ϣ
	int nSerAddrLen = sizeof(sockaddr_in);	//����ͻ�����Ϣ�ֽ���
	memset(&serverAddr, 0, nSerAddrLen);		//�������Ϊ0

	serverAddr.sin_family = AF_INET;			//����������
	serverAddr.sin_port = htons(6000);		//�˿�
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY)/*inet_addr("127.0.0.1")*/;	//IP

	//�׽������������(��ϵͳ֪���˿� IP)
	if (bind(sServer, (sockaddr*)&serverAddr, nSerAddrLen))	//����0ʱ�ɹ� ����ʧ�ܻ��ߴ���
	{
		printf("----UDP���׽���ʧ��----\n");
		closesocket(sServer);
		WSACleanup();
		return -1;
	}
	printf("----UDP���׽��ֳɹ�----\n");

	struct sockaddr_in ClientAddr;	//����ͻ��˵���Ϣ
	int nClientAddrLen = sizeof(sockaddr_in);
	memset(&ClientAddr, 0, nClientAddrLen);		//����ͻ�����Ϣ�ֽ���

	char recBuffer[MAX_TEXT_LEN] = {0};
	char msgSend[] = "good job";
	while (true)
	{
		int nRetLen = recvfrom(sServer, recBuffer, MAX_TEXT_LEN, 0, (struct sockaddr*)&ClientAddr, &nClientAddrLen);

		recBuffer[nRetLen] = 0;
		printf("������Ϣ��%s ��IP:[%s] �˿ڣ�[%d]\n", recBuffer, inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

		//�������ݳɹ����͸��ͻ���
		sendto(sServer, msgSend, strlen(msgSend), 0, (sockaddr*)&ClientAddr, nClientAddrLen);
	}
	closesocket(sServer);
	WSACleanup();
	return 0;
}