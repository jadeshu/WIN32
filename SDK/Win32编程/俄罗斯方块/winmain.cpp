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

//定时器  
#define  MY_TIMEER 1  
#define  DEFAULT_INTERVAL 500 //默认每0.5秒下降一格  

//定义俄罗斯方块的形状  
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


//当前方块的形状  
BOOL g_CurTetris[4][4];  
BOOL g_NextTetris[4][4];  
BOOL g_stGame[GAME_X][GAME_Y];//记录已经落下来的方块  

//记录方块左上角的坐标  
UINT TetrisX;  
UINT TetrixY;  
UINT g_uiInterval;  
UINT g_uiScore;  

UINT g_uiMySeed = 0xffff;  

// 全局变量:  
HINSTANCE hInst;                                // 当前实例  
TCHAR szTitle[MAX_LOADSTRING] = _T("俄罗斯方块");                  // 标题栏文本  
TCHAR szWindowClass[MAX_LOADSTRING] = _T("elfk");            // 主窗口类名  

// 此代码模块中包含的函数的前向声明:  
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

	// TODO: 在此放置代码。  
	MSG msg;  
 
	MyRegisterClass(hInstance);  

	// 执行应用程序初始化:  
	if (!InitInstance (hInstance, nCmdShow))  
	{  
		return FALSE;  
	}  

	// 主消息循环:  
	while (GetMessage(&msg, NULL, 0, 0))  
	{  
		TranslateMessage(&msg);  
		DispatchMessage(&msg);  
	}  

	return (int) msg.wParam;  
}  



//  
//  函数: MyRegisterClass()  
//  
//  目的: 注册窗口类。  
//  
//  注释:  
//  
//    仅当希望  
//    此代码与添加到 Windows 95 中的“RegisterClassEx”  
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，  
//    这样应用程序就可以获得关联的  
//    “格式正确的”小图标。  
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
//   函数: InitInstance(HINSTANCE, int)  
//  
//   目的: 保存实例句柄并创建主窗口  
//  
//   注释:  
//  
//        在此函数中，我们在全局变量中保存实例句柄并  
//        创建和显示主程序窗口。  
//  
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)  
{  
	HWND hWnd;  

	hInst = hInstance; // 将实例句柄存储在全局变量中  

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
	//取随机数  
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
//信息区 的绘制  
VOID DrawInfo(HDC hdc)  
{  
	int x,y;  
	int nStartX,nStartY;  
	RECT rect;  
	TCHAR szBuf[100];//得分的字符串  

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

//绘制区方块，起始坐标和需要绘制的方块形状  
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
			//j 是x方向的坐标偏移  
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

//旋转方块, 并且靠左上角  
VOID RotateTetris(BOOL bTetris[4][4])  
{  
	BOOL bNewTetris[4][4] = {};//初始化置零  
	int x, y;  
	int xPos,yPos;  
	BOOL bFlag;//靠近左上角  

	//从上往下，从左往右，顺时针旋转  
	//靠上  
	for (x = 0,xPos = 0 ;x < 4 ; x++)  
	{  
		bFlag = FALSE;  
		for (y = 0 ;y < 4 ;y++)  
		{  
			bNewTetris[xPos][y] = bTetris[3 - y][x];  
			//逆时针旋转  
			//bNewTetris[x][y] = bTetris[y][3 - x];  
			if (bNewTetris[xPos][y])  
			{  
				bFlag = TRUE;//这一行有数据  
			}  
		}  
		if (bFlag)  
		{  
			xPos++;  
		}  
	}  


	memset(bTetris,0,sizeof(bNewTetris));  
	//靠左  
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
	{//碰到左墙  
		return FALSE;  
	}  

	for (x = 0;x < 4;x++)  
	{  
		for (y = 0;y < 4;y++)  
		{  
			if (bTetris[x][y])  
			{  
				//碰右墙  
				if (nStartX +y >=GAME_X)  
				{  
					return FALSE;  
				}  
				//碰下墙  
				if (nStartY + x >=GAME_Y)  
				{  
					return FALSE;  
				}  
				//碰到已有的方块  
				if (bGame[nStartX +y][nStartY + x])  
				{  
					return FALSE;  
				}  
			}  
		}  
	}  
	return TRUE;  
}  

//落地的方块合并，并且满足消除一行  
VOID RefreshTetris(int nStartX,int nStartY,BOOL bTetris[4][4], BOOL bGame[GAME_X][GAME_Y])  
{  
	BOOL bFlag = FALSE;  
	int x,y;  
	int newX,newY;//主要用来记录  
	int iFulllie = 0; //校区满行的格子记录行数，用于积分  

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
			if (!bGame[x][y])//这一行不满格  
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
			//满格的话，用上一行替换这一行  
			iFulllie++;  
		}  
	}  

	if (iFulllie)  
	{  
		g_uiScore -= iFulllie *1;  
	}  
	//合并以后生成新的方块，并刷新位置  
	memcpy(g_CurTetris,g_NextTetris,sizeof(g_CurTetris));  
	memcpy(g_NextTetris,g_astTetris[ GetRandNum(0,TETRIS_CNT)],sizeof(g_NextTetris));  

	TetrisX = (GAME_X - 4)/2;  
	TetrixY = 0;  
}  

//初始化游戏,就是方块最先初始化的位置  
VOID InitGame()  
{  
	int iTmp;  

	TetrisX = (GAME_X - 4 )/2 ; //居中  
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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  目的: 处理主窗口的消息。  
//  
//  WM_COMMAND  - 处理应用程序菜单  
//  WM_PAINT    - 绘制主窗口  
//  WM_DESTROY  - 发送退出消息并返回  
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
		//获取窗口大小  
		GetWindowRect(hWnd,&rect);  
		nWinX = rect.right - rect.left;  
		nWinY = rect.bottom - rect.top;  
		//获取客户区大小  
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
		//定时器中方块下降  
		if (CheckTetris(TetrisX,TetrixY + 1,g_CurTetris,g_stGame))  
		{  
			TetrixY++;  
		}  
		else  
		{  
			if (TetrixY == 0)  
			{  
				MessageBox(NULL,L"不行了",L"shit!",MB_OK);  
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
		case VK_LEFT://左方向键  
			if (CheckTetris(TetrisX -1,TetrixY,g_CurTetris,g_stGame))  
			{//判断一下当前方块没有靠墙就  
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
			{//判断一下当前方块没有靠墙就  
				TetrisX++;  
				InvalidateRect(hWnd,NULL,TRUE);  
			}  
			else  
			{  
				MessageBeep(0);  
			}  
			break;  
		case VK_UP://变形，但是要判断变形成功或者失败  
			memcpy(bTmpTetris,g_CurTetris,sizeof(bTmpTetris));  
			RotateTetris((bTmpTetris));  
			if (CheckTetris(TetrisX,TetrixY,bTmpTetris,g_stGame))  
			{  
				//成功后，再把旋转后的copy回来  
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
		// TODO: 在此添加任意绘图代码...  
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