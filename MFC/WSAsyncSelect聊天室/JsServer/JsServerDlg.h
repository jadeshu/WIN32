
// JsServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "SocketServer.h"

// CJsServerDlg �Ի���
class CJsServerDlg : public CDialog
{
// ����
public:
	CJsServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JSSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void WriteLog(CString log);

	CSocketServer* pSocketServer;

	CIPAddressCtrl m_IP;
	afx_msg void OnBnClickedButtonListen();
	afx_msg void OnBnClickedButtonSend();
	afx_msg LRESULT OnLogMsg(WPARAM dwEvent, LPARAM dwLen);
	afx_msg LRESULT OnRecvMsg(WPARAM dwEvent, LPARAM dwLen);
	CString m_Log;
	CString m_editSend;
	CString m_editRecv;
	CString m_Port;
};
