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
typedef struct Node	//���
{
	ElemType data;
	struct Node *pNext;
}Node,*pNode;

typedef struct LinkStack	//��ջ
{
	pNode top;	//�����ڵ�ָ��
	int count;	//����
}LinkStack;

/*  ����һ����ջS */
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
/* ��S��Ϊ��ջ */
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
/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
JS_Statu Push(LinkStack *s,ElemType e)
{
	pNode pn=(pNode)malloc(sizeof(Node)); 
	pn->data = e;
	pn->pNext = s->top;
	s->top = pn;
	s->count++;
	return JS_OK;
}

/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
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