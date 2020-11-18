#include <windows.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 1、创建线程练习*/
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
DWORD WINAPI myfun1(LPVOID lpThreadParameter);
DWORD WINAPI myfun2(LPVOID lpThreadParameter);
int main()
{
	HANDLE h1,h2;
	h1 = CreateThread(nullptr,0,myfun1,nullptr,0,nullptr);
	printf("线程1开始运行！\n");
	h2 = CreateThread(nullptr,0,myfun2,nullptr,0,nullptr);
	printf("线程2开始运行！\n");
	CloseHandle(h1);
	CloseHandle(h2);
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
	printf("线程1正在运行！\n");
	return 0;
}

DWORD WINAPI myfun2(LPVOID lpThreadParameter)
{
	printf("线程2正在运行！\n");
	return 0;
}