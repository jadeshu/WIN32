#if !defined(AFX_SOCKETSERVER_H__DB7CF4B9_5D61_44CA_9BA7_BA767FBE83C6__INCLUDED_)
#define AFX_SOCKETSERVER_H__DB7CF4B9_5D61_44CA_9BA7_BA767FBE83C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SocketClient.h"
class CSocketServer : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CSocketServer();
	virtual ~CSocketServer();

// Overrides
public:
	void DeleteRemoteSocket(CSocketClient* pSock);
	POSITION GetRemoteSocketPos(CSocketClient* pSock);
	CSocketClient* GetRemoteSocket(int pSock);
	CPtrList m_clientList;
	HWND m_hMsgWnd;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketServer)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocketServer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKETSERVER_H__DB7CF4B9_5D61_44CA_9BA7_BA767FBE83C6__INCLUDED_)
