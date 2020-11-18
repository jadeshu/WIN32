
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#include "LogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientDlg 对话框



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


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
        
	//AfxSocketInit();

	m_brBack.DeleteObject();
	m_bmBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_CLIENT_BK);
	m_brBack.CreatePatternBrush(&m_bmBack);

	m_bSend.AutoLoad(IDC_SEND,this);

	// TODO: 在此添加额外的初始化代码
	tryagain:
	CLogDlg dlg;
	if (dlg.DoModal()!=IDOK)
	{
		PostQuitMessage(0);
		return TRUE;
	}
	if (_tcslen(dlg.m_IpAddrS)==0)
	{
		MessageBox(_T("请输入服务器地址！"));
		goto tryagain;
	}
	//用户名为空
	if (dlg.m_UserName.IsEmpty())
	{
		MessageBox(_T("请输入你的名字"));
		goto tryagain;
	}
	m_UserName = dlg.m_UserName;
	

	//套接字初始化和设置
	m_Socket.AttachCWnd(this);

	CString msgStr;	//消息框消息
	if(m_Socket.Create()==FALSE)
	{
		DWORD dwRetErro = GetLastError();
		msgStr.Format(_T("创建Socket失败！\r\n错误代码：%d"),dwRetErro);
		goto msgBox;
	}
	SetWindowText(_T("正在连接服务器"));

	//连接服务器计算机，端口为0x8123的程序
	if (m_Socket.Connect(dlg.m_IpAddrS,0x8123)==FALSE)
	{
		DWORD dwRetErro = GetLastError();
		msgStr.Format(_T("连接服务器失败！\r\n错误代码：%d"),dwRetErro);
msgBox:
		//退出
		MessageBox(msgStr);
		PostQuitMessage(0);
		return TRUE;			
	}

	//CString pktStr;
	//pktStr.Format(_T("%s已经连接服务器！"),m_UserName);
	//SetWindowText(pktStr);
	TCHAR pkt[200];
	_stprintf_s(pkt,_T("%s已经连接服务器！"),m_UserName);
	SetWindowText(pkt);

	pkt[0] = 0x11;
	TCHAR imgIndexS = dlg.m_imgNum+sizeof(TCHAR);
	pkt[1] = imgIndexS;
	_tcsncpy_s(pkt+2,100,m_UserName,64);
	int iLength = _tcslen(pkt)+sizeof(TCHAR);
	if (m_Socket.Send(pkt,iLength) == FALSE)
	{
		MessageBox(_T("发送数据错误！"));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_DLG)
		return m_brBack;
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CClientDlg::OnBnClickedSend()
{
	TCHAR pkt[4096];
	UpdateData();
	memset(pkt,0,4096);
	int	len = 0;
	if (m_bCheckBtn)	//私聊
	{
		pkt[0] = 0x51;	//私聊指令
		_tcscpy_s(pkt+sizeof(TCHAR),100,m_pName[m_curIndex]);
		len = _stprintf_s(pkt + 100,1000 ,_T("%s 悄悄的对你说：%s\r\n"),m_UserName,m_Say);
		m_Socket.Send(pkt,len + 100);


		_stprintf_s(pkt + 100 ,1000 ,_T(" 你悄悄的对%s说：%s\r\n"),m_pName[m_curIndex],m_Say);
		m_Ctx += pkt +100;
		m_Say.Empty();
	}
	else
	{
		pkt[0] = 0x21;										//填入功能码0x21
		len = _stprintf_s(pkt+sizeof(TCHAR),1000,_T("%s说: %s\r\n"),m_UserName,m_Say);	//len是长度
		m_Socket.Send(pkt,len + 3);							//字符串以零结尾。多发两个零

		m_Say.Empty();		
	}
	UpdateData(FALSE);
}

LRESULT CClientDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	TCHAR	pkt[4096];
	memset(pkt,0,4096);
	CEdit	*pEd = (CEdit*)GetDlgItem(IDC_CTX);				//得到编辑框对象的控制指针
	LVFINDINFO   info;
	LVITEM lvitem; 
	switch(lParam)
	{
	case RETR:
		{
			m_Socket.Receive(pkt,4096);
			if(m_Ctx.GetLength() > 8196)
				m_Ctx.Empty();
			//忽略功能码

			switch(pkt[0])
			{
			case 0x11:					//用户进入信息
				m_pName[m_curNum] = pkt +2;
				m_curNum++;
				m_Ctx += pkt + 2;
				m_Ctx += _T(" 进入聊室。\r\n");

				lvitem.mask = LVIF_IMAGE|LVIF_TEXT; 
				lvitem.iItem = m_curNum; 
				lvitem.pszText = pkt + 2; 
				lvitem.iImage = pkt[1] - 1; 
				lvitem.iSubItem = 0; 
				m_List.InsertItem(&lvitem);

				break;

			case 0x31:					//在线用户信息
				m_pName[m_curNum] = pkt +2;
				m_curNum++;
				lvitem.mask = LVIF_IMAGE|LVIF_TEXT; 
				lvitem.iItem = m_curNum; 
				lvitem.pszText = pkt + 2; 
				lvitem.iImage = pkt[1] - 0x31; 
				lvitem.iSubItem = 0; 
				m_List.InsertItem(&lvitem); 

				break;
			case 0x41:					//用户离开聊天室信息

				m_Ctx += pkt + 1;
				m_Ctx += _T(" 退出聊室。\r\n");
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
		MessageBox(_T("服务器已关闭!"));
		break;
	}
	return 0;
}