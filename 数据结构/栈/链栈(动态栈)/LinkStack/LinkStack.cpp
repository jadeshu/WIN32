#include <stdlib.h>
#include <stdio.h>
#define JS_ERROR -1
#define JS_OK	1
#define JS_FALSE 0

typedef int JS_Statu;
typedef int ElemType;

JS_Statu visit(ElemType c)
{
	printf("%d ",c);
	return JS_OK;
}
typedef struct Node	//结点
{
	ElemType data;
	struct Node *pNext;
}Node,*pNode;

typedef struct LinkStack	//链栈
{
	pNode top;	//顶部节点指针
	int count;	//个数
}LinkStack;

/*  构造一个空栈S */
JS_Statu InitStack(LinkStack *s)
{
	s->top = (pNode)malloc(sizeof(Node));		
	if (!s->top)
	{
		return JS_ERROR;
	}
	s->top = NULL;
	s->count = 0;
	return JS_OK;

}
/* 把S置为空栈 */
JS_Statu ClearStack(LinkStack *s)
{ 
	pNode p,q;
	p = s->top;
	while (p)
	{
		q = p;
		p = p->pNext;
		free(q);
	}
	s->count = 0;
	return JS_OK;
}
/* 插入元素e为新的栈顶元素 */
JS_Statu Push(LinkStack *s,ElemType e)
{
	pNode pn=(pNode)malloc(sizeof(Node)); 
	pn->data = e;
	pn->pNext = s->top;
	s->top = pn;
	s->count++;
	return JS_OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
JS_Statu Pop(LinkStack *s,ElemType *e)
{ 
	pNode p;
	if (s->count == 0)
	{
		return JS_ERROR;
	}
	*e = s->top->data;
	p = s->top;
	s->top = s->top->pNext;
	free(p);
	s->count--;
	return JS_OK;
}
int main()
{
	return 0;
}