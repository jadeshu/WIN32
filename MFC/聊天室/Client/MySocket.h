#if !defined(AFX_MYSOCKET_H__8BB6F3A7_3F23_4285_8487_851C322D1DF7__INCLUDED_)
#define AFX_MYSOCKET_H__8BB6F3A7_3F23_4285_8487_851C322D1DF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//
#include <afxsock.h>
#define SOCKET_EVENT WM_USER + 8191

enum {ACCEPT = 0,SEND = 1,RETR = 2,CLOSE = 3};

/////////////////////////////////////////////////////////////////////////////
// CMySocket command target

class CMySocket : public CSocket
{
// Attributes
public:

	CWnd *pWnd;
// Operations
public:
	CMySocket();
	virtual ~CMySocket();

// Overrides
public:
//	CString m_Player;
	void AttachCWnd(CWnd *pWnd);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
};
#endif // !defined(AFX_MYSOCKET_H__8BB6F3A7_3F23_4285_8487_851C322D1DF7__INCLUDED_)