#pragma once
#include "afxwin.h"


// CDengLuDlg �Ի���

class CDengLuDlg : public CDialog
{
	DECLARE_DYNAMIC(CDengLuDlg)

public:
	CDengLuDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDengLuDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	//CEdit m_userName;
	//CEdit m_PassWord;
};
