// �Ի���λͼ����  - WM_CTLCOLORDLG��ʹ��StretchBlt��ͼ  
#include <windows.h>  
#include "resource.h"  

const char szDlgTitle[] = "λͼ���� ʹ��StretchBlt��ͼ";  

// �Ի�����Ϣ������  
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
	//static BITMAP s_bm;  
	//static HDC    s_hdcMem; 
	static HBRUSH s_brush;

	switch (message)  
	{  
	case WM_INITDIALOG:  
		{
			// ���öԻ������  
			SetWindowText(hDlg, szDlgTitle);  
			// ���öԻ����С�ɵ���  
			LONG style = GetWindowLong(hDlg, GWL_STYLE);
			//style &= WS_DLGFRAME;
			SetWindowLong(hDlg, GWL_STYLE, style | WS_SIZEBOX | WS_MAXIMIZEBOX); 

			// ���ر�ӰͼƬ  
			HBITMAP    hBitmap = (HBITMAP)LoadImage(NULL, "005.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  
			if (hBitmap == NULL)  
			{  
				MessageBox(hDlg, "LoadImage failed", "Error", MB_ICONERROR);  
				exit(0);  
			}         
			else  
			{  
				// ����ӰͼƬ����HDC - s_hdcMem  
/*				HDC        hdc;  
				hdc = GetDC(hDlg);  
				s_hdcMem = CreateCompatibleDC(hdc);  
				SelectObject(s_hdcMem, hBitmap);      
				ReleaseDC(hDlg, hdc);*/  

				// �õ�λͼ��Ϣ  
				//GetObject(hBitmap, sizeof(s_bm), &s_bm); 

				// ����λͼ��ˢ 
				
			}  
			s_brush = CreatePatternBrush(hBitmap);
			return 0;
		}		  

	case WM_COMMAND:  
		{
			switch (LOWORD(wParam))  
			{  
			case IDCANCEL:  
				//DeleteDC(s_hdcMem); 
				DeleteObject(s_brush);
				EndDialog(hDlg, LOWORD(wParam));  
				return TRUE;  
			}  
			break;
		}  
	case WM_SIZE:  
		{
			InvalidateRect(hDlg, NULL, TRUE);  
			return TRUE;  
		}	
	case WM_CTLCOLORDLG:  
		{
			//��һ�� ��ֱ�ӻ�ͼ
			//RECT   rcDialog;  
			//GetClientRect(hDlg, &rcDialog);  
			////ͨ��SetStretchBltMode��������ʹStretchBlt������ͼ���������  
			//SetStretchBltMode((HDC)wParam, COLORONCOLOR);  
			//StretchBlt((HDC)wParam, 0, 0, rcDialog.right, rcDialog.bottom, s_hdcMem, 0, 0, s_bm.bmWidth, s_bm.bmHeight, SRCCOPY);     
			//return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));

			//�ڶ��� ����λͼ��ˢ
			return (BOOL)s_brush;	//ƽ��ͼƬ
		}
		
	/*case WM_NCHITTEST:  
		POINT point;  
		point.x = LOWORD(lParam);  
		point.y = HIWORD(lParam);  
		RECT rect;          
		GetWindowRect(hDlg,&rect);  
		if(point.x <= rect.left+5)  
		{  
			return HTLEFT;  
		}  
		else if(point.x >= rect.right-5 && point.y < rect.bottom-10)  
		{  
			return HTRIGHT;  
		}  
		else if(point.y <= rect.top+5)  
		{      
			return HTTOP;  
		}  
		else if(point.y >= rect.bottom-5&& point.x < rect.right-10)  
		{  
			return HTBOTTOM;  
		}  
		else if(point.x <= rect.left+10 && point.y <= rect.top+10)  
		{  
			return HTTOPLEFT;  
		}  
		else if(point.x >= rect.right-10 && point.y <= rect.top+10)  
		{  
			return HTTOPRIGHT;  
		}  
		else if(point.x <= rect.left+10 && point.y >= rect.bottom-10)  
		{  
			return HTBOTTOMLEFT;  
		}  
		else if(point.x >= rect.right-10 && point.y >= rect.bottom-10)  
		{  
			return HTBOTTOMRIGHT;  
		}  

	case WM_SETCURSOR:  
		{  
			UINT nHitTest = LOWORD(lParam);  
			switch(nHitTest)  
			{  
			case HTTOP:  
			case HTBOTTOM:  
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));  
				break;  
			case HTLEFT:  
			case HTRIGHT:  
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));  
				break;  
			case HTTOPLEFT:  
			case HTBOTTOMRIGHT:  
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));  
				break;  
			case HTTOPRIGHT:  
			case HTBOTTOMLEFT:  
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));  
				break;  
			case HTCAPTION:  
			case HTSYSMENU:  
			case HTMENU:  
			case HTCLIENT:  
			default:  
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));  
				break;  
			}  
		}
	case WM_NCLBUTTONDOWN:  
		switch(wParam)  
		{  
		case HTTOP:  
			SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, lParam);  
			break;  
		case HTBOTTOM:  
			SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, lParam);  
			break;  
		case HTLEFT:  
			SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, lParam);  
			break;  
		case HTRIGHT:  
			SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, lParam);  
			break;  
		case HTTOPLEFT:  
			SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, lParam);  
			break;  
		case HTTOPRIGHT:  
			SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, lParam);  
			break;  
		case HTBOTTOMLEFT:  
			SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, lParam);  
			break;  
		case HTBOTTOMRIGHT:  
			SendMessage(hDlg, WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, lParam);  
			break;  
		default:  
			break;  
		}  */
	}  
	return FALSE;  
}  