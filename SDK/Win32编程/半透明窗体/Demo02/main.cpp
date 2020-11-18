// 可变透明度窗体 先加上WS_EX_LAYERED属性再SetLayeredWindowAttributes设置透明度
#include <windows.h>  
#include "resource.h"  
#include <commctrl.h> 

const char szDlgTitle[] = "可变透明度窗体";  

// 对话框消息处理函数  
BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);  

int APIENTRY WinMain(HINSTANCE hInstance,  
					 HINSTANCE hPrevInstance,  
					 LPSTR     lpCmdLine,  
					 int       nCmdShow)  
{  
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);  
	return 0;  
}  


BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)  
{  	
	const int INIT_TRANSPARENT = 200; //窗体初始透明度 
	static HBRUSH s_brush = NULL;
	switch (message)  
	{  
	case WM_INITDIALOG:  
		{
			// 设置对话框标题  
			SetWindowText(hDlg, szDlgTitle);  
			
			HBITMAP hBmp = (HBITMAP)LoadImage(NULL,"005.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE/*|LR_CREATEDIBSECTION*/);
			//创建图案画刷
			s_brush = CreatePatternBrush(hBmp);

			// 设置分层属性
			LONG style = GetWindowLong(hDlg, GWL_EXSTYLE);
			style |= WS_EX_LAYERED;
			SetWindowLong(hDlg, GWL_EXSTYLE, style); 
			SetLayeredWindowAttributes(hDlg,0, INIT_TRANSPARENT, LWA_ALPHA);

			// 设置滑动条变化范围 
			SendMessage(GetDlgItem(hDlg,IDC_SLIDER1),TBM_SETRANGE,FALSE,MAKELONG(0,255));
			SendMessage(GetDlgItem(hDlg,IDC_SLIDER1),TBM_SETPOS,TRUE,INIT_TRANSPARENT);
			return 0;
		}		  

	case WM_COMMAND:  
		{
			switch (LOWORD(wParam))  
			{  
			case IDCANCEL:
				DeleteObject(s_brush);
				EndDialog(hDlg, LOWORD(wParam));  
				return TRUE;  
			}  
			break;
		}  	
	case WM_HSCROLL:
		{
			// 获取当前滑块位置  
			int nTransparent = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETPOS, 0, 0);   
			// 设置新透明度  
			SetLayeredWindowAttributes(hDlg, 0, nTransparent, LWA_ALPHA);  
			break;
		}
	case WM_CTLCOLORDLG:  
		{
			return (BOOL)s_brush;	//平铺图片
		}
	}  
	return FALSE;  
}  