// �ɱ�͸���ȴ��� �ȼ���WS_EX_LAYERED������SetLayeredWindowAttributes����͸����
#include <windows.h>  
#include "resource.h"  
#include <commctrl.h> 

const char szDlgTitle[] = "�ɱ�͸���ȴ���";  

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
	const int INIT_TRANSPARENT = 200; //�����ʼ͸���� 
	static HBRUSH s_brush = NULL;
	switch (message)  
	{  
	case WM_INITDIALOG:  
		{
			// ���öԻ������  
			SetWindowText(hDlg, szDlgTitle);  
			
			HBITMAP hBmp = (HBITMAP)LoadImage(NULL,"005.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE/*|LR_CREATEDIBSECTION*/);
			//����ͼ����ˢ
			s_brush = CreatePatternBrush(hBmp);

			// ���÷ֲ�����
			LONG style = GetWindowLong(hDlg, GWL_EXSTYLE);
			style |= WS_EX_LAYERED;
			SetWindowLong(hDlg, GWL_EXSTYLE, style); 
			SetLayeredWindowAttributes(hDlg,0, INIT_TRANSPARENT, LWA_ALPHA);

			// ���û������仯��Χ 
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
			// ��ȡ��ǰ����λ��  
			int nTransparent = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETPOS, 0, 0);   
			// ������͸����  
			SetLayeredWindowAttributes(hDlg, 0, nTransparent, LWA_ALPHA);  
			break;
		}
	case WM_CTLCOLORDLG:  
		{
			return (BOOL)s_brush;	//ƽ��ͼƬ
		}
	}  
	return FALSE;  
}  