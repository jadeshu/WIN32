#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

//�ַ�����������С
#define MAX_TEXT_LEN 100


//1. ��ʼ���׽��ֿ�
//2. �����׽���
//3. ���ͽ�������
int main()
{
	WSADATA wsData;
	int nRet = WSAStartup(0x0202, &wsData);
	if (nRet)
	{
		printf("----WSAStartup��ʼ��ʧ��\n----");
	}

	//�����׽���(������֪������ʲôЭ����׽���)
	SOCKET sClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sClient == INVALID_SOCKET)
	{
		return -1;
	}
	printf("----UDP�����׽��ֳɹ�!----\n");

	struct sockaddr_in serverAddr;			//����ͻ��˵���Ϣ
	int nSerAddrLen = sizeof(sockaddr_in);	//����ͻ�����Ϣ�ֽ���
	memset(&serverAddr, 0, nSerAddrLen);		//�������Ϊ0

	serverAddr.sin_family = AF_INET;			//����������
	serverAddr.sin_port = htons(6000);		//�˿�
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1")/*inet_addr("127.0.0.1")*/;	//IP

	char recBuffer[MAX_TEXT_LEN] = {0};
	char msgSend[] = "�ѽ��ܵ���������Ϣ";
	while (true)
	{
		printf("----��������������������������͵����� ��С%d�ֽ� ���з���----\n",MAX_TEXT_LEN);
		//��ȡ�����ַ�
		gets_s(recBuffer,MAX_TEXT_LEN);
		sendto(sClient, recBuffer, strlen(recBuffer), 0,(sockaddr*)&serverAddr, nSerAddrLen);
		
		int nRetLen = recvfrom(sClient, recBuffer, MAX_TEXT_LEN, 0, 0/*(struct sockaddr*)&serverAddr*/, 0/*&nSerAddrLen*/);
		recBuffer[nRetLen] = 0;
		printf("������Ϣ��%s ��IP:[%s] �˿ڣ�[%d]\n", recBuffer, inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
	}
	closesocket(sClient);
	WSACleanup();
	return 0;
}