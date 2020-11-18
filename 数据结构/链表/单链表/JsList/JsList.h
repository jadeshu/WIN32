#define JS_ERROR -1
#define JS_OK	1
#define JS_FALSE 0
typedef int JS_Statu;

typedef int ElemType;
typedef struct tagNode
{
	ElemType data;
	struct tagNode *pNext;
}Node,*JsList;

void CreateListHead(JsList *L,int n);   //ͷ�巨
void CreateListTail(JsList *L,int n);   //β�巨
JS_Statu ClearList(JsList *L);		
JS_Statu GetElem(JsList L,int i,ElemType *e);
JS_Statu ListInsert(JsList *L,int i,ElemType e);
JS_Statu ListDelete(JsList *L,int i,ElemType *e);
