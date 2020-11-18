
// JsServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JsServer.h"
#include "JsServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CJsServerDlg 对话框




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


// CJsServerDlg 消息处理程序

BOOL CJsServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_IP.SetWindowText(_T("127.0.0.1"));
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJsServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
		WriteLog(_T("创建服务器SOCKET成功"));
	else WriteLog(_T("创建服务器SOCKET失败"));

	if (pSocketServer->Listen())
		WriteLog(_T("监听服务器成功"));
	else WriteLog(_T("监听服务器失败"));
}

void CJsServerDlg::OnBnClickedButtonSend()
{
	if (pSocketServer == NULL) 
	{
		WriteLog(_T("SOCKET没有初始化"));
		return;
	}
	if (pSocketServer->m_clientList.GetCount() <= 0)
	{
		WriteLog(_T("没有客户端SOCKET"));
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

	WriteLog(_T("发送数据中。。。。。。"));
}

// 接收消息通知
LRESULT CJsServerDlg::OnRecvMsg(WPARAM dwEvent, LPARAM dwLen)
{
	if(!dwLen)	return 1;
	BYTE* temp = new BYTE[dwLen+1];
	memset(temp, 0x00, dwLen+1);
	memcpy(temp, (const void*)dwEvent, dwLen);
	CString log; 
	log.Format(_T("接收到客户端数据=%s\r\n"), (LPCTSTR)temp);

	if (m_editRecv.GetLength() > 50000)	m_editRecv = "";
	m_editRecv += log;	
	UpdateData(FALSE);
	return 1;
}

// 接收到日志
LRESULT CJsServerDlg::OnLogMsg(WPARAM dwEvent, LPARAM dwLen)
{
	if(!dwLen)	return 1;
	BYTE* temp = new BYTE[dwLen+1];
	memset(temp, 0x00, dwLen+1);
	memcpy(temp, (const void*)dwEvent, dwLen);
	WriteLog((LPCTSTR)temp);
	return 1;
}