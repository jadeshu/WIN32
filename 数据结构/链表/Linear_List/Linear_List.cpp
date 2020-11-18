#include <iostream>
using namespace std;
typedef int ElemType;
typedef struct
{
	ElemType *pBase;
	int MAXSIZE;
	int cnt;
}SxList;

bool ClearList(SxList *List);    //������Ա�����
bool LengthList(SxList *List,int *length,int *cnt);   //��ȡ�б��ܳ��ȱ���length�У�ʵ����Ч����Ϊcnt��
bool InitList(SxList *List,int length);	//��ʼ�����Ա� lengthΪҪ����Ŀռ��С  ,��ʼ����������DeleteList
bool GetElem(SxList *List,int i,ElemType *e); //��ȡָ��i������Ԫ�ز������ڻ�����e��
bool InsertList(SxList *List,int i,ElemType e);  //��������i��Ԫ��e
bool DeleteList(SxList *List); //ɾ���������Ա�
bool DeleteElemList(SxList *List,int i,ElemType *e);  //ɾ������i��Ԫ�ز�����ɾ�������ݱ�����e��
bool EmptyList(SxList *List);  //��ǰ�б��Ƿ�Ϊ��  �շ���TRUE���򷵻�FALSE
bool GetListElem(SxList *List,SxList *L1);


bool InitList(SxList *List,int length)   //��ʼ�����Ա�
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

bool EmptyList(SxList *List) //��ǰ�б��Ƿ�Ϊ��  �շ���TRUE���򷵻�FALSE
{
	return (List->cnt==0)?true:false;
}

bool DeleteList(SxList *List) //ɾ���������Ա�
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
		printf("��%d��Ԫ��ֵΪ:%d",i+1,List->pBase[i]);
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