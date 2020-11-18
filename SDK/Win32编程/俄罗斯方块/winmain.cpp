#include <windows.h> 
#include <tchar.h>

#define MAX_LOADSTRING 100  
//Tetris  
#define BOUND_SIZE 10  
#define TETRIS_SIZE 30  
#define GAME_X 10  
#define GAME_Y 20  
#define INFO_X 6  
#define INFO_Y GAME_Y  

//��ʱ��  
#define  MY_TIMEER 1  
#define  DEFAULT_INTERVAL 500 //Ĭ��ÿ0.5���½�һ��  

//�������˹�������״  
BOOL g_astTetris[6][4][4] =   
{  
	{{1,1,0,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},  
	{{1,1,0,0},{0,0,1,1},{0,0,0,0},{0,0,0,0}},  
	{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},  
	{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},  
	{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},  
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}}  
};  
#define  TETRIS_CNT (sizeof(g_astTetris)/sizeof(g_astTetris[0]))  


//��ǰ�������״  
BOOL g_CurTetris[4][4];  
BOOL g_NextTetris[4][4];  
BOOL g_stGame[GAME_X][GAME_Y];//��¼�Ѿ��������ķ���  

//��¼�������Ͻǵ�����  
UINT TetrisX;  
UINT TetrixY;  
UINT g_uiInterval;  
UINT g_uiScore;  

UINT g_uiMySeed = 0xffff;  

// ȫ�ֱ���:  
HINSTANCE hInst;                                // ��ǰʵ��  
TCHAR szTitle[MAX_LOADSTRING] = _T("����˹����");                  // �������ı�  
TCHAR szWindowClass[MAX_LOADSTRING] = _T("elfk");            // ����������  

// �˴���ģ���а����ĺ�����ǰ������:  
ATOM                MyRegisterClass(HINSTANCE hInstance);  
BOOL                InitInstance(HINSTANCE, int);  
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);  
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);  

int APIENTRY _tWinMain(HINSTANCE hInstance,  
					   HINSTANCE hPrevInstance,  
					   LPTSTR    lpCmdLine,  
					   int       nCmdShow)  
{  
	UNREFERENCED_PARAMETER(hPrevInstance);  
	UNREFERENCED_PARAMETER(lpCmdLine);  

	// TODO: �ڴ˷��ô��롣  
	MSG msg;  
 
	MyRegisterClass(hInstance);  

	// ִ��Ӧ�ó����ʼ��:  
	if (!InitInstance (hInstance, nCmdShow))  
	{  
		return FALSE;  
	}  

	// ����Ϣѭ��:  
	while (GetMessage(&msg, NULL, 0, 0))  
	{  
		TranslateMessage(&msg);  
		DispatchMessage(&msg);  
	}  

	return (int) msg.wParam;  
}  



//  
//  ����: MyRegisterClass()  
//  
//  Ŀ��: ע�ᴰ���ࡣ  
//  
//  ע��:  
//  
//    ����ϣ��  
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��  
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��  
//    ����Ӧ�ó���Ϳ��Ի�ù�����  
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ  
//  
ATOM MyRegisterClass(HINSTANCE hInstance)  
{  
	WNDCLASSEX wcex;  

	wcex.cbSize = sizeof(WNDCLASSEX);  

	wcex.style          = CS_HREDRAW | CS_VREDRAW;  
	wcex.lpfnWndProc    = WndProc;  
	wcex.cbClsExtra     = 0;  
	wcex.cbWndExtra     = 0;  
	wcex.hInstance      = hInstance;  
	wcex.hIcon          = 0;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RUSSIAN_CUBE));  
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);  
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);  
	wcex.lpszMenuName   = 0;//MAKEINTRESOURCE(IDC_RUSSIAN_CUBE);  
	wcex.lpszClassName  = szWindowClass;  
	wcex.hIconSm        = 0;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));  

	return RegisterClassEx(&wcex);  
}  

//  
//   ����: InitInstance(HINSTANCE, int)  
//  
//   Ŀ��: ����ʵ�����������������  
//  
//   ע��:  
//  
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������  
//        ��������ʾ�����򴰿ڡ�  
//  
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)  
{  
	HWND hWnd;  

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����  

	hWnd = CreateWindow(szWindowClass, szTitle,  WS_MINIMIZEBOX | WS_SYSMENU,  
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);  

	if (!hWnd)  
	{  
		return FALSE;  
	}  

	ShowWindow(hWnd, nCmdShow);  
	UpdateWindow(hWnd);  

	return TRUE;  
}  

int GetRandNum(int iMin,int iMax)  
{  
	//ȡ�����  
	srand(GetTickCount() + g_uiMySeed-- );  

	return iMin + rand()%(iMax -iMin);  
}  

VOID DrawBackGround(HDC hdc)  
{  
	int x, y;  
	HPEN hPen = (HPEN)GetStockObject(NULL_PEN);  
	HBRUSH hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);  
	//(HBRUSH)CreateSolidBrush()  


	HBRUSH hBrush_luo = (HBRUSH)GetStockObject(BLACK_BRUSH);  

	Rectangle(hdc,BOUND_SIZE,BOUND_SIZE,BOUND_SIZE + GAME_X*TETRIS_SIZE  
		,BOUND_SIZE + GAME_Y * TETRIS_SIZE);  

	SelectObject(hdc,hPen);  

	for (x = 0; x < GAME_X; x++)  
	{  
		for (y = 0 ;y < GAME_Y; y++)  
		{  
			if (g_stGame[x][y])  
			{  
				SelectObject(hdc,hBrush_luo);  
			}  
			else  
			{  

				SelectObject(hdc,hBrush);  
			}  
			Rectangle(hdc,BOUND_SIZE + x*TETRIS_SIZE,  
				BOUND_SIZE + y * TETRIS_SIZE,  
				BOUND_SIZE + (x + 1)*TETRIS_SIZE,  
				BOUND_SIZE + (y + 1) * TETRIS_SIZE);  
		}  
	}  
}  
//��Ϣ�� �Ļ���  
VOID DrawInfo(HDC hdc)  
{  
	int x,y;  
	int nStartX,nStartY;  
	RECT rect;  
	TCHAR szBuf[100];//�÷ֵ��ַ���  

	HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);  
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);  

	HBRUSH hBrush_have = (HBRUSH)GetStockObject(GRAY_BRUSH);  
	SelectObject(hdc,hPen);  
	SelectObject(hdc,hBrush);  

	Rectangle(hdc,BOUND_SIZE*2 + GAME_X * TETRIS_SIZE,  
		BOUND_SIZE,BOUND_SIZE *2 + (GAME_X + INFO_X)*TETRIS_SIZE,  
		BOUND_SIZE + INFO_Y * TETRIS_SIZE);  

	for (x = 0; x < 4; x++)  
	{  
		for (y = 0 ;y < 4 ;y++)  
		{  
			nStartX = BOUND_SIZE *2 + GAME_X*TETRIS_SIZE + (y +1)*TETRIS_SIZE;  
			nStartY = BOUND_SIZE + (x +1)*TETRIS_SIZE;  
			if (g_NextTetris[x][y])  
			{  
				SelectObject(hdc,hBrush);  
			}  
			else  
			{  
				SelectObject(hdc,hBrush_have);  
			}  
			Rectangle(hdc,nStartX,nStartY,nStartX+TETRIS_SIZE,nStartY+TETRIS_SIZE);  
		}  
	}  

	nStartX = BOUND_SIZE *2 + GAME_X*TETRIS_SIZE;  
	nStartY = BOUND_SIZE ;  

	rect.left = nStartX + TETRIS_SIZE;  
	rect.right = nStartX + TETRIS_SIZE * (INFO_X -1);  
	rect.top = nStartY + TETRIS_SIZE *6;  
	rect.bottom = nStartY + TETRIS_SIZE *7;  

	wsprintf(szBuf,L"Score: %d",g_uiScore = 0);  

	DrawText(hdc,szBuf,wcslen(szBuf),&rect,DT_CENTER);  

}  

//���������飬��ʼ�������Ҫ���Ƶķ�����״  
VOID DrawTetris(HDC hdc, int nStartX,int nStartY,BOOL bTetris[4][4])  
{  
	int i,j;  
	HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);  
	HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);  
	SelectObject(hdc,hPen);  
	SelectObject(hdc,hBrush);  

	for (i = 0;i < 4; i++)  
	{  
		for (j = 0;j < 4;j++)  
		{  
			//j ��x���������ƫ��  
			if (bTetris[i][j])  
			{  
				Rectangle(hdc,BOUND_SIZE +(nStartX + j) * TETRIS_SIZE,  
					BOUND_SIZE + (nStartY + i)* TETRIS_SIZE,  
					BOUND_SIZE +(nStartX + j + 1) * TETRIS_SIZE,  
					BOUND_SIZE + (nStartY + i + 1)* TETRIS_SIZE);  
			}  
		}  
	}  
}  

//��ת����, ���ҿ����Ͻ�  
VOID RotateTetris(BOOL bTetris[4][4])  
{  
	BOOL bNewTetris[4][4] = {};//��ʼ������  
	int x, y;  
	int xPos,yPos;  
	BOOL bFlag;//�������Ͻ�  

	//�������£��������ң�˳ʱ����ת  
	//����  
	for (x = 0,xPos = 0 ;x < 4 ; x++)  
	{  
		bFlag = FALSE;  
		for (y = 0 ;y < 4 ;y++)  
		{  
			bNewTetris[xPos][y] = bTetris[3 - y][x];  
			//��ʱ����ת  
			//bNewTetris[x][y] = bTetris[y][3 - x];  
			if (bNewTetris[xPos][y])  
			{  
				bFlag = TRUE;//��һ��������  
			}  
		}  
		if (bFlag)  
		{  
			xPos++;  
		}  
	}  


	memset(bTetris,0,sizeof(bNewTetris));  
	//����  
	for (y = 0, yPos = 0;y < 4 ;y++)  
	{  
		bFlag = FALSE;  
		for (x = 0;x < 4; x++)  
		{  
			bTetris[x][yPos] = bNewTetris[x][y];  
			if (bTetris[x][yPos])  
			{  
				bFlag = TRUE;  
			}  
		}  
		if (bFlag)  
		{  
			yPos++;  
		}  
	}  
	//memcpy(bTetris,bNewTetris,sizeof(bNewTetris));  
	return;  
}  
BOOL CheckTetris(int nStartX,int nStartY,BOOL bTetris[4][4],BOOL bGame[GAME_X][GAME_Y])  
{  
	int x,y;  
	if (nStartX < 0)  
	{//������ǽ  
		return FALSE;  
	}  

	for (x = 0;x < 4;x++)  
	{  
		for (y = 0;y < 4;y++)  
		{  
			if (bTetris[x][y])  
			{  
				//����ǽ  
				if (nStartX +y >=GAME_X)  
				{  
					return FALSE;  
				}  
				//����ǽ  
				if (nStartY + x >=GAME_Y)  
				{  
					return FALSE;  
				}  
				//�������еķ���  
				if (bGame[nStartX +y][nStartY + x])  
				{  
					return FALSE;  
				}  
			}  
		}  
	}  
	return TRUE;  
}  

//��صķ���ϲ���������������һ��  
VOID RefreshTetris(int nStartX,int nStartY,BOOL bTetris[4][4], BOOL bGame[GAME_X][GAME_Y])  
{  
	BOOL bFlag = FALSE;  
	int x,y;  
	int newX,newY;//��Ҫ������¼  
	int iFulllie = 0; //У�����еĸ��Ӽ�¼���������ڻ���  

	for (x = 0; x < 4;x ++)  
	{  
		for (y = 0 ;y < 4; y++)  
		{  
			if (bTetris[x][y])  
			{  
				bGame[nStartX + y][nStartY +x] = TRUE;  
			}  
		}  
	}  

	for (y = GAME_Y,newY = GAME_Y; y >= 0; y--)  
	{  
		bFlag= FALSE;  
		for (x = 0;x < GAME_X;x++)  
		{  
			bGame[x][newY] = bGame[x][y];  
			if (!bGame[x][y])//��һ�в�����  
			{  
				bFlag = TRUE;  
			}  
		}  
		if (bFlag)  
		{  
			newY--;  
		}  
		else  
		{  
			//����Ļ�������һ���滻��һ��  
			iFulllie++;  
		}  
	}  

	if (iFulllie)  
	{  
		g_uiScore -= iFulllie *1;  
	}  
	//�ϲ��Ժ������µķ��飬��ˢ��λ��  
	memcpy(g_CurTetris,g_NextTetris,sizeof(g_CurTetris));  
	memcpy(g_NextTetris,g_astTetris[ GetRandNum(0,TETRIS_CNT)],sizeof(g_NextTetris));  

	TetrisX = (GAME_X - 4)/2;  
	TetrixY = 0;  
}  

//��ʼ����Ϸ,���Ƿ������ȳ�ʼ����λ��  
VOID InitGame()  
{  
	int iTmp;  

	TetrisX = (GAME_X - 4 )/2 ; //����  
	TetrixY = 0;  

	g_uiScore = 0;  
	g_uiInterval = DEFAULT_INTERVAL;  

	iTmp = GetRandNum(0,TETRIS_CNT);  
	memcpy(g_CurTetris,g_astTetris[iTmp],sizeof(g_CurTetris));  

	iTmp = GetRandNum(0,TETRIS_CNT);  
	memcpy(g_NextTetris,g_astTetris[iTmp],sizeof(g_NextTetris));  

	memset(g_stGame,0,sizeof(g_stGame));  
}  
//  
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  Ŀ��: ���������ڵ���Ϣ��  
//  
//  WM_COMMAND  - ����Ӧ�ó���˵�  
//  WM_PAINT    - ����������  
//  WM_DESTROY  - �����˳���Ϣ������  
//  
//  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  
{  
	PAINTSTRUCT ps;  
	HDC hdc;  

	int nWinX,nWinY,nClientX,nClientY;  
	RECT rect;  
	BOOL bTmpTetris[4][4] = {};  

	switch (message)  
	{  
	case WM_CREATE:  
		//��ȡ���ڴ�С  
		GetWindowRect(hWnd,&rect);  
		nWinX = rect.right - rect.left;  
		nWinY = rect.bottom - rect.top;  
		//��ȡ�ͻ�����С  
		GetClientRect(hWnd,&rect);  
		nClientX = rect.right - rect.left;  
		nClientY = rect.bottom - rect.top;  

		MoveWindow(hWnd,0,0,3 * BOUND_SIZE + (GAME_X + INFO_X)* TETRIS_SIZE +  
			(nWinX  - nClientX),  
			2 * BOUND_SIZE + GAME_Y*TETRIS_SIZE + (nWinY - nClientY),true);  
		InitGame();  
		SetTimer(hWnd,MY_TIMEER,g_uiInterval,NULL);  
		break;  
	case WM_TIMER:  
		//��ʱ���з����½�  
		if (CheckTetris(TetrisX,TetrixY + 1,g_CurTetris,g_stGame))  
		{  
			TetrixY++;  
		}  
		else  
		{  
			if (TetrixY == 0)  
			{  
				MessageBox(NULL,L"������",L"shit!",MB_OK);  
				KillTimer(hWnd,MY_TIMEER);  
			}  
			RefreshTetris(TetrisX,TetrixY,g_CurTetris,g_stGame);  
		}  
		InvalidateRect(hWnd,NULL,TRUE);  

		break;  
	case WM_LBUTTONDOWN:  
		RotateTetris(g_CurTetris);  
		InvalidateRect(hWnd,NULL,TRUE);  
		break;  
	case WM_KEYDOWN:  
		switch(wParam)  
		{  
		case VK_LEFT://�����  
			if (CheckTetris(TetrisX -1,TetrixY,g_CurTetris,g_stGame))  
			{//�ж�һ�µ�ǰ����û�п�ǽ��  
				TetrisX--;  
				InvalidateRect(hWnd,NULL,TRUE);  
			}  
			else  
			{  
				MessageBeep(0);  
			}  
			break;  
		case  VK_RIGHT:  
			if (CheckTetris(TetrisX +1,TetrixY,g_CurTetris,g_stGame))  
			{//�ж�һ�µ�ǰ����û�п�ǽ��  
				TetrisX++;  
				InvalidateRect(hWnd,NULL,TRUE);  
			}  
			else  
			{  
				MessageBeep(0);  
			}  
			break;  
		case VK_UP://���Σ�����Ҫ�жϱ��γɹ�����ʧ��  
			memcpy(bTmpTetris,g_CurTetris,sizeof(bTmpTetris));  
			RotateTetris((bTmpTetris));  
			if (CheckTetris(TetrisX,TetrixY,bTmpTetris,g_stGame))  
			{  
				//�ɹ����ٰ���ת���copy����  
				memcpy(g_CurTetris,bTmpTetris,sizeof(bTmpTetris));  
				InvalidateRect(hWnd,NULL,TRUE);  
			}  
			break;  
		case VK_DOWN:  
			while (CheckTetris(TetrisX,TetrixY + 1,g_CurTetris,g_stGame))  
			{  
				TetrixY++;  

			}  
			RefreshTetris(TetrisX,TetrixY,g_CurTetris,g_stGame);  
			InvalidateRect(hWnd,NULL,TRUE);  
			break;  
		default:  
			break;  
		}  

		break;  
	case WM_PAINT:  
		hdc = BeginPaint(hWnd, &ps);  
		// TODO: �ڴ���������ͼ����...  
		DrawBackGround(hdc);  
		DrawInfo(hdc);  
		DrawTetris(hdc,TetrisX,TetrixY,g_CurTetris);  
		EndPaint(hWnd, &ps);  
		break;  
	case WM_DESTROY:  
		KillTimer(hWnd,MY_TIMEER);  
		PostQuitMessage(0);  
		break;  
	default:  
		return DefWindowProc(hWnd, message, wParam, lParam);  
	}  
	return 0;  
}