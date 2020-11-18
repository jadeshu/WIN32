#include <iostream>
using namespace std;
typedef int ElemType;
typedef struct
{
	ElemType *pBase;
	int MAXSIZE;
	int cnt;
}SxList;

bool ClearList(SxList *List);    //清除线性表数据
bool LengthList(SxList *List,int *length,int *cnt);   //获取列表总长度保存length中，实际有效长度为cnt中
bool InitList(SxList *List,int length);	//初始化线性表 length为要申请的空间大小  ,初始化后必须调用DeleteList
bool GetElem(SxList *List,int i,ElemType *e); //获取指定i索引的元素并保存在缓存区e中
bool InsertList(SxList *List,int i,ElemType e);  //插入索引i的元素e
bool DeleteList(SxList *List); //删除整个线性表
bool DeleteElemList(SxList *List,int i,ElemType *e);  //删除索引i的元素并返回删除的数据保存在e中
bool EmptyList(SxList *List);  //当前列表是否为空  空返回TRUE否则返回FALSE
bool GetListElem(SxList *List,SxList *L1);


bool InitList(SxList *List,int length)   //初始化线性表
{
	if (length <= 0)
	{
		return false;
	}
	List->MAXSIZE = length;
	List->pBase = new ElemType[List->MAXSIZE];
	List->cnt = 0;
	return true;
}

bool EmptyList(SxList *List) //当前列表是否为空  空返回TRUE否则返回FALSE
{
	return (List->cnt==0)?true:false;
}

bool DeleteList(SxList *List) //删除整个线性表
{
	if (EmptyList(List))
	{
		return false;
	}
	else
	{
		delete []List->pBase;
		return true;
	}
}

bool InsertList(SxList *List,int i,ElemType e)
{
	if (i == List->MAXSIZE)
	{
		return false;
	}
	if (i<1 || i>(List->cnt + 1))
	{
		return false;
	}
	int k;
	for (k=List->cnt-1;k>=i-1;k--)
	{
		List->pBase[k+1] = List->pBase[k];

	}
	List->pBase[i-1] = e;
	++List->cnt;
	return true;
}

bool GetListElem(SxList *List)
{
	int i;
	for (i=0;i<(List->cnt);i++)
	{
		printf("第%d个元素值为:%d",i+1,List->pBase[i]);
	}
	 return true;
}

void main(void)
{
	
	SxList List;
	InitList(&List,6);
	InsertList(&List,1,1);
	InsertList(&List,2,2);
	InsertList(&List,1,3);
	InsertList(&List,2,4);
	GetListElem(&List);
	DeleteList(&List);
}