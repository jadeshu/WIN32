#pragma once
#include "afxwin.h"


// CDengLuDlg 对话框

class CDengLuDlg : public CDialog
{
	DECLARE_DYNAMIC(CDengLuDlg)

public:
	CDengLuDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDengLuDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	//CEdit m_userName;
	//CEdit m_PassWord;
};
