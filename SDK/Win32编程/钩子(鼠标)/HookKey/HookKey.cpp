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
		MessageBox(NULL,_T("ע�ᴰ��ʧ�ܣ�"),_T("��ʾ"),MB_OKCANCEL);
	}

	HWND hWnd = CreateWindow(wndClassName,_T("HOOK��KEY����"),WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,800,600,NULL,NULL,hInstance,nullptr);
	if (!hWnd)
	{
		MessageBox(NULL,_T("���ڴ���ʧ�ܣ�"),_T("��ʾ"),MB_OKCANCEL);
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
		if   (wParam == WM_MOUSEMOVE)       info = _T("����ƶ���������");
		else if(wParam == WM_LBUTTONDOWN)   info = _T("��꡾���������");
		else if(wParam == WM_LBUTTONUP)     info = _T("��꡾�����̧��");
		else if(wParam == WM_LBUTTONDBLCLK) info = _T("��꡾�����˫��");
		else if(wParam == WM_RBUTTONDOWN)   info = _T("��꡾�Ҽ�������");
		else if(wParam == WM_RBUTTONUP)     info = _T("��꡾�Ҽ���̧��");
		else if(wParam == WM_RBUTTONDBLCLK) info = _T("��꡾�Ҽ���˫��");
		else if(wParam == WM_MBUTTONDOWN)   info = _T("��꡾���֡�����");
		else if(wParam == WM_MBUTTONUP)     info = _T("��꡾���֡�̧��");
		else if(wParam == WM_MBUTTONDBLCLK) info = _T("��꡾���֡�˫��");
		else if(wParam == WM_MOUSEWHEEL)    info = _T("��꡾���֡�����");

		ZeroMemory(text, sizeof(text));
		ZeroMemory(pData, sizeof(pData));
		ZeroMemory(mData, sizeof(mData));

		wsprintf(text,_T("��ǰ״̬��%10s"),info);
		wsprintf(pData,_T("0x%x - X: [%04d], Y: [%04d]"),wParam,pt.x,pt.y);
		wsprintf(mData,_T("�������ݣ� %16u"),mouseData);

		HDC hdc = GetDC(hgWnd);         
		TextOut(hdc, 10, 10,  text, _tcslen(text));
		TextOut(hdc, 10, 30, pData, _tcslen(pData));
		TextOut(hdc, 10, 50, mData, _tcslen(mData));
		ReleaseDC(hgWnd,hdc);
	}


	return CallNextHookEx(hookKey,code,wParam,lParam);
}