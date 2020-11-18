#include <stdio.h>
#define JS_ERROR -1
#define JS_OK	1
#define JS_FALSE 0
#define MAXSIZE 100
typedef int JS_Statu;
typedef int ElemType;

typedef struct
{
	ElemType data[MAXSIZE];
	int top;
}Stack;

JS_Statu visit(ElemType c)
{
	printf("%d ",c);
	return JS_OK;
}

JS_Statu InitStack(Stack *s)  /*  ����һ����ջS */
{
	s->top = -1;
	return JS_OK;
}

JS_Statu ClearStack(Stack *s)  /* ��S��Ϊ��ջ */
{
	s->top = -1;
	return JS_OK;
}

JS_Statu StackEmpty(Stack s)	/* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
{
	if (s.top == -1)
	{
		return JS_OK;
	}
	return JS_FALSE;
}

/* ����S��Ԫ�ظ�������ջ�ĳ��� */
int StackLength(Stack s)
{
	return s.top+1;
}

// ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR 
JS_Statu GetTop(Stack s,ElemType *e)
{
	if (s.top == -1)
	{
		return JS_ERROR;
	}
	*e = s.data[s.top];
	return JS_OK;
}
/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
JS_Statu Push(Stack *s,ElemType e)
{
	if (s->top == MAXSIZE-1)
	{
		return JS_ERROR;
	}
	s->top++;
	s->data[s->top] = e;
	return JS_OK;
}
/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
JS_Statu Pop(Stack *s,ElemType *e)
{
	if (s->top == -1)
	{
		return JS_ERROR;
	}
	*e = s->data[s->top];
	s->top--;
	return JS_OK;
}
/* ��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ����ʾ */
JS_Statu StackTraverse(Stack s)
{
	int i;
	i=0;
	while(i<=s.top)
	{
		visit(s.data[i++]);
	}
	printf("\n");
	return JS_OK;
}
int main()
{
	int j;
	Stack s;
	int e;
	if(InitStack(&s)==JS_OK)
		for(j=1;j<=10;j++)
			Push(&s,j);
	printf("ջ��Ԫ������Ϊ��");
	StackTraverse(s);
	Pop(&s,&e);
	printf("������ջ��Ԫ�� e=%d\n",e);
	printf("ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));
	GetTop(s,&e);
	printf("ջ��Ԫ�� e=%d ջ�ĳ���Ϊ%d\n",e,StackLength(s));
	ClearStack(&s);
	printf("���ջ��ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));
	return 0;
}