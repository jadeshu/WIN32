#include <windows.h>
#include <tchar.h>
#include "Resource.h"

#define MDIClientName  L"MDICLIENT"
#define MDIClientChildName L"MDIChildName"
// ȫ�ֱ���:
HINSTANCE g_hInst;
TCHAR szTitle[20] = _T("MDI��ϰ");                  // �������ı�  
TCHAR szWindowClass[20] = _T("mdilx");            // ����������  

HWND g_hWndFrame;	//�����
HWND g_hWndClient;	//�ͻ���

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ChildWndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMO02));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= 0;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);
	wcex.lpfnWndProc = ChildWndProc;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszClassName = MDIClientChildName;
	RegisterClassEx(&wcex);

	g_hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	g_hWndFrame = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!g_hWndFrame)
	{
		return FALSE;
	}

	ShowWindow(g_hWndFrame, nCmdShow);
	UpdateWindow(g_hWndFrame);
	// ����Ϣѭ��:
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//�˴���ͬ
		//if (!TranslateMDISysAccel(g_hWndClient,&msg))
		//{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		//}		
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	CLIENTCREATESTRUCT clientStruct;
	switch (message)
	{
	case WM_CREATE:
		{
			clientStruct.hWindowMenu = 0;
			clientStruct.idFirstChild = 100;
			g_hWndClient = CreateWindowEx(0,MDIClientName,0,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,
				CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,hWnd,0,g_hInst,&clientStruct);
			CreateMDIWindow(MDIClientChildName,0,WS_OVERLAPPEDWINDOW,50,50,500,300,g_hWndClient,g_hInst,0);
			break;
		}
	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			switch(wmId)
			{
			case IDM_NEW:
				{
					CreateMDIWindow(MDIClientChildName,0,WS_OVERLAPPEDWINDOW,
						50,50,500,300,g_hWndClient,g_hInst,0);
					break;
				}
			case IDM_CLOSE:
				{
					HWND hClient = (HWND)SendMessage(g_hWndClient,WM_MDIGETACTIVE,0,0);
					SendMessage(hClient,WM_CLOSE,0,0);
					break;
				}
			case IDM_VER:
				{
					SendMessage(g_hWndClient,WM_MDITILE,MDITILE_VERTICAL,0);
					break;
				}
			case IDM_ZONGPAI:
				{
					SendMessage(g_hWndClient,WM_MDITILE,MDITILE_HORIZONTAL,0);
					break;
				}
			case IDM_SERETCH:
				{
					SendMessage(g_hWndClient,WM_MDICASCADE,MDITILE_SKIPDISABLED,0);
					break;
				}
			default:
				{
					DefFrameProc(hWnd, g_hWndClient,message, wParam, lParam);
					break;
				}			
			}
			// �����˵�ѡ��:
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefFrameProc(hWnd, g_hWndClient,message, wParam, lParam);	//�˴���ͬ
	}
	return 0;
}

LRESULT CALLBACK	ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefMDIChildProc(hWnd, message, wParam, lParam);//�˴���ͬ
}