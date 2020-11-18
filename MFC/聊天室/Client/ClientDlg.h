
// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "MySocket.h"
#include "afxcmn.h"

// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CBitmap m_bmBack;		//����ͼƬ
	CBrush  m_brBack;		//������ˢ
	CBitmapButton m_bSend;  //���Ͱ�ť

	CMySocket m_Socket;		//�׽���
	CString m_UserName;		//�û�����
	int  m_curIndex;		//�б�ѡ������
	CString m_pName[100];	//
	int m_curNum;
	


	BOOL m_bCheckBtn;
	CString m_Ctx;
	CString m_Say;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
