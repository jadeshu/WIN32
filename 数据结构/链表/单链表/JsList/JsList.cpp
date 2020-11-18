#include "JsList.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//随机产生n个元素的值，建立带头结点的单链表L（头插法）
void CreateListHead(JsList *L,int n)
{
	JsList p;
	int i;
	srand(time(0));	//初始化随机数字
	*L = (JsList)malloc(sizeof(Node));
	(*L)->pNext = NULL;   //先建立一个带头结点的单链表
	for (i=0;i<n;i++)
	{
		p = (JsList)malloc(sizeof(Node));
		p->data = rand()%100+1;
		p->pNext = (*L)->pNext;
		(*L)->pNext = p;
	}
}
//随机产生n个元素的值，建立带头结点的单链表L（尾插法）
void CreateListTail(JsList *L,int n)
{
	JsList p,r;
	int i;
	srand(time(0));	//初始化随机数字
	*L = (JsList)malloc(sizeof(Node));	//为整个线性表
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
//初始化条件:线性表L已存在，操作结果：将L重置为空表
JS_Statu ClearList(JsList *L)	
{
	if (L == NULL)
	{
		return JS_ERROR;
	}
	JsList p,q;
	p = (*L)->pNext;	//p指向第一个结点
	while (p)			//没到表尾
	{
		q = p->pNext;	
		free(p);
		p = q;
	}
	(*L)->pNext = NULL;	//头结点指针域为空
	return JS_OK;
}

JS_Statu GetElem(JsList L,int i,ElemType *e)
{
	int j;
	JsList p; // 声明一指针P
	p = L->pNext;//指向链表L的第一个结点
	j = 1;
	while ( p && j<i)
	{
		p = p->pNext;	//让p指向下一个结点
		++j;
	}
	if (!p || j>i)
	{
		return JS_ERROR;	//第i个元素不存在
	}
	*e = p->data;	//取第i个元素的数据
	return JS_OK;
}

JS_Statu ListInsert(JsList *L,int i,ElemType e)
{
	int j;
	JsList p,s;
	p = *L;
	j = 1;
	while (p && j<i)	//寻找第i个结点
	{
		p = p->pNext;
		++j;
	}
	if (!p || j>i)
	{
		return JS_ERROR;	//第i个元素不存在
	}
	s = (JsList)malloc(sizeof(Node));//生成新结点
	s->data = e;
	s->pNext = p->pNext;//将p的后继结点赋值给s的后继
	p->pNext = s;	//将s赋值给p的后继
	return JS_OK;
}

JS_Statu ListDelete(JsList *L,int i,ElemType *e)
{
	int j;
	JsList p,q;
	p = *L;
	j = 1;
	while (p && j<i)	//寻找第i个结点
	{
		p = p->pNext;
		++j;
	}
	if (!p || j>i)
	{
		return JS_ERROR;	//第i个元素不存在
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