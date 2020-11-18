// DengLuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Http.h"
#include "DengLuDlg.h"
#include "afxdialogex.h"


// CDengLuDlg 对话框

IMPLEMENT_DYNAMIC(CDengLuDlg, CDialog)

CDengLuDlg::CDengLuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDengLuDlg::IDD, pParent)
{

}

CDengLuDlg::~CDengLuDlg()
{
}

void CDengLuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT1, m_userName);
	//DDX_Control(pDX, IDC_EDIT2, m_PassWord);
}


BEGIN_MESSAGE_MAP(CDengLuDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDengLuDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDengLuDlg 消息处理程序

#import "c:\\Windows\\System32\\WinHttp.dll" no_namespace
void CDengLuDlg::OnBnClickedButton1()
{
	CString userName,passWord;
	GetDlgItemText(IDC_EDIT1,userName);
	GetDlgItemText(IDC_EDIT2,passWord);
	if (passWord.IsEmpty() || userName.IsEmpty())
	{
		MessageBox(_T("密码账号不能为空！"));
		return;
	}
	IWinHttpRequestPtr pHttpReq = nullptr;
	HRESULT hr = pHttpReq.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr)) return ;

	hr = pHttpReq->Open(_T("POST"),_T("http://www.tuidc.com/user/userlogin1.asp"));
	if (FAILED(hr)) return ;

	CString strBoby;
	strBoby.Format(_T("username=%s&password=%s"),userName,passWord);
	COleVariant varBoby = strBoby;
	
	pHttpReq->SetRequestHeader(_T("Content-Type"),_T("application/x-www-form-urlencoded"));
	hr = pHttpReq->Send(varBoby);
	if (FAILED(hr)) return ;

	_bstr_t bstrRsp = pHttpReq->ResponseText;
	CString strRsp = bstrRsp;
	MessageBox(strRsp);
	

}