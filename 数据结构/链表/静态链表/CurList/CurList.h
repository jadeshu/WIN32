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

JsStatu InitList(CurSpace space);//将一维数组space中各分量链成一备用链表
int Malloc_SLL(CurSpace space);		//若备用空间链表非空，则返回分配的结点下表，否则返回0
JsStatu ListInsert(CurSpace space,int i,Elemtype e);
int ListLength(CurSpace space);
