#if !defined(AFX_SOCKETCLIENT_H__FFE761D4_28DD_4A9E_8BB1_508CA6798F96__INCLUDED_)
#define AFX_SOCKETCLIENT_H__FFE761D4_28DD_4A9E_8BB1_508CA6798F96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSocketClient command target
#define MAXSOCKBUF	1024
class CSocketClient : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CSocketClient();
	virtual ~CSocketClient();

// Overrides
public:	
	void Init();
	int m_nLength;
	CString m_strHost;
	CString m_strIP;
	char m_szSendBuf[MAXSOCKBUF];
	char m_szReceBuf[MAXSOCKBUF];
	HWND m_hMsgWnd;
	BOOL m_bConnect;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketClient)
	public:
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocketClient)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKETCLIENT_H__FFE761D4_28DD_4A9E_8BB1_508CA6798F96__INCLUDED_)
