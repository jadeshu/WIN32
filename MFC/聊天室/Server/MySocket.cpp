// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "MySocket.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySocket

CMySocket::CMySocket()
{
	pWnd = NULL;
	m_Total = 0;
	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("Windows 通信端口初始化失败。"));
	}
}

CMySocket::~CMySocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMySocket member functions

void CMySocket::OnReceive(int nErrorCode) 
{
	m_Total++;

	if(pWnd)
		pWnd->SendMessage(SOCKET_EVENT,(WPARAM)this,RETR);	//this 表示当前通信的SOCKET指针

	CSocket::OnReceive(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode) 
{
	if(pWnd)
		pWnd->SendMessage(SOCKET_EVENT,(WPARAM)this,CLOSE);

	CSocket::OnClose(nErrorCode);
}

void CMySocket::OnAccept(int nErrorCode) 
{
	if(pWnd)
		pWnd->SendMessage(SOCKET_EVENT,(WPARAM)this,ACCEPT);

	CSocket::OnAccept(nErrorCode);
}

void CMySocket::AttachCWnd(CWnd *pW)
{
	pWnd = pW;
}
