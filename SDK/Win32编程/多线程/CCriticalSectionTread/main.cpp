#include <afxmt.h>
#include <stdio.h>
/************************************************************************/
/* 1、创建线程练习*/
/* 2、MFC临界区CCriticalSection*/
/************************************************************************/
DWORD WINAPI myfun1(LPVOID lpThreadParameter);
DWORD WINAPI myfun2(LPVOID lpThreadParameter);
CCriticalSection g_cs;
int g_length = 0;
int main()
{
	HANDLE h1,h2;
	h1 = CreateThread(nullptr,0,myfun1,nullptr,0,nullptr);
	printf("线程1开始运行!\r\n");
	h2 = CreateThread(nullptr,0,myfun2,nullptr,0,nullptr);
	printf("线程2开始运行!\r\n");

	CloseHandle(h1);
	CloseHandle(h2);
	getchar();
	return 0;
}

DWORD WINAPI myfun1(LPVOID lpThreadParameter)
{
	while (1)
	{
		g_cs.Lock();
		if (g_length<10000)
		{
			Sleep(10);
			g_length++;
			printf("线程1：%d\n",g_length);
			g_cs.Unlock();
		}
		else
		{
			g_cs.Unlock();
			break;
		}
	}
	
	return 0;
}

DWORD WINAPI myfun2(LPVOID lpThreadParameter)
{
	while (1)
	{
		g_cs.Lock();
		if (g_length<10000)
		{
			Sleep(100);
			g_length++;
			printf("线程2：%d\n",g_length);
			g_cs.Unlock();
		}
		else
		{
			g_cs.Unlock();
			break;
		}
	}
	return 0;
}