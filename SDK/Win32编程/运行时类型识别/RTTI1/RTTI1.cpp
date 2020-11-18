// RTTI1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "winappx.h"
#include "Wndx.h"


int _tmain(int argc, _TCHAR* argv[])
{

	CRuntimeClass pobJ = CObj::classCObj;
	CRuntimeClass pCMD = CCmd::classCCmd;
	CRuntimeClass pThread = CThread::classCThread;
	CRuntimeClass pApp = CWinAppx::classCWinAppx;
	CRuntimeClass pWndx = CWndx::classCWndx;
	CRuntimeClass *frist = CRuntimeClass::pFristClass;
	return 0;
}