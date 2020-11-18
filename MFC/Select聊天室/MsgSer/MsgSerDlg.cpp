
// MsgSerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MsgSer.h"
#include "MsgSerDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMsgSerDlg �Ի���
CMsgSerDlg::CMsgSerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgSerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Port = 6000;
}

void CMsgSerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_listCtrl);
}

DWORD WINAPI ThrProc(LPVOID lpParameter)
{
	CMsgSerDlg* pThis = (CMsgSerDlg*)lpParameter;
	struct timeval tv = {0};
	tv.tv_sec = 2;
	(pThis->m_SocketSer).Select(&(pThis->m_SocketSer.m_ReadSet),&tv);
	return 0;
}

BEGIN_MESSAGE_MAP(CMsgSerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CMsgSerDlg::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_START_BTN, &CMsgSerDlg::OnBnClickedStartBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMsgSerDlg ��Ϣ�������

BOOL CMsgSerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//��ʼ���׽���
	AfxSocketInit();

	//�˿�����
	CString strPort;
	GetDlgItemText(IDC_PORT_EDT,strPort);
	if (!strPort.IsEmpty())
	{
		m_Port = _ttoi(strPort);
	}
	//���Թرհ�ť
	GetDlgItem(IDC_CLOSE_BTN)->EnableWindow(FALSE);
	//����listctrl�ؼ�
	setListCtlStyle();

	
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMsgSerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMsgSerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMsgSerDlg::OnBnClickedCloseBtn()
{
	//���Թرհ�ť
	GetDlgItem(IDC_CLOSE_BTN)->EnableWindow(FALSE);
	//���ÿ�ʼ��ť
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	KillTimer(1);
}

void CMsgSerDlg::OnBnClickedStartBtn()
{
	struct sockaddr_in serverAddr;			//�������˵���Ϣ
	int nSerAddrLen = sizeof(sockaddr_in);	//����������Ϣ�ֽ���
	memset(&serverAddr, 0, nSerAddrLen);		//�������Ϊ0

	serverAddr.sin_family = AF_INET;			//����������
	serverAddr.sin_port = htons(6000);			//�˿�
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY)/*inet_addr("127.0.0.1")*/;	//IP
	m_SocketSer.Bind(&serverAddr,nSerAddrLen);

	m_SocketSer.Listen();
	::CreateThread(NULL,0,ThrProc,(void*)this,0,0);

	SetTimer(1,500,NULL);

	//���ùرհ�ť
	GetDlgItem(IDC_CLOSE_BTN)->EnableWindow(TRUE);
	//���Կ�����ť
	GetDlgItem(IDC_START_BTN)->EnableWindow(FALSE);
}

void CMsgSerDlg::setListCtlStyle()
{
	m_listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_INFOTIP|LVS_EX_FULLROWSELECT);
	m_listCtrl.InsertColumn(1,_T("�û���"),LVCFMT_CENTER,200,0);
	m_listCtrl.InsertColumn(2,_T("IP"),LVCFMT_CENTER,230,1);
}

void CMsgSerDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int iNum = 0;
	if (iNum < m_SocketSer.m_UserNum)
	{
		m_listCtrl.DeleteAllItems();
		list<stUser> m = m_SocketSer.m_UserList;
		int i=0;
		for (list<stUser>::iterator it= m.begin(); it != m.end(); ++it,i++)
		{
			char iName[10]={0};
			itoa((int)(it->userSocket),iName,10);
			int nRow = m_listCtrl.InsertItem(i, iName);//������
			m_listCtrl.SetItemText(nRow, 1,it->userIP);//��������	
		}
		iNum = m_SocketSer.m_UserNum;
	}

	CDialog::OnTimer(nIDEvent);
}
