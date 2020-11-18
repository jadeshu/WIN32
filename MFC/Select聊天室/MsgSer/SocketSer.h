#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <list>
using namespace std;
#define MAX_BUFFER_LEN 512

struct stUser
{
	SOCKET userSocket;		//�û��׽���
	unsigned int userPort;	//�ͻ��˿�
	//char userName[16];		//�ͻ���
	char userIP[20];		//�ͻ�IP
	char msg[MAX_BUFFER_LEN];			//�ͻ���Ϣ
};

class CSocketSer
{
public:
	CSocketSer();
	~CSocketSer();

	SOCKET getSocket()
	{
		return m_SocketSer;
	}
	int Bind(const struct sockaddr_in * name,int namelen); //����0ʱ�ɹ� ����ʧ�ܻ��ߴ���
	int Listen();
	int Select(fd_set* readfds, const timeval *timeout, fd_set *writefds = 0, fd_set *exceptfds = 0);
	//bool Send( SOCKET s,const char* buf,int len,int flags = 0);

protected:
	bool Socket();  //����Socket
	//�û���Ϣ�ṹ��	

public:
	
	SOCKET		  m_SocketSer;					//�������׽���
	list<stUser> m_UserList;					//�û��б�
	fd_set	m_ReadSet, m_WriteSet, m_ExceptSet;
	int			  m_UserNum;					//�û�����
	BYTE          m_szBuffer[MAX_BUFFER_LEN];	//������
	//CList<SOCKET> m_SocketList;				//��Ҫ�����׽���
};
#endif