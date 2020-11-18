//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
using namespace std;

// 插入排序
void InsertSort(int arr[], int len)
{
	int temp = 0;
	int j = 0;
	// 插入多少次
	for (int i = 0; i < len ; i++)
	{
		temp = arr[i];
		j = i - 1;
		while (j >= 0 && temp < arr[j])
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

int main()
{
	int arr[] = { 10,4,8,90,250,340,12,56 };
	int len = sizeof(arr) / sizeof(arr[0]);
	InsertSort(arr, len);
	for (int i = 0; i < len; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\r\n");

	system("pause");
	return 0;
}