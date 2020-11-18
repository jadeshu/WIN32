#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")


unsigned int nPerNum = 0;	//��������
struct fd_set fdClientSkt;	//�ļ��������� ---���Կͻ�����Ϣ
#define MAX_TEXT_LEN 100	//�����ַ�����ֽ���


DWORD __stdcall ClientProcess( LPVOID lpThreadParameter)
{
	//ת������ֵ
	//fd_set *pFdClient = (fd_set*)(lpThreadParameter);

	char RecBuffer[MAX_TEXT_LEN] = {0};
	char tongzhi[] = "���������յ�������Ϣ��";
	int nRet = 0;  //����ֵ	
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
						printf("�ͻ���:%d����ǿ�ƹر�\n", fRead.fd_array[i]);
						
						FD_CLR(fRead.fd_array[i],&fdClientSkt);
						closesocket(fRead.fd_array[i]);
						nPerNum--;
						printf("----����:%d���ͻ�----\n",nPerNum);
					}
					else if (nRet == 0)
					{
						printf("�ͻ���:%d�����˳�\n", fRead.fd_array[i]);
						
						FD_CLR(fRead.fd_array[i],&fdClientSkt);
						closesocket(fRead.fd_array[i]);
						nPerNum--;
					}
					else
					{
						RecBuffer[nRet] = '\0';
						printf("�ͻ���:%d���� %s\n", fRead.fd_array[i], RecBuffer);

						//����֪ͨ���ͻ���
						/*nRet = */send(fRead.fd_array[i], tongzhi, strlen(tongzhi)*sizeof(char), 0);
						//if (nRet == SOCKET_ERROR)
						//{
						//	printf("�ͻ���:%d����ǿ�ƹر�\n", fdClientSkt.fd_array[i]);
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

	//������ͻ������Ӵ�����߳�
	CreateThread(NULL, 0, ClientProcess, NULL/*(void*)&fdClientSkt*/, 0, NULL);

	struct sockaddr_in clientAddr;	//����ͻ��˵���Ϣ
	int nClientArrLen = sizeof(clientAddr);	//����ͻ�����Ϣ�ֽ���
	while (true)
	{
		//���ܵ����Ŀͻ���
		SOCKET sClient = accept(sServer, (struct sockaddr*)&clientAddr, &nClientArrLen);	

		FD_SET(sClient,&fdClientSkt);
		++nPerNum;
		printf("----�¿ͻ�:%d����,����:%d���ͻ�----\n",sClient,nPerNum);

	}
	FD_ZERO(&fdClientSkt);
	closesocket(sServer);
	WSACleanup();
	return 0;
}