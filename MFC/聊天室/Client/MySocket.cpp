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
	if(pWnd)
		pWnd->SendMessage(SOCKET_EVENT,(long)this,RETR);//发送SOCKET_EVENT给对话框，this指m_socket这个对象

	CSocket::OnReceive(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode) 
{
	if(pWnd)
		pWnd->SendMessage(SOCKET_EVENT,(long)this,CLOSE);

	CSocket::OnClose(nErrorCode);
}

void CMySocket::OnAccept(int nErrorCode) 
{
	if(pWnd)
		pWnd->SendMessage(SOCKET_EVENT,(long)this,ACCEPT);//接受登入的消息

	CSocket::OnAccept(nErrorCode);
}

void CMySocket::AttachCWnd(CWnd *pW)    //CWnd S是WINDOWS的一个基类，对话框，按钮等都是从它派生过来
{
	pWnd = pW;
}
