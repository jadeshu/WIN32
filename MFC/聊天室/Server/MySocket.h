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
	ULONG m_Total;								//对话数量
	CString m_Player;
	void AttachCWnd(CWnd *pWnd);				//将Socket与操作窗体绑定

	public:
	virtual void OnReceive(int nErrorCode);	//接收到消息
	virtual void OnClose(int nErrorCode);	//关闭消息
	virtual void OnAccept(int nErrorCode);	//接受连接
};

#endif // !defined(AFX_MYSOCKET_H__8BB6F3A7_3F23_4285_8487_851C322D1DF7__INCLUDED_)
