//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
using namespace std;
#include <windows.h>

DWORD WINAPI thread_fun(LPVOID n)
{
	int i = 0;
	for (int i = 0; i < 10; i++)
	{
		printf("%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d\n", n, n, n, n, n, n, n, n, n, n, n, n, n, n, n);
	}
	return 0;
}

int main()
{
	HANDLE hThread = nullptr;
	DWORD ThreadID = 0;
	for (int i = 0; i < 5; i++)
	{
		hThread = CreateThread(nullptr, 0, thread_fun, (LPVOID)(i), 0, &ThreadID);
		if (hThread)
		{
			printf("线程创建成功:%d \n", i);
		}
	}
	
	Sleep(2000);
	//return EXIT_SUCCESS;

	system("pause");
	return 0;
}