
// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#include "LogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientDlg �Ի���



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
	, m_bCheckBtn(FALSE)
	, m_Ctx(_T(""))
	, m_Say(_T(""))
{
	m_curNum = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bCheckBtn);
	DDX_Text(pDX, IDC_CTX, m_Ctx);
	DDX_Text(pDX, IDC_SAY, m_Say);
	DDX_Control(pDX, IDC_User_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(SOCKET_EVENT,&CClientDlg::OnSocket)
	ON_BN_CLICKED(IDC_SEND, &CClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
        
	//AfxSocketInit();

	m_brBack.DeleteObject();
	m_bmBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_CLIENT_BK);
	m_brBack.CreatePatternBrush(&m_bmBack);

	m_bSend.AutoLoad(IDC_SEND,this);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	tryagain:
	CLogDlg dlg;
	if (dlg.DoModal()!=IDOK)
	{
		PostQuitMessage(0);
		return TRUE;
	}
	if (_tcslen(dlg.m_IpAddrS)==0)
	{
		MessageBox(_T("�������������ַ��"));
		goto tryagain;
	}
	//�û���Ϊ��
	if (dlg.m_UserName.IsEmpty())
	{
		MessageBox(_T("�������������"));
		goto tryagain;
	}
	m_UserName = dlg.m_UserName;
	

	//�׽��ֳ�ʼ��������
	m_Socket.AttachCWnd(this);

	CString msgStr;	//��Ϣ����Ϣ
	if(m_Socket.Create()==FALSE)
	{
		DWORD dwRetErro = GetLastError();
		msgStr.Format(_T("����Socketʧ�ܣ�\r\n������룺%d"),dwRetErro);
		goto msgBox;
	}
	SetWindowText(_T("�������ӷ�����"));

	//���ӷ�������������˿�Ϊ0x8123�ĳ���
	if (m_Socket.Connect(dlg.m_IpAddrS,0x8123)==FALSE)
	{
		DWORD dwRetErro = GetLastError();
		msgStr.Format(_T("���ӷ�����ʧ�ܣ�\r\n������룺%d"),dwRetErro);
msgBox:
		//�˳�
		MessageBox(msgStr);
		PostQuitMessage(0);
		return TRUE;			
	}

	//CString pktStr;
	//pktStr.Format(_T("%s�Ѿ����ӷ�������"),m_UserName);
	//SetWindowText(pktStr);
	TCHAR pkt[200];
	_stprintf_s(pkt,_T("%s�Ѿ����ӷ�������"),m_UserName);
	SetWindowText(pkt);

	pkt[0] = 0x11;
	TCHAR imgIndexS = dlg.m_imgNum+sizeof(TCHAR);
	pkt[1] = imgIndexS;
	_tcsncpy_s(pkt+2,100,m_UserName,64);
	int iLength = _tcslen(pkt)+sizeof(TCHAR);
	if (m_Socket.Send(pkt,iLength) == FALSE)
	{
		MessageBox(_T("�������ݴ���"));
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_DLG)
		return m_brBack;
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CClientDlg::OnBnClickedSend()
{
	TCHAR pkt[4096];
	UpdateData();
	memset(pkt,0,4096);
	int	len = 0;
	if (m_bCheckBtn)	//˽��
	{
		pkt[0] = 0x51;	//˽��ָ��
		_tcscpy_s(pkt+sizeof(TCHAR),100,m_pName[m_curIndex]);
		len = _stprintf_s(pkt + 100,1000 ,_T("%s ���ĵĶ���˵��%s\r\n"),m_UserName,m_Say);
		m_Socket.Send(pkt,len + 100);


		_stprintf_s(pkt + 100 ,1000 ,_T(" �����ĵĶ�%s˵��%s\r\n"),m_pName[m_curIndex],m_Say);
		m_Ctx += pkt +100;
		m_Say.Empty();
	}
	else
	{
		pkt[0] = 0x21;										//���빦����0x21
		len = _stprintf_s(pkt+sizeof(TCHAR),1000,_T("%s˵: %s\r\n"),m_UserName,m_Say);	//len�ǳ���
		m_Socket.Send(pkt,len + 3);							//�ַ��������β���෢������

		m_Say.Empty();		
	}
	UpdateData(FALSE);
}

LRESULT CClientDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	TCHAR	pkt[4096];
	memset(pkt,0,4096);
	CEdit	*pEd = (CEdit*)GetDlgItem(IDC_CTX);				//�õ��༭�����Ŀ���ָ��
	LVFINDINFO   info;
	LVITEM lvitem; 
	switch(lParam)
	{
	case RETR:
		{
			m_Socket.Receive(pkt,4096);
			if(m_Ctx.GetLength() > 8196)
				m_Ctx.Empty();
			//���Թ�����

			switch(pkt[0])
			{
			case 0x11:					//�û�������Ϣ
				m_pName[m_curNum] = pkt +2;
				m_curNum++;
				m_Ctx += pkt + 2;
				m_Ctx += _T(" �������ҡ�\r\n");

				lvitem.mask = LVIF_IMAGE|LVIF_TEXT; 
				lvitem.iItem = m_curNum; 
				lvitem.pszText = pkt + 2; 
				lvitem.iImage = pkt[1] - 1; 
				lvitem.iSubItem = 0; 
				m_List.InsertItem(&lvitem);

				break;

			case 0x31:					//�����û���Ϣ
				m_pName[m_curNum] = pkt +2;
				m_curNum++;
				lvitem.mask = LVIF_IMAGE|LVIF_TEXT; 
				lvitem.iItem = m_curNum; 
				lvitem.pszText = pkt + 2; 
				lvitem.iImage = pkt[1] - 0x31; 
				lvitem.iSubItem = 0; 
				m_List.InsertItem(&lvitem); 

				break;
			case 0x41:					//�û��뿪��������Ϣ

				m_Ctx += pkt + 1;
				m_Ctx += _T(" �˳����ҡ�\r\n");
				info.flags = LVFI_PARTIAL|LVFI_STRING;  
				info.psz   = pkt + 1;
				int item;
				item = m_List.FindItem(&info);
				if(item != -1)
				{
					m_List.DeleteItem(item);
				}
				break;
			default:

				m_Ctx += pkt + 1;
			}

			pEd->LineScroll(1000); 
			UpdateData(false);
			break;
		}		

	case CLOSE:
		MessageBox(_T("�������ѹر�!"));
		break;
	}
	return 0;
}