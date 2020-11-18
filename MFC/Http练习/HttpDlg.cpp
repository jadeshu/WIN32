
// HttpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Http.h"
#include "HttpDlg.h"
#include "afxdialogex.h"
#include "DengLuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHttpDlg �Ի���
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

// CHttpDlg ��Ϣ�������
BOOL CHttpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHttpDlg::OnPaint()
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

HCURSOR CHttpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "CWinHttpRequest.h"
void CHttpDlg::OnBnClickedButton1()
{
	//��ʼ��COM���
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
