
// MsgSerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "SocketSer.h"
#include "SocketSer.h"

// CMsgSerDlg �Ի���
class CMsgSerDlg : public CDialog
{
// ����
public:
	CMsgSerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MSGSER_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CSocketSer m_SocketSer;
	int  m_Port;
	

public:
	void setListCtlStyle();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
