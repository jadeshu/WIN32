
// MsgSer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMsgSerApp:
// �йش����ʵ�֣������ MsgSer.cpp
//

class CMsgSerApp : public CWinAppEx
{
public:
	CMsgSerApp();

// ��д
	public:
	virtual BOOL InitInstance();
};

extern CMsgSerApp theApp;