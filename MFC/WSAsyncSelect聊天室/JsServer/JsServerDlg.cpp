
// JsServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JsServer.h"
#include "JsServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CJsServerDlg �Ի���




CJsServerDlg::CJsServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJsServerDlg::IDD, pParent)
{
	m_Port = _T("6666");
	m_editRecv = _T("");
	m_editSend = _T("");
	m_Log = _T("");

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJsServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IP);
	DDX_Text(pDX, IDC_EDIT_LOG, m_Log);
	DDX_Text(pDX, IDC_EDIT_SEND, m_editSend);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_editRecv);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
}

BEGIN_MESSAGE_MAP(CJsServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CJsServerDlg::OnBnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CJsServerDlg::OnBnClickedButtonSend)
	ON_MESSAGE(WM_SOCKET_LOG, &CJsServerDlg::OnLogMsg)
	ON_MESSAGE(WM_SOCKET_RECEIVE, &CJsServerDlg::OnRecvMsg)
END_MESSAGE_MAP()


// CJsServerDlg ��Ϣ�������

BOOL CJsServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_IP.SetWindowText(_T("127.0.0.1"));
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CJsServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJsServerDlg::OnPaint()
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
HCURSOR CJsServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CJsServerDlg::WriteLog(CString log)
{
	m_Log += log;
	m_Log += _T("\r\n");
	UpdateData(FALSE);
}

void CJsServerDlg::OnBnClickedButtonListen()
{
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);

	pSocketServer = new CSocketServer;

	UpdateData(TRUE);
	pSocketServer->m_hMsgWnd = this->GetSafeHwnd();

	if (pSocketServer->Create(_ttoi(m_Port), SOCK_STREAM, FD_ACCEPT|FD_CLOSE))
		WriteLog(_T("����������SOCKET�ɹ�"));
	else WriteLog(_T("����������SOCKETʧ��"));

	if (pSocketServer->Listen())
		WriteLog(_T("�����������ɹ�"));
	else WriteLog(_T("����������ʧ��"));
}

void CJsServerDlg::OnBnClickedButtonSend()
{
	if (pSocketServer == NULL) 
	{
		WriteLog(_T("SOCKETû�г�ʼ��"));
		return;
	}
	if (pSocketServer->m_clientList.GetCount() <= 0)
	{
		WriteLog(_T("û�пͻ���SOCKET"));
		return;
	}
	UpdateData(TRUE);
	int iLen = m_editSend.GetLength();
	BYTE* s= new BYTE[iLen];
	memset(s, 0x00, iLen);
	memcpy(s, (LPCTSTR)m_editSend, iLen);	

	int iCount = pSocketServer->m_clientList.GetCount();
	for (int i = 0;i <iCount;i ++)
	{
		POSITION pos = pSocketServer->m_clientList.FindIndex(i);
		CSocketClient* pClient = (CSocketClient*)pSocketServer->m_clientList.GetAt(pos);
		if (pClient != NULL)	pClient->Send((unsigned char*)s, iLen);
	}

	WriteLog(_T("���������С�����������"));
}

// ������Ϣ֪ͨ
LRESULT CJsServerDlg::OnRecvMsg(WPARAM dwEvent, LPARAM dwLen)
{
	if(!dwLen)	return 1;
	BYTE* temp = new BYTE[dwLen+1];
	memset(temp, 0x00, dwLen+1);
	memcpy(temp, (const void*)dwEvent, dwLen);
	CString log; 
	log.Format(_T("���յ��ͻ�������=%s\r\n"), (LPCTSTR)temp);

	if (m_editRecv.GetLength() > 50000)	m_editRecv = "";
	m_editRecv += log;	
	UpdateData(FALSE);
	return 1;
}

// ���յ���־
LRESULT CJsServerDlg::OnLogMsg(WPARAM dwEvent, LPARAM dwLen)
{
	if(!dwLen)	return 1;
	BYTE* temp = new BYTE[dwLen+1];
	memset(temp, 0x00, dwLen+1);
	memcpy(temp, (const void*)dwEvent, dwLen);
	WriteLog((LPCTSTR)temp);
	return 1;
}