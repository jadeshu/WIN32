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
		AfxMessageBox(_T("Windows ͨ�Ŷ˿ڳ�ʼ��ʧ�ܡ�"));
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
		pWnd->SendMessage(SOCKET_EVENT,(long)this,RETR);//����SOCKET_EVENT���Ի���thisָm_socket�������

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
		pWnd->SendMessage(SOCKET_EVENT,(long)this,ACCEPT);//���ܵ������Ϣ

	CSocket::OnAccept(nErrorCode);
}

void CMySocket::AttachCWnd(CWnd *pW)    //CWnd S��WINDOWS��һ�����࣬�Ի��򣬰�ť�ȶ��Ǵ�����������
{
	pWnd = pW;
}
