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

JS_Statu InitStack(Stack *s)  /*  构造一个空栈S */
{
	s->top = -1;
	return JS_OK;
}

JS_Statu ClearStack(Stack *s)  /* 把S置为空栈 */
{
	s->top = -1;
	return JS_OK;
}

JS_Statu StackEmpty(Stack s)	/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
{
	if (s.top == -1)
	{
		return JS_OK;
	}
	return JS_FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(Stack s)
{
	return s.top+1;
}

// 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR 
JS_Statu GetTop(Stack s,ElemType *e)
{
	if (s.top == -1)
	{
		return JS_ERROR;
	}
	*e = s.data[s.top];
	return JS_OK;
}
/* 插入元素e为新的栈顶元素 */
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
/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
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
/* 从栈底到栈顶依次对栈中每个元素显示 */
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
	printf("栈中元素依次为：");
	StackTraverse(s);
	Pop(&s,&e);
	printf("弹出的栈顶元素 e=%d\n",e);
	printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
	GetTop(s,&e);
	printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
	ClearStack(&s);
	printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
	return 0;
}