
// MsgSerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "SocketSer.h"
#include "SocketSer.h"

// CMsgSerDlg 对话框
class CMsgSerDlg : public CDialog
{
// 构造
public:
	CMsgSerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MSGSER_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CSocketSer m_SocketSer;
	int  m_Port;
	

public:
	void setListCtlStyle();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedStartBtn();
	CListCtrl m_listCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
