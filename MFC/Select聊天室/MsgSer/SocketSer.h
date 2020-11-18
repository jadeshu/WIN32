#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <list>
using namespace std;
#define MAX_BUFFER_LEN 512

struct stUser
{
	SOCKET userSocket;		//用户套接字
	unsigned int userPort;	//客户端口
	//char userName[16];		//客户名
	char userIP[20];		//客户IP
	char msg[MAX_BUFFER_LEN];			//客户消息
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
	int Bind(const struct sockaddr_in * name,int namelen); //返回0时成功 否则失败或者错误
	int Listen();
	int Select(fd_set* readfds, const timeval *timeout, fd_set *writefds = 0, fd_set *exceptfds = 0);
	//bool Send( SOCKET s,const char* buf,int len,int flags = 0);

protected:
	bool Socket();  //创建Socket
	//用户信息结构体	

public:
	
	SOCKET		  m_SocketSer;					//服务器套接字
	list<stUser> m_UserList;					//用户列表
	fd_set	m_ReadSet, m_WriteSet, m_ExceptSet;
	int			  m_UserNum;					//用户人数
	BYTE          m_szBuffer[MAX_BUFFER_LEN];	//缓冲区
	//CList<SOCKET> m_SocketList;				//需要检测的套接字
};
#endif