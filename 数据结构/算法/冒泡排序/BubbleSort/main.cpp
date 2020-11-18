//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
using namespace std;

// 冒泡排序
void BubbleSort(int arr[], int len)
{
	// 遍历多少趟
	for (int i = 0; i < (len-1); i++)
	{
		// 剩余多少数比较
		for (int j = 0; j < (len-1) - i; j++)
		{
			if (arr[j] > arr[j+1])
			{
				// 互换数据
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

int main()
{
	int arr[] = { 10,4,8,90,250,340,12,56 };
	int len = sizeof(arr) / sizeof(arr[0]);
	BubbleSort(arr, len);
	for (int i = 0; i < len; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\r\n");

	system("pause");
	return 0;
}