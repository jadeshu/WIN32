#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT UMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR szBuffer[100] = {0};
	switch (UMsg)
	{
	//case WM_SYSCOMMAND:
	//	{
	//		if (wParam ==SC_CLOSE)
	//		{
	//			PostQuitMessage(0);
	//			return TRUE;
	//		}
	//		break;
	//	}
	case WM_KEYDOWN:
		{
			int i=2;
			break;
		}
	case WM_COMMAND:
		{
			int id = LOWORD(wParam);
			int nCode = HIWORD(wParam);
			switch (id)
			{
			case IDC_BUTTON1:
				{
					TCHAR szBuffer[100] = {0};
					SendMessage(GetDlgItem(hwndDlg,IDC_EDIT1),WM_GETTEXT,100,(LPARAM)szBuffer);
					MessageBox(hwndDlg,szBuffer,_T("安全提示"),MB_OK);
					return TRUE;
				}
			case IDC_EDIT1:
				{
					if (nCode == EN_CHANGE)
					{
						SendMessage(GetDlgItem(hwndDlg,IDC_EDIT1),WM_GETTEXT,100,(LPARAM)szBuffer);
						SendMessage(GetDlgItem(hwndDlg,IDC_EDIT2),WM_SETTEXT,0,(LPARAM)szBuffer);
						
					}
					return TRUE;
				}
			default:
				break;
			}
			break;
		}
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return TRUE;
		}		
	default:
		break;
	}
	return FALSE;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	HWND  hWndDlg = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG_MAIN),NULL,DialogProc);
	ShowWindow(hWndDlg,nShowCmd);

	RECT rt;
	GetClientRect(hWndDlg,&rt);
	int cxClient = rt.right - rt.left;
	int cyClient = rt.bottom - rt.top;
	int cxScreen = GetSystemMetrics(SM_CXFULLSCREEN);
	int cyScreen = GetSystemMetrics(SM_CYFULLSCREEN);
	SetWindowPos(hWndDlg,HWND_TOP,(cxScreen-cxClient)/2,(cyScreen-cyClient)/2,cxClient,cyClient,SWP_NOSIZE|SWP_SHOWWINDOW);
	
	MSG msg = {0};
	while (GetMessage(&msg,NULL,0,0))
	{
		if(!IsDialogMessage(hWndDlg,&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}