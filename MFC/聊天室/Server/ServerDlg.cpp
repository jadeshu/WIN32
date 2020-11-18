
// ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg 对话框



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
	, m_Ctx(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYER_LIST, m_List);
	DDX_Text(pDX, IDC_CTX, m_Ctx);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CServerDlg::OnBnClickedExitBtn)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(SOCKET_EVENT,&CServerDlg::OnSocket)
END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//AfxSocketInit();

	// TODO: 在此添加额外的初始化代码
	m_List.InsertColumn(0,_T("称谓"),LVCFMT_LEFT,120);		//第一列表头
	m_List.InsertColumn(1,_T("IP"),LVCFMT_LEFT,100);		//第二列表头
	m_List.InsertColumn(2,_T("消息数"),LVCFMT_LEFT,60);		//第三列表头
	m_List.InsertColumn(3,_T("头像"),LVCFMT_LEFT,60);		//第四列表头

	m_socket.AttachCWnd(this);							//将Socket绑定到本窗
	m_socket.Create(0x8123,SOCK_STREAM);				//SOCK_STREAM表示TCP连接
	m_socket.Listen();									//等待连接

	m_brBack.DeleteObject();
	m_bmBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_BKSERVER);
	m_brBack.CreatePatternBrush(&m_bmBack);

	 m_bExit.AutoLoad(IDC_EXIT,this);
	 m_bExit.SizeToContent();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::OnBnClickedExitBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}

void CServerDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CServerDlg::OnOK() 
{
	//	CDialog::OnOK();
}

HBRUSH CServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor == CTLCOLOR_DLG)
		return m_brBack;
	return hbr;
}

LRESULT CServerDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	CMySocket *socketFrom = (CMySocket*)wParam;
	//解析协议
	switch (lParam)	
	{
	case ACCEPT:
		{
			CMySocket *pSocketClient = new CMySocket();
			pSocketClient->AttachCWnd(this);
			SOCKADDR_IN sockAddr;
			int nSize = sizeof(sockAddr);
			BOOL res = socketFrom->Accept(*pSocketClient,(SOCKADDR*)&sockAddr,&nSize);
			if (res==FALSE)
			{
				MessageBox(_T("接收客户端失败！"));
			}
			break;
		}
	case CLOSE:
		{
			ClosePlayer(socketFrom);
			break;
		}
	case RETR:
		{
			ParserPkt(socketFrom);
			break;
		}
	}

	return TRUE;
}

void CServerDlg::ClosePlayer(CMySocket* socketFrom)
{
	int		i,msg_len;
	TCHAR	out_msg[200];
	TCHAR	nbuf[100];
	nbuf[0] = 0x41;									//用户退出的命令号
	msg_len = _stprintf_s(out_msg,_T(" %s 退出聊天室\r\n"),socketFrom->m_Player) + sizeof(TCHAR);

	m_criticalSection.Lock();
	for(i = 0; i < m_List.GetItemCount(); i++)		//删除退出用户的信息
	{
		if(m_List.GetItemData(i) == (DWORD)socketFrom)
		{
			delete socketFrom;							//删除套接字
			m_List.GetItemText(i,0,nbuf + 1, 90);	 
			m_List.DeleteItem(i);					//删除退出用户在列表中的信息
			break;
		}
	}

	for(i = 0; i < m_List.GetItemCount(); i++)		//将用户退出消息发送给各个用户
	{
		CMySocket *s;

		s = (CMySocket*)m_List.GetItemData(i);
		s->Send(nbuf,90);							//发送消息
	}
	m_criticalSection.Unlock();

	Append(out_msg);
}

void CServerDlg::ParserPkt(CMySocket *socketFrom)
{
	TCHAR SendBuff[4096];		//发送缓冲
	TCHAR ShowBuff[4096];		//显示缓冲
	int len;					//记录发送长度
	int item;					//列表序号
	TCHAR pic[2];				//图像序号		
	CString ipaddr;				//IP字符串	
	UINT port;					//端口号
	CMySocket *s1;				//发送一般消息的Socket		
	CMySocket *s;				//发送用户进入信息的Socket
	TCHAR nbuf[100];				//临时缓冲区
	//初始化各缓冲区
	memset(SendBuff,0,4096);
	memset(ShowBuff,0,4096);
	memset(nbuf,0,100);

	len = socketFrom->Receive(SendBuff,4096);				//读取数据
	if(len < 1)												//读取失败
		return;

	if(SendBuff[0] == 0x11)									//新用户加入
	{
		socketFrom->GetPeerName(ipaddr,port);						//取得与该套接字链接的对方的IP地址、端口号


		socketFrom->m_Player = SendBuff + 2;						//与SOCKET通信的用户的称谓
		pic[0] = SendBuff[1] + 0x30;
		pic[1] = _T('\0');										//头像序号

		m_criticalSection.Lock();
		item = m_List.InsertItem(0,SendBuff+2);				//列表中插入一行，返回插入的行号
		m_List.SetItemData(item,(DWORD)socketFrom);				//保存该SOCKET指针到该行的附加数据域
		m_List.SetItemText(item,1,ipaddr);					//设置第2列，IP地址列
		m_List.SetItemText(item,3,pic);						//设置第3列，用户头像
		m_criticalSection.Unlock();

		len = _stprintf_s(ShowBuff ,_T(" %s 进入聊室。\r\n"),socketFrom->m_Player);

		s1 = (CMySocket*)m_List.GetItemData(item);
		m_criticalSection.Lock();
		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			s = (CMySocket*)m_List.GetItemData(item);		//取附加数据（SOCKET指针）
			s->Send(SendBuff,len);							//通知所有用户有新用户加入
			Sleep(200);
			if(s != socketFrom)	
			{	//发送新用户加入消息

				m_List.GetItemText(item,3,&pic[0],2);
				nbuf[0] = 0x31;
				nbuf[1] = pic[0];
				m_List.GetItemText(item,0,nbuf+2,100);
				len = _tcslen(nbuf);
				s1->Send(nbuf,14);
			}
			else
			{	//新用户消息加1
				TCHAR tot[10];

				_stprintf_s(tot,_T("%u"),socketFrom->m_Total);
				m_List.SetItemText(item,2,tot);				//设置第2列，消息数列
			}
		}
		m_criticalSection.Unlock();
	}
	else if(SendBuff[0] == 0x51)							//私聊信息
	{
		TCHAR pName[100],bName[100];
		memset(pName,0,100);
		memset(bName,0,100);
		_tcscpy_s(pName,SendBuff +sizeof(TCHAR));
		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			m_List.GetItemText(item,0,bName,100);
			if(0 == _tcscmp(pName,bName))
			{
				s = (CMySocket*)m_List.GetItemData(item);	//取附加数据（SOCKET指针）
				s->Send(SendBuff + 99 ,len);
			}
		}
		memcpy(ShowBuff,SendBuff+99,3996);
	}
	else													//公聊信息
	{
		m_criticalSection.Lock();
		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			s = (CMySocket*)m_List.GetItemData(item);		//取附加数据（SOCKET指针）
			s->Send(SendBuff,len);

			if(s == socketFrom)
			{
				TCHAR tot[10];

				_stprintf_s(tot,_T("%u"),socketFrom->m_Total);
				m_List.SetItemText(item,2,tot);				//设置第2列，消息数列
			}
		}
		m_criticalSection.Unlock();
	}
	Append(ShowBuff);
}

void CServerDlg::Append(TCHAR *msg)
{
	CEdit	*pEd = (CEdit*)GetDlgItem(IDC_CTX);		//读取消息框中所有 的消息

	if(m_Ctx.GetLength() > 8196)					//保存的消息过长
		m_Ctx.Empty();								//清空消息
	m_Ctx += msg;									//追加新消息
	UpdateData(FALSE);								//显示

	pEd->LineScroll(1000);
}