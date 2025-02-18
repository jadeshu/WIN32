
// ThreadMsgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ThreadMsg.h"
#include "ThreadMsgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CThreadMsgDlg 对话框



CThreadMsgDlg::CThreadMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THREADMSG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadMsgDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE_THREAD_BTN, &CThreadMsgDlg::OnBnClickedCreateThreadBtn)
END_MESSAGE_MAP()


// CThreadMsgDlg 消息处理程序

BOOL CThreadMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CThreadMsgDlg::OnPaint()
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
HCURSOR CThreadMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int g_num = 100; // 1全局变量共享线程间

UINT  th1(LPVOID)
{
	while (TRUE)
	{
		g_num++;
		Sleep(4000);
	}
	return 0;
}

UINT  th2(LPVOID)
{
	while (TRUE)
	{
		CString msgStr;
		msgStr.Format(_T("%d\n"), g_num);
		OutputDebugString(msgStr);
		Sleep(2000);
	}
	return 0;
}
void CThreadMsgDlg::OnBnClickedCreateThreadBtn()
{
	AfxBeginThread(th1, 0);
	AfxBeginThread(th2, 0);
}
