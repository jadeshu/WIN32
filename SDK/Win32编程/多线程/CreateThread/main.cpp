#include <windows.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 1�������߳���ϰ*/
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
DWORD WINAPI myfun1(LPVOID lpThreadParameter);
DWORD WINAPI myfun2(LPVOID lpThreadParameter);
int main()
{
	HANDLE h1,h2;
	h1 = CreateThread(nullptr,0,myfun1,nullptr,0,nullptr);
	printf("�߳�1��ʼ���У�\n");
	h2 = CreateThread(nullptr,0,myfun2,nullptr,0,nullptr);
	printf("�߳�2��ʼ���У�\n");
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
	printf("�߳�1�������У�\n");
	return 0;
}

DWORD WINAPI myfun2(LPVOID lpThreadParameter)
{
	printf("�߳�2�������У�\n");
	return 0;
}