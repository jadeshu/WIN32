#include "JsList.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//�������n��Ԫ�ص�ֵ��������ͷ���ĵ�����L��ͷ�巨��
void CreateListHead(JsList *L,int n)
{
	JsList p;
	int i;
	srand(time(0));	//��ʼ���������
	*L = (JsList)malloc(sizeof(Node));
	(*L)->pNext = NULL;   //�Ƚ���һ����ͷ���ĵ�����
	for (i=0;i<n;i++)
	{
		p = (JsList)malloc(sizeof(Node));
		p->data = rand()%100+1;
		p->pNext = (*L)->pNext;
		(*L)->pNext = p;
	}
}
//�������n��Ԫ�ص�ֵ��������ͷ���ĵ�����L��β�巨��
void CreateListTail(JsList *L,int n)
{
	JsList p,r;
	int i;
	srand(time(0));	//��ʼ���������
	*L = (JsList)malloc(sizeof(Node));	//Ϊ�������Ա�
	r = *L;
	for (i=0;i<n;i++)
	{
		p = (JsList)malloc(sizeof(Node));
		p->data = rand()%100+1;
		r->pNext = p;
		r = p;
	}
	r->pNext = NULL;
}
//��ʼ������:���Ա�L�Ѵ��ڣ������������L����Ϊ�ձ�
JS_Statu ClearList(JsList *L)	
{
	if (L == NULL)
	{
		return JS_ERROR;
	}
	JsList p,q;
	p = (*L)->pNext;	//pָ���һ�����
	while (p)			//û����β
	{
		q = p->pNext;	
		free(p);
		p = q;
	}
	(*L)->pNext = NULL;	//ͷ���ָ����Ϊ��
	return JS_OK;
}

JS_Statu GetElem(JsList L,int i,ElemType *e)
{
	int j;
	JsList p; // ����һָ��P
	p = L->pNext;//ָ������L�ĵ�һ�����
	j = 1;
	while ( p && j<i)
	{
		p = p->pNext;	//��pָ����һ�����
		++j;
	}
	if (!p || j>i)
	{
		return JS_ERROR;	//��i��Ԫ�ز�����
	}
	*e = p->data;	//ȡ��i��Ԫ�ص�����
	return JS_OK;
}

JS_Statu ListInsert(JsList *L,int i,ElemType e)
{
	int j;
	JsList p,s;
	p = *L;
	j = 1;
	while (p && j<i)	//Ѱ�ҵ�i�����
	{
		p = p->pNext;
		++j;
	}
	if (!p || j>i)
	{
		return JS_ERROR;	//��i��Ԫ�ز�����
	}
	s = (JsList)malloc(sizeof(Node));//�����½��
	s->data = e;
	s->pNext = p->pNext;//��p�ĺ�̽�㸳ֵ��s�ĺ��
	p->pNext = s;	//��s��ֵ��p�ĺ��
	return JS_OK;
}

JS_Statu ListDelete(JsList *L,int i,ElemType *e)
{
	int j;
	JsList p,q;
	p = *L;
	j = 1;
	while (p && j<i)	//Ѱ�ҵ�i�����
	{
		p = p->pNext;
		++j;
	}
	if (!p || j>i)
	{
		return JS_ERROR;	//��i��Ԫ�ز�����
	}
	q = p->pNext;
	p->pNext = q->pNext;
	*e = q->data;
	free(q);
	return JS_OK;
}

int main()
{
	/*JsList jsde;
	CreateListHead(&jsde,5);
	ClearList(&jsde);*/
	return 0;
}