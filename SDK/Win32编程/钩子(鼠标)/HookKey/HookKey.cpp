#include <windows.h>
#include <tchar.h>

TCHAR wndClassName[] = _T("HOOKKEY");
LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK  HookKeyPROC(int code, WPARAM wParam, LPARAM lParam);
HHOOK hookKey;
HWND hgWnd;
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
				   _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	WNDCLASS wndClass = {sizeof(wndClass)};
	wndClass.lpfnWndProc = wndProc;
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = wndClassName;
	wndClass.style = CS_HREDRAW| CS_VREDRAW;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDI_APPLICATION));

	int nRet  = RegisterClass(&wndClass);
	if (!nRet)
	{
		MessageBox(NULL,_T("注册窗口失败！"),_T("提示"),MB_OKCANCEL);
	}

	HWND hWnd = CreateWindow(wndClassName,_T("HOOK—KEY测试"),WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,800,600,NULL,NULL,hInstance,nullptr);
	if (!hWnd)
	{
		MessageBox(NULL,_T("窗口窗口失败！"),_T("提示"),MB_OKCANCEL);
	}
	hgWnd = hWnd;

	ShowWindow(hWnd,SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	hookKey = SetWindowsHookEx(WH_MOUSE_LL,HookKeyPROC,hInstance,0);
	MSG msg = {0};
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hookKey);
	UnregisterClass(wndClassName,hInstance);
	return msg.wParam;

}

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}

LRESULT CALLBACK  HookKeyPROC(int code, WPARAM wParam, LPARAM lParam)
{
	LPMSLLHOOKSTRUCT pMsll = (LPMSLLHOOKSTRUCT)lParam;
	POINT pt = pMsll->pt;
	DWORD   mouseData = pMsll->mouseData;
	const TCHAR *info = nullptr;
	TCHAR text[60], pData[50], mData[50];
	if (code >= 0)
	{
		if   (wParam == WM_MOUSEMOVE)       info = _T("鼠标移动　　　　");
		else if(wParam == WM_LBUTTONDOWN)   info = _T("鼠标【左键】按下");
		else if(wParam == WM_LBUTTONUP)     info = _T("鼠标【左键】抬起");
		else if(wParam == WM_LBUTTONDBLCLK) info = _T("鼠标【左键】双击");
		else if(wParam == WM_RBUTTONDOWN)   info = _T("鼠标【右键】按下");
		else if(wParam == WM_RBUTTONUP)     info = _T("鼠标【右键】抬起");
		else if(wParam == WM_RBUTTONDBLCLK) info = _T("鼠标【右键】双击");
		else if(wParam == WM_MBUTTONDOWN)   info = _T("鼠标【滚轮】按下");
		else if(wParam == WM_MBUTTONUP)     info = _T("鼠标【滚轮】抬起");
		else if(wParam == WM_MBUTTONDBLCLK) info = _T("鼠标【滚轮】双击");
		else if(wParam == WM_MOUSEWHEEL)    info = _T("鼠标【滚轮】滚动");

		ZeroMemory(text, sizeof(text));
		ZeroMemory(pData, sizeof(pData));
		ZeroMemory(mData, sizeof(mData));

		wsprintf(text,_T("当前状态：%10s"),info);
		wsprintf(pData,_T("0x%x - X: [%04d], Y: [%04d]"),wParam,pt.x,pt.y);
		wsprintf(mData,_T("附带数据： %16u"),mouseData);

		HDC hdc = GetDC(hgWnd);         
		TextOut(hdc, 10, 10,  text, _tcslen(text));
		TextOut(hdc, 10, 30, pData, _tcslen(pData));
		TextOut(hdc, 10, 50, mData, _tcslen(mData));
		ReleaseDC(hgWnd,hdc);
	}


	return CallNextHookEx(hookKey,code,wParam,lParam);
}