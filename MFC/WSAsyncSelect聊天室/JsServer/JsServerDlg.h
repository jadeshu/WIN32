
// JsServerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "SocketServer.h"

// CJsServerDlg 对话框
class CJsServerDlg : public CDialog
{
// 构造
public:
	CJsServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JSSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
