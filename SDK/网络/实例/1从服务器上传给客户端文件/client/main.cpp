//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
//#include <string>
#include <iostream>
using namespace std;
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//�ַ�����������С
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
		cout << "----WSAStartup��ʼ��ʧ��----" << endl;
	}

	SOCKET cSock = socket(AF_INET, SOCK_STREAM, 0);
	if (cSock == INVALID_SOCKET)
	{
		return -1;
	}

	sockaddr_in sockAddr;					// �������˵���Ϣ
	int sockAddrLen = sizeof(sockaddr_in);	// ����������Ϣ�ֽ���
	memset(&sockAddr, 0, sizeof(sockAddr)); // �������Ϊ0

	sockAddr.sin_family = AF_INET;	// ����������
	sockAddr.sin_addr.s_addr = inet_addr(pChIP);
	sockAddr.sin_port = htons(PORT);	// �˿�
										//�׽������������(��ϵͳ֪���˿� IP)
	if (connect(cSock, (sockaddr*)&sockAddr, sockAddrLen))	//����0ʱ�ɹ� ����ʧ�ܻ��ߴ���
	{
		DWORD i = GetLastError();
		cout << "----���ӷ�����ʧ��,������:" << i << "----" << endl;
		closesocket(cSock);
		WSACleanup();
		return -1;
	}
	
	cout << "----���ӷ������ɹ�----" << endl;

	// �½��������ļ���д��
	FILE *fp = fopen("34.jpg", "wb");
	//ѭ���������ݣ�ֱ���ļ��������
	char buffer[BUF_SIZE] = { 0 };  //�ļ�������
	int nCount;
	// �������ȡ����
	while ((nCount = recv(cSock, buffer, BUF_SIZE, 0)) > 0) {
		// ���ļ�д������
		fwrite(buffer,  1, nCount, fp);
	}
	puts("File transfer success!");
	//�ļ�������Ϻ�ֱ�ӹر��׽��֣��������shutdown()
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
//	FILE *fp = fopen("12.mp4", "rb");  //�Զ����Ʒ�ʽ���ļ�
//	if (fp == NULL) {
//		printf("Cannot open file, press any key to exit!\n");
//		system("pause");
//		exit(0);
//	}
//
//	FILE *fpW = fopen("34.mp4", "wb");  //�Զ����Ʒ�ʽ���ļ�
//	if (fpW == NULL) {
//		printf("Cannot open file, press any key to exit!\n");
//		system("pause");
//		exit(0);
//	}
//	//ѭ���������ݣ�ֱ���ļ���β
//	char buffer[BUF_SIZE] = { 0 };  //������
//	int nCount;
//	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
//		fwrite(buffer, nCount, 1, fpW);
//	}
//
//	
//	system("pause");
//	return 0;
//}