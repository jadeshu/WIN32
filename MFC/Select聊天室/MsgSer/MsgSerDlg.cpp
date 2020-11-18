
// MsgSerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MsgSer.h"
#include "MsgSerDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMsgSerDlg 对话框
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


// CMsgSerDlg 消息处理程序

BOOL CMsgSerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//初始化套接字
	AfxSocketInit();

	//端口问题
	CString strPort;
	GetDlgItemText(IDC_PORT_EDT,strPort);
	if (!strPort.IsEmpty())
	{
		m_Port = _ttoi(strPort);
	}
	//禁言关闭按钮
	GetDlgItem(IDC_CLOSE_BTN)->EnableWindow(FALSE);
	//设置listctrl控件
	setListCtlStyle();

	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMsgSerDlg::OnPaint()
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
HCURSOR CMsgSerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMsgSerDlg::OnBnClickedCloseBtn()
{
	//禁言关闭按钮
	GetDlgItem(IDC_CLOSE_BTN)->EnableWindow(FALSE);
	//启用开始按钮
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	KillTimer(1);
}

void CMsgSerDlg::OnBnClickedStartBtn()
{
	struct sockaddr_in serverAddr;			//保存服务端的信息
	int nSerAddrLen = sizeof(sockaddr_in);	//保存服务端信息字节数
	memset(&serverAddr, 0, nSerAddrLen);		//填充数据为0

	serverAddr.sin_family = AF_INET;			//家族网络族
	serverAddr.sin_port = htons(6000);			//端口
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY)/*inet_addr("127.0.0.1")*/;	//IP
	m_SocketSer.Bind(&serverAddr,nSerAddrLen);

	m_SocketSer.Listen();
	::CreateThread(NULL,0,ThrProc,(void*)this,0,0);

	SetTimer(1,500,NULL);

	//启用关闭按钮
	GetDlgItem(IDC_CLOSE_BTN)->EnableWindow(TRUE);
	//禁言开启按钮
	GetDlgItem(IDC_START_BTN)->EnableWindow(FALSE);
}

void CMsgSerDlg::setListCtlStyle()
{
	m_listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_INFOTIP|LVS_EX_FULLROWSELECT);
	m_listCtrl.InsertColumn(1,_T("用户名"),LVCFMT_CENTER,200,0);
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
			int nRow = m_listCtrl.InsertItem(i, iName);//插入行
			m_listCtrl.SetItemText(nRow, 1,it->userIP);//设置数据	
		}
		iNum = m_SocketSer.m_UserNum;
	}

	CDialog::OnTimer(nIDEvent);
}
