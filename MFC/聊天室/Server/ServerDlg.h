
// ServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MySocket.h"

// CServerDlg �Ի���
class CServerDlg : public CDialogEx
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	
	
// ʵ��
protected:
	HICON m_hIcon;
	CBitmap m_bmBack;		//����ͼƬ
	CBrush  m_brBack;		//������ˢ
	CBitmapButton m_bExit;	//��ť
	CCriticalSection m_criticalSection;	//�ٽ���
	

	// ���ɵ���Ϣӳ�亯��
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
