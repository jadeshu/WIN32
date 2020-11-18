#include <windows.h>
#include <stdio.h>
/************************************************************************/
/* 1、创建线程练习*/
/* 2、CRITICAL_SECTION 临界区*/
/************************************************************************/
DWORD WINAPI myfun1(LPVOID lpThreadParameter);
DWORD WINAPI myfun2(LPVOID lpThreadParameter);
CRITICAL_SECTION cs;
int g1 = 0;
int main()
{
	InitializeCriticalSection(&cs);
	HANDLE h1,h2;
	h1 = CreateThread(nullptr,0,myfun1,nullptr,0,nullptr);
	printf("线程1开始运行！\n");
	h2 = CreateThread(nullptr,0,myfun2,nullptr,0,nullptr);
	printf("线程2开始运行！\n");

	CloseHandle(h1);
	CloseHandle(h2);
	
	Sleep(10000);
	if (getchar() == 'q')
	{
		return 0;
	}
	else
	{
		::Sleep(100);
	}
	return 0;
}

DWORD WINAPI myfun1(LPVOID lpThreadParameter)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		g1++;
		if (g1<10000)
		{
			Sleep(100);
			printf("线程1正在计数:%d\r\n",g1);
			LeaveCriticalSection(&cs);
		}
		else
		{
			LeaveCriticalSection(&cs);
			break;
		}

	}
	return 0;
}

DWORD WINAPI myfun2(LPVOID lpThreadParameter)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		g1++;
		if (g1<10000)
		{
			Sleep(100);
			printf("线程2正在计数:%d\r\n",g1);
			LeaveCriticalSection(&cs);
		}
		else
		{
			LeaveCriticalSection(&cs);
			break;
		}

	}
	return 0;
}