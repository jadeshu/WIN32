
// ClientDlg.h : 头文件
//

#pragma once
#include "MySocket.h"
#include "afxcmn.h"

// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CBitmap m_bmBack;		//背景图片
	CBrush  m_brBack;		//背景画刷
	CBitmapButton m_bSend;  //发送按钮

	CMySocket m_Socket;		//套接字
	CString m_UserName;		//用户名称
	int  m_curIndex;		//列表选项索引
	CString m_pName[100];	//
	int m_curNum;
	


	BOOL m_bCheckBtn;
	CString m_Ctx;
	CString m_Say;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedSend();
	afx_msg LRESULT OnSocket(WPARAM wParam,LPARAM lParam);

	
	CListCtrl m_List;
};
