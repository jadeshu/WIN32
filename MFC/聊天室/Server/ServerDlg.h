
// ServerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MySocket.h"

// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	
	
// 实现
protected:
	HICON m_hIcon;
	CBitmap m_bmBack;		//背景图片
	CBrush  m_brBack;		//背景画刷
	CBitmapButton m_bExit;	//按钮
	CCriticalSection m_criticalSection;	//临界区
	

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMySocket	m_socket;
	CListCtrl	m_List;
	CString		m_Ctx;
	afx_msg void OnBnClickedExitBtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnSocket(WPARAM wParam,LPARAM lParam);

	void ClosePlayer(CMySocket* socketFrom);
	void Append(TCHAR *msg);
	void ParserPkt(CMySocket *socketFrom);
	
};
