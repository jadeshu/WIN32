#include "CurList.h"
//将一维数组space中各分量链成一备用链表
//space[0].Cur为头指针，"0"表示空指针
JsStatu InitList(CurSpace space)
{
	int i;
	for (i=0;i<MAXSIZE-1;i++)
	{
		space[i].Cur = i+1;
	}
	space[MAXSIZE-1].Cur = 0;
	return JS_TRUE;
}
//若备用空间链表非空，则返回分配的结点下表，否则返回0
int Malloc_SLL(CurSpace space)
{
	int i = space[0].Cur; //当前数组第一个元素的cur存的值  就是要返回的第一个备用空闲的下标
	if (space[0].Cur)
	{
		space[0].Cur = space[i].Cur; //由于要拿出一个分量来使用了，所以我们就得把它的下一个分量用来做备用
	}
	return i;
}
//在L中第i个元素之前插入新的数据元素e
JsStatu ListInsert(CurSpace space,int i,Elemtype e)
{
	int j,k,l;
	k = MAXSIZE - 1; //注意K首先是最后一个元素的小标
	if (i<1||i>ListLength(space)+1)
	{
		return JS_ERROR;
	}
	j = Malloc_SLL(space); //获得空闲分量的下标
	if (j)
	{
		space[j].data = e; 
		for (l = 1;l<= i-1;l++)	//找到第i个元素之前的位置
		{
			k = space[k].Cur;
		}
		space[j].Cur = space[k].Cur; //把第i个元素之前的cur赋值给新元素的cur
		space[k].Cur = j;
		return JS_TRUE;
	}
	return JS_ERROR;
}
//初始条件：静态链表space已存在.操作结果:返回space中数据元素的个数
int ListLength(CurSpace space)
{
	int j=0;
	int i = space[MAXSIZE-1].Cur;
	while (i)
	{
		i = space[i].Cur;
		j++;
	}
	return j;
}

int main()
{
	return 0;
}