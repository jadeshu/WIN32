// SocketServer.cpp : implementation file
//

#include "stdafx.h"
#include "SocketServer.h"
#include "SocketClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocketServer

CSocketServer::CSocketServer()
{
	
}

CSocketServer::~CSocketServer()
{
	while (!m_clientList.IsEmpty())
	{
		CSocketClient* client=(CSocketClient*)m_clientList.RemoveHead();
		client->Close();
		delete client;
	}
	m_clientList.RemoveAll();
	if (m_hSocket!=INVALID_SOCKET)
		Close();
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocketServer, CAsyncSocket)
	//{{AFX_MSG_MAP(CSocketServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocketServer member functions

void CSocketServer::OnAccept(int nErrorCode) 
{	
	char* pLog=new char[200];	
	if (nErrorCode)
	{
		if (nErrorCode==WSAENETDOWN)
			sprintf(pLog, "网络故障!");
		else 
			sprintf(pLog, "FD_ACCEPT未知错误");
		return;
	}
	else
	{
		sockaddr address;
		CString IPaddr;
		UINT port;
		int address_len;
		address_len=sizeof(address);
		CSocketClient* pSocket=new CSocketClient();
		pSocket->m_hMsgWnd=m_hMsgWnd;	
		if (this->Accept(*pSocket,&address,&address_len))
		{				
			pSocket->AsyncSelect(FD_WRITE|FD_READ|FD_CLOSE);		
			pSocket->GetPeerName(IPaddr,port);
			pSocket->m_strIP=IPaddr;
			m_clientList.AddTail(pSocket);
			sprintf(pLog, "接收客户端连接。IP=%s;端口=%d", IPaddr, port);									
		}
		else
		{
			int Error=GetLastError();
			if (Error==WSAECONNREFUSED)
				sprintf(pLog, "拒绝连接");
			else
			{
				sprintf(pLog,"WSAAccept失败，错误代码: %d",Error);
			}
			delete pSocket;
			return;
		}
	}

	if (m_hMsgWnd!=NULL)	
		::SendMessage(m_hMsgWnd, WM_SOCKET_LOG, (WPARAM)pLog, strlen(pLog));
	
	CAsyncSocket::OnAccept(nErrorCode);
}

void CSocketServer::OnClose(int nErrorCode) 
{
	while (!m_clientList.IsEmpty())
	{
		CSocketClient* client=(CSocketClient*)m_clientList.RemoveHead();
		client->Close();
		delete client;
	}
	m_clientList.RemoveAll();
	
	if (m_hSocket!=INVALID_SOCKET)
		Close();
	CAsyncSocket::OnClose(nErrorCode);
}

CSocketClient* CSocketServer::GetRemoteSocket(int pSock)
{
	POSITION pos=m_clientList.GetHeadPosition();	
	while(pos!=NULL)
	{	
		CSocketClient* client= (CSocketClient*)m_clientList.GetNext(pos);		
		if ((int)client->m_hSocket==pSock)
		{		
			return client;
		}
	}	
	return NULL;
}

POSITION CSocketServer::GetRemoteSocketPos(CSocketClient* pSock)
{
	POSITION pos=m_clientList.GetHeadPosition();
	while(pos!=NULL)
	{		
		POSITION position;
		position=pos;
		CSocketClient* client= (CSocketClient*)m_clientList.GetNext(pos);	
		if (client==pSock)
			return position;
	}
	return NULL;
}

void CSocketServer::DeleteRemoteSocket(CSocketClient* pSock)
{	
	pSock->Close();
	POSITION pos=m_clientList.GetHeadPosition();
	POSITION temp;
	while(pos!=NULL)
	{	
		temp=pos;
		CSocketClient* client= (CSocketClient*)m_clientList.GetNext(pos);		
		if (client==pSock)
		{				
			m_clientList.RemoveAt(temp);
			client->Close();
			delete client;
			break;
		}
	}	
	return ;
}

