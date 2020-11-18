#include "stdafx.h"
#include "SocketSer.h"

CSocketSer::CSocketSer()
{
	m_UserNum = 0;
	m_SocketSer = INVALID_SOCKET;
	FD_ZERO(&m_ReadSet);
	FD_ZERO(&m_WriteSet);
	FD_ZERO(&m_ExceptSet);

	WSADATA wsaData;
	int i = ::WSAStartup(MAKEWORD(2,2),&wsaData);
	Socket();
}

CSocketSer::~CSocketSer()
{
	::WSACleanup();
}


bool CSocketSer::Socket()
{
	m_SocketSer = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (INVALID_SOCKET == m_SocketSer)
	{
		//printf("创建套接字失败!%ld\n",WSAGetLastError());
		::WSACleanup();
		return false;
	}
	return true;
}


int CSocketSer::Bind(const struct sockaddr_in * name,int namelen)
{
	if (m_SocketSer == INVALID_SOCKET)
	{
		::closesocket(m_SocketSer);
		return INVALID_SOCKET;
	}
	int ret = ::bind(m_SocketSer, (sockaddr*)name, namelen);
	return ret;
}


int CSocketSer::Listen()
{
	int ret = ::listen(m_SocketSer,SOMAXCONN);
	if (SOCKET_ERROR == ret)
	{
		closesocket(m_SocketSer);
	}

	FD_SET(m_SocketSer,&m_ReadSet);
	return ret;
}


int CSocketSer::Select(fd_set* readfds, const timeval *timeout, fd_set *writefds, fd_set *exceptfds)
{
	while (true)
	{
		fd_set fd = *readfds;
		if (::select(0, &fd, writefds, exceptfds, timeout) > 0) 
		{
			if (FD_ISSET(m_SocketSer, &fd)) 
			{
				sockaddr_in ClientAddress;
				int nClientLength = sizeof(ClientAddress);

				SOCKET ClientSocket = accept(m_SocketSer, (SOCKADDR*)&ClientAddress, &nClientLength);

				if (INVALID_SOCKET == ClientSocket)
				{
					//printf("接受客户失败!%ld\n",WSAGetLastError());
					closesocket(ClientSocket);
				}

				//创建临时用户
				stUser userTmp;
				char* addr = inet_ntoa(ClientAddress.sin_addr);
				userTmp.userSocket = ClientSocket;
				userTmp.userPort = ClientAddress.sin_port;
				int is = strlen(addr);
				strcpy_s(userTmp.userIP,strlen(addr)*sizeof(char)+2,addr);

				//添加用户到链表中
				m_UserList.push_back(userTmp);
				m_UserNum++;
				FD_SET(ClientSocket,readfds);
			}

			for (list<stUser>::iterator lit= m_UserList.begin(); lit!=m_UserList.end(); ++lit)
			{

				if (FD_ISSET(lit->userSocket, &fd))
				{
					int nBytes = recv(lit->userSocket, lit->msg, MAX_BUFFER_LEN, 0);

					if ((0 == nBytes) || (SOCKET_ERROR == nBytes))
					{
						if (0 != nBytes)
						{
							//printf(_T("\n接收客户端数据失败,错误码: 0x%08X.",WSAGetLastError())
						}

						//清除
						FD_CLR(lit->userSocket,readfds);
						closesocket(lit->userSocket);
						m_UserList.erase(lit);
						m_UserNum--;		//人数减去
						if (m_UserList.empty())
						{
							break;
						}
						continue;
					}
					(*lit).msg[nBytes] = '\0';
					for (list<stUser>::iterator it= m_UserList.begin();it!=m_UserList.end();++it)
					{
						//if (lit->userSocket == it->userSocket)
						//{
						//	continue;
						//}
						send(it->userSocket, lit->msg, strlen(lit->msg)*sizeof(char), 0);	
					}	
				}
			}
		}
	}
}