#include <stdio.h>
#include "JxList.h"

////////////////////////////////////////////////////////////////////////
//������
////////////////////////////////////////////////////////////////////////

//����ڵ�
struct ListNode 
{
	void*		pData;	//Ҫ�洢������
	ListNode*	pNext;	//ָ����һ���ڵ�
};

struct OnlyList
{
	OnlyList():pHead(nullptr),nSize(0)
	{
	}
	ListNode* pHead;			//���һ��ͷָ�룬�������
	unsigned int nSize;			//����ڵ���Ч����,����֪���ܹ��ж��ٸ��ڵ�
};

//����Ԫ��
////////////////////////////////////////////////////////////////////////////////////////////////////
//���������������,Ĭ�ϴ�ͷ���룬��ͷ�巨
//1.������Ҫ�Ѿ����ڵ�
//2.������Ҫ�Ѿ����ڵ�
bool AddOnlyListBeginEle(OnlyList* pList, void* pdata)
{
	//List��data����һ��Ϊ����ʲôҲ����
	if (pList==nullptr || pdata == nullptr)
	{
		return false;
	}
	//����һ���µĽڵ�
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
	//��������ָ�����
	pNewNode->pData = pdata;

	//������ͷָ�븳���½ڵ����һ���ڵ��ָ��
	pNewNode->pNext = pList->pHead;
	//���½ڵ��ָ�븳�������ͷָ��
	pList->pHead = pNewNode;

	//����ڵ�����һ��
	pList->nSize++;	
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//ɾ��Ԫ��
////////////////////////////////////////////////////////////////////////////////////////////////////
//ɾ�������е���Ԫ��
bool DelOnlyListBeginEle(OnlyList* pList)
{
	if (pList == nullptr ||pList->nSize == 0 /*|| pList->pHead == nullptr*/)
	{
		return false;
	}
	//��ʱ���������ͷָ��
	ListNode* pOldNode = pList->pHead;
	//�������ͷָ����ָ�����һ���ڵ�ָ�븴�������ͷָ��
	pList->pHead = pOldNode->pNext;
	//��Ч������һ
	pList->nSize--;

	//�ͷſռ�
	//pTmp->pNext = nullptr;
	free(pOldNode);
	return true;
}

//ɾ�������е�βԪ��
bool DelOnlyListEndEle(OnlyList* pList)
{
	if (pList == nullptr ||pList->nSize == 0 /*|| pList->pHead == nullptr*/)
	{
		return false;
	}
	
	//////////////////////////////////////////////////////////////////////////
	//�ҵ�β���
	//////////////////////////////////////////////////////////////////////////
	ListNode* pTmpEndNode = pList->pHead;
	ListNode* pTmpPreEndNode = pTmpEndNode;
	//�ж��Ƿ�Ϊ�գ���Ϊ����ѭ����ֱ���ҵ�β�ڵ����
	while (pTmpEndNode->pNext)	//���ҽڵ����һ���ڵ�ָ���Ƿ�ΪNULL
	{
		pTmpPreEndNode =  pTmpEndNode;			//�洢����ѭ���ڵ�,ֱ���ҵ�β���,��ʱβ����ǰһ���ڵ�
		pTmpEndNode   =  pTmpEndNode->pNext;	//�洢����ѭ���ڵ����һ���ڵ�ָ�룬ֱ���ҵ�β���
	}
	///��һ�ַ���---------------------------------------
	//�ѵ����ڶ�����һ��ָ����ֵΪnullptr
	//�ͷ�β���ռ�
	free(pTmpPreEndNode->pNext);
	//free(pTmpEndNode);

	pTmpPreEndNode->pNext = nullptr;
	//��Ч������һ
	pList->nSize--;

	//��ֻ��һ����ЧԪ��ʱ
	if (pList->nSize == 0)
	{
		pList->pHead = nullptr;
	}
	return true;
}

//��������ɾ��ָ��������һ��Ԫ��
bool DelOnlyListEleByIndex(OnlyList* pList,unsigned int index)		//index������1��ʼ
{
	if (pList == nullptr ||pList->nSize == 0 /*|| pList->pHead == nullptr*/)
	{
		return false;
	}

	ListNode* pTmpEndNode = pList->pHead;
	ListNode* pTmpPreEndNode = pTmpEndNode;
	for (unsigned int i=0; i< (index-1); i++)
	{
		pTmpPreEndNode = pTmpEndNode;
		pTmpEndNode = pTmpEndNode->pNext;
	}

	pTmpPreEndNode->pNext = pTmpEndNode->pNext;
	pList->nSize--;
	free(pTmpEndNode);

	//��ֻ��һ����ЧԪ��ʱ
	if (pList->nSize == 0)
	{
		pList->pHead = nullptr;
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//�޸�Ԫ��
////////////////////////////////////////////////////////////////////////////////////////////////////
//���������޸�ָ��������һ��Ԫ��
bool UpdateOnlyListEleByIndex(OnlyList* pList,unsigned int index,void* data)		//index������1��ʼ
{
	if (pList == nullptr ||pList->nSize == 0 /*|| pList->pHead == nullptr*/)
	{
		return false;
	}
	if (index > (pList->nSize) || index <= 0)
	{
		return false;
	}
	ListNode* pTmpEndNode = pList->pHead;
	for (unsigned int i=0; i< (index-1); i++)
	{
		pTmpEndNode = pTmpEndNode->pNext;
	}
	//��ֵ���ݣ���ָ���ַ���ı���
	pTmpEndNode->pData = data;
	return true;
}

int main()
{
	//OnlyList list;
	int a = 2;
	int b = 3;
	int c = 4;
	int d = 5;

	CJxList<int> lst;
	lst.AddBeginEle(a);
	lst.AddBeginEle(b);
	lst.AddBeginEle(c);
	lst.AddBeginEle(d);
	lst.UpdataEleByIndex(4,1000);
	for (int i=1;i<7;i++)
	{
		int ret = lst.FindEleByIndex(i);
		printf("��%d��Ԫ���ǣ�%d\n",i,ret);
	}
	//lst.DelEndEle(c);
	//lst.DelEndEle();
	//lst.AddBeginEle(c);
	//lst.AddBeginEle(d);
	//int i = lst.FindEleByIndex(2);
	//i = lst.FindEleByIndex(4);
	//i = lst.FindEleByIndex(10);
	//
	//lst.UpdataEleByIndex(1,1000);
	//AddOnlyListBeginEle(&list,&a);
	//AddOnlyListBeginEle(&list,&b);
	//AddOnlyListBeginEle(&list,&c);
	//AddOnlyListBeginEle(&list,&d);

	//bool ret = false;
	//int f = 100;
	//ret = UpdateOnlyListEleByIndex(&list,10,&f);
	//ret = UpdateOnlyListEleByIndex(&list,1,&f);
	//ret = DelOnlyListBeginEle(&list);
	//ret = DelOnlyListEndEle(&list);
	//ret = DelOnlyListEndEle(&list);
	//ret = DelOnlyListBeginEle(&list);
	//ret = DelOnlyListEle(&list,1);

	//ret = DelOnlyListBeginEle(&list);

	//ret = DelOnlyListBeginEle(&list);

	return 0;
}