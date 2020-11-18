
// HttpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Http.h"
#include "HttpDlg.h"
#include "afxdialogex.h"
#include "DengLuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHttpDlg 对话框
CHttpDlg::CHttpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHttpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHttpDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHttpDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHttpDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_DENGLU_BTN, &CHttpDlg::OnBnClickedDengluBtn)
END_MESSAGE_MAP()

// CHttpDlg 消息处理程序
BOOL CHttpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHttpDlg::OnPaint()
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

HCURSOR CHttpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "CWinHttpRequest.h"
void CHttpDlg::OnBnClickedButton1()
{
	//初始化COM组件
	::CoInitialize(nullptr);
	CWinHttpRequest *pHttpReq = new CWinHttpRequest();

	BOOL bret = pHttpReq->CreateDispatch(_T("WinHttp.WinHttpRequest.5.1")/*__uuidof(WinHttpRequest)*/);

	if (!bret)
	{
		return ;
	}

	COleVariant asyn =  VARIANT_FALSE;
	pHttpReq->Open(_T("GET"),_T("http://pan.baidu.com"),asyn);
	pHttpReq->Send(vtMissing);
	CString str = pHttpReq->get_ResponseText();
	MessageBox(str);
	pHttpReq->ReleaseDispatch();
	delete pHttpReq;
	::CoUninitialize();
}

#import "C:\\Windows\\System32\\winhttp.dll" no_namespace
void CHttpDlg::OnBnClickedButton2()
{
	::CoInitialize(nullptr);
	IWinHttpRequest *pHttpReq = nullptr;
	HRESULT hr = CoCreateInstance(__uuidof(WinHttpRequest),nullptr,CLSCTX_ALL,__uuidof(IWinHttpRequest),(LPVOID*)&pHttpReq);
	if (FAILED(hr))
	{
		::CoUninitialize();
		return ;
	}

	hr = pHttpReq->Open(_T("GET"),_T("https://mail.qq.com/cgi-bin/loginpage"));
	if (FAILED(hr))
	{
		pHttpReq->Release();
		::CoUninitialize();
		return ;
	}
	hr = pHttpReq->Send();
	if (FAILED(hr))
	{
		pHttpReq->Release();
		::CoUninitialize();
		return ;
	}

	CString strText = pHttpReq->ResponseText;
	MessageBox(strText);

	pHttpReq->Release();
	::CoUninitialize();
}

//#import "C:\\Windows\\System32\\winhttp.dll" no_namespace
void CHttpDlg::OnBnClickedButton3()
{
	::CoInitialize(nullptr);
	IWinHttpRequestPtr  pHttpReq = nullptr;
	HRESULT hr = pHttpReq.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))
	{
		::CoUninitialize();
		return ;
	}
	hr = pHttpReq->Open(_T("GET"),_T("https://mail.qq.com/cgi-bin/loginpage"));
	if (FAILED(hr))
	{
		//pHttpReq.Release();
		::CoUninitialize();
		return ;
	}
	hr = pHttpReq->Send();
	if (FAILED(hr))
	{
		//pHttpReq.Release();
		::CoUninitialize();
		return ;
	}

	CString strText = pHttpReq->ResponseText;
	MessageBox(strText);
	//pHttpReq.Release();

	::CoUninitialize();
}

void CHttpDlg::OnBnClickedDengluBtn()
{
	CDengLuDlg dlg;
	dlg.DoModal();
}
