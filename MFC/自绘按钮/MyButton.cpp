#include "stdafx.h"
#include "MyButton.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
}
BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


void CMyButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	AfxMessageBox(_T("按钮控件右键消息"));
	CButton::OnRButtonDown(nFlags, point);
}
