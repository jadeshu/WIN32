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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	AfxMessageBox(_T("��ť�ؼ��Ҽ���Ϣ"));
	CButton::OnRButtonDown(nFlags, point);
}
