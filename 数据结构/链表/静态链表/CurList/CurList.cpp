#include "CurList.h"
//��һά����space�и���������һ��������
//space[0].CurΪͷָ�룬"0"��ʾ��ָ��
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
//�����ÿռ�����ǿգ��򷵻ط���Ľ���±����򷵻�0
int Malloc_SLL(CurSpace space)
{
	int i = space[0].Cur; //��ǰ�����һ��Ԫ�ص�cur���ֵ  ����Ҫ���صĵ�һ�����ÿ��е��±�
	if (space[0].Cur)
	{
		space[0].Cur = space[i].Cur; //����Ҫ�ó�һ��������ʹ���ˣ��������Ǿ͵ð�������һ����������������
	}
	return i;
}
//��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e
JsStatu ListInsert(CurSpace space,int i,Elemtype e)
{
	int j,k,l;
	k = MAXSIZE - 1; //ע��K���������һ��Ԫ�ص�С��
	if (i<1||i>ListLength(space)+1)
	{
		return JS_ERROR;
	}
	j = Malloc_SLL(space); //��ÿ��з������±�
	if (j)
	{
		space[j].data = e; 
		for (l = 1;l<= i-1;l++)	//�ҵ���i��Ԫ��֮ǰ��λ��
		{
			k = space[k].Cur;
		}
		space[j].Cur = space[k].Cur; //�ѵ�i��Ԫ��֮ǰ��cur��ֵ����Ԫ�ص�cur
		space[k].Cur = j;
		return JS_TRUE;
	}
	return JS_ERROR;
}
//��ʼ��������̬����space�Ѵ���.�������:����space������Ԫ�صĸ���
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