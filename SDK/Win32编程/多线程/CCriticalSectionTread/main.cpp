#include <afxmt.h>
#include <stdio.h>
/************************************************************************/
/* 1�������߳���ϰ*/
/* 2��MFC�ٽ���CCriticalSection*/
/************************************************************************/
DWORD WINAPI myfun1(LPVOID lpThreadParameter);
DWORD WINAPI myfun2(LPVOID lpThreadParameter);
CCriticalSection g_cs;
int g_length = 0;
int main()
{
	HANDLE h1,h2;
	h1 = CreateThread(nullptr,0,myfun1,nullptr,0,nullptr);
	printf("�߳�1��ʼ����!\r\n");
	h2 = CreateThread(nullptr,0,myfun2,nullptr,0,nullptr);
	printf("�߳�2��ʼ����!\r\n");

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
			printf("�߳�1��%d\n",g_length);
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
			printf("�߳�2��%d\n",g_length);
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