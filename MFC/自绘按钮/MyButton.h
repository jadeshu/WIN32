#pragma once
#include "afxwin.h"
class CMyButton :public CButton
{
public:
	CMyButton();
	~CMyButton();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

