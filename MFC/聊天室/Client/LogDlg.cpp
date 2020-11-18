// LogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "LogDlg.h"
#include "afxdialogex.h"


// CLogDlg �Ի���

IMPLEMENT_DYNAMIC(CLogDlg, CDialog)

CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
	, m_UserName(_T(""))
{

}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_IpAddrCtrl);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_UserName);
	DDX_Control(pDX, IDOK, m_bLogIn);
	DDX_Control(pDX, IDCANCEL, m_bCancel);
	DDX_Control(pDX, IDC_COMBO_PHOTO_IMG, m_ComboBoxPhotoImg);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLogDlg ��Ϣ�������


HBRUSH CLogDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_DLG)
		return m_brBack;
	return hbr;
}


BOOL CLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//�����û�Ĭ�ϵ�ַ
	m_IpAddrCtrl.SetAddress(127,0,0,1);

	//���ص�½��ȡ����ťͼƬ
	m_bLogIn.LoadBitmaps(IDB_LOGIN_DISPLAY,IDB_LOGIN_SEL,IDB_LOGIN_FOCUS);
	m_bLogIn.SizeToContent();
	m_bCancel.LoadBitmaps(IDB_CANCEL_DISPLAY,IDB_CANCEL_SEL,IDB_CANCEL_FOCUS);
	m_bCancel.SizeToContent();

	//����ͼ���б�
	m_imageList.Create(32, 32, ILC_COLOR16, 4, 4);
	for(int i = 0; i < 10; i++)
	{
		m_imageList.Add(::LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1+i)));
	}
	
	m_ComboBoxPhotoImg.SetImageList(&m_imageList); //Ϊ�б������ͼ���б�
	int numImgInList = m_imageList.GetImageCount();
	for(int i=0; i<numImgInList; i++)
	{
		COMBOBOXEXITEM cbi ={0};
		cbi.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_OVERLAY |
			CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

		cbi.iItem = i;
		CString str;
		str.Format(_T("Numb %2d"), i+1);
		cbi.pszText = /*(LPTSTR)(LPCTSTR)*/str.GetBuffer();
		cbi.cchTextMax = str.GetLength();
		cbi.iImage = i;
		cbi.iSelectedImage = i;
		cbi.iOverlay = 2;
		cbi.iIndent = 0;
		int nItem = m_ComboBoxPhotoImg.InsertItem(&cbi);		//Ϊ��Ͽ��������Ŀ
		ASSERT(nItem == i);
	}

	
	m_ComboBoxPhotoImg.SetCurSel(0);

	m_brBack.DeleteObject();
	m_bmBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_BKLOG);
	m_brBack.CreatePatternBrush(&m_bmBack);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLogDlg::OnOK()
{
	UpdateData(TRUE);
	m_imgNum = m_ComboBoxPhotoImg.GetCurSel();
	m_IpAddrCtrl.GetWindowText(m_IpAddrS,32);

	CDialog::OnOK();
}
