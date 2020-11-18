//#include "resource.h"
#include <windows.h>
#include "resource.h"
#include <tchar.h>
#include "PrSht.h"
#pragma comment(lib,"comctl32.lib")
HINSTANCE g_hInst;
INT_PTR  CALLBACK LogInProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int DoPropertySheet(HWND hDlg) 
{ 
	PROPSHEETPAGE psp[2]; 
	PROPSHEETHEADER psh;
	psp[0].dwSize = sizeof(PROPSHEETPAGE); 
	psp[0].dwFlags =PSP_USETITLE; 
	psp[0].hInstance = g_hInst; 
	psp[0].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG1); 
	psp[0].pszIcon = NULL; 
	psp[0].pfnDlgProc =LogInProc; 
	psp[0].pszTitle =TEXT("test1"); 
	psp[0].lParam = 0; 
	psp[0].pfnCallback =NULL;
	psp[1].dwSize = sizeof(PROPSHEETPAGE); 
	psp[1].dwFlags = PSP_USETITLE ; 
	psp[1].hInstance = g_hInst; 
	psp[1].pszTemplate =MAKEINTRESOURCE(IDD_DIALOG2); 
	psp[1].pszIcon = NULL; 
	psp[1].pfnDlgProc = NULL; 
	psp[1].pszTitle = TEXT("test2"); 
	psp[1].lParam = 0; 
	psp[1].pfnCallback = NULL;
	psh.dwSize = sizeof(PROPSHEETHEADER); 
	psh.dwFlags = PSH_PROPSHEETPAGE; 
	psh.hwndParent = hDlg; 
	psh.hInstance = g_hInst; 
	psh.pszIcon =NULL; 
	psh.pszCaption = _T( "Cell Properties"); 
	psh.nPages = sizeof(psp)/sizeof(PROPSHEETPAGE); 
	psh.nStartPage = 0; 
	psh.ppsp = (LPCPROPSHEETPAGE) &psp; 
	psh.pfnCallback = NULL;
	int code=PropertySheet(&psh); 
	return code; 
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR lpCmdLine,
					   int nCmdShow)
{
	g_hInst=hInstance;
	return DoPropertySheet(NULL);
}
INT_PTR  CALLBACK LogInProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(message)
	{
	case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if (LOWORD(wParam)==IDOK || LOWORD(wParam)==IDCANCEL)
			{
				MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
				EndDialog(hDlg,LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}