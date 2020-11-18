#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxext.h"


// CLogDlg �Ի���

class CLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogDlg();

// �Ի�������
	enum { IDD = IDD_LOGDLG };
	
	CBitmap m_bmBack;		//����ͼƬ
	CBrush  m_brBack;		//������ˢ
	CImageList m_imageList; //ͼ���б�
	
	TCHAR m_IpAddrS[32];	//�û�IP��ַ�ַ���
	int m_imgNum;			//�û�ѡ���ͼ������


	/************************************************************************/
	/* �󶨱���                                                             */
	/************************************************************************/
	CIPAddressCtrl m_IpAddrCtrl;	//�û�IP��ַ
    CComboBoxEx m_ComboBoxPhotoImg;	//�û�ͼ��
	CString m_UserName;				//�û�����	
	CBitmapButton m_bLogIn;			//��½��ť
	CBitmapButton m_bCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
		
	virtual void OnOK();
	
	
};
