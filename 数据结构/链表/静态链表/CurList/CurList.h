#define MAXSIZE 100
#define JS_ERROR -1
#define JS_TRUE 1
#define JS_FALSE 0

typedef int JsStatu;
typedef int Elemtype;

typedef struct
{
	Elemtype data;
	int Cur;
}Node,CurSpace[MAXSIZE];

JsStatu InitList(CurSpace space);//��һά����space�и���������һ��������
int Malloc_SLL(CurSpace space);		//�����ÿռ�����ǿգ��򷵻ط���Ľ���±����򷵻�0
JsStatu ListInsert(CurSpace space,int i,Elemtype e);
int ListLength(CurSpace space);
