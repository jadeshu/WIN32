#include <stdio.h>
#include "JxList.h"

////////////////////////////////////////////////////////////////////////
//单链表
////////////////////////////////////////////////////////////////////////

//链表节点
struct ListNode 
{
	void*		pData;	//要存储的数据
	ListNode*	pNext;	//指向下一个节点
};

struct OnlyList
{
	OnlyList():pHead(nullptr),nSize(0)
	{
	}
	ListNode* pHead;			//添加一个头指针，方便操作
	unsigned int nSize;			//链表节点有效个数,方便知道总共有多少个节点
};

//增加元素
////////////////////////////////////////////////////////////////////////////////////////////////////
//往链表中添加数据,默认从头插入，即头插法
//1.链表需要已经存在的
//2.数据需要已经存在的
bool AddOnlyListBeginEle(OnlyList* pList, void* pdata)
{
	//List和data任意一个为空则什么也不做
	if (pList==nullptr || pdata == nullptr)
	{
		return false;
	}
	//创建一个新的节点
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
	//复制数据指针变量
	pNewNode->pData = pdata;

	//把链表头指针赋给新节点的下一个节点的指针
	pNewNode->pNext = pList->pHead;
	//把新节点的指针赋给链表的头指针
	pList->pHead = pNewNode;

	//链表节点增加一个
	pList->nSize++;	
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//删除元素
////////////////////////////////////////////////////////////////////////////////////////////////////
//删除链表中的首元素
bool DelOnlyListBeginEle(OnlyList* pList)
{
	if (pList == nullptr ||pList->nSize == 0 /*|| pList->pHead == nullptr*/)
	{
		return false;
	}
	//临时储存链表的头指针
	ListNode* pOldNode = pList->pHead;
	//把链表的头指针所指向的下一个节点指针复制链表的头指针
	pList->pHead = pOldNode->pNext;
	//有效个数减一
	pList->nSize--;

	//释放空间
	//pTmp->pNext = nullptr;
	free(pOldNode);
	return true;
}

//删除链表中的尾元素
bool DelOnlyListEndEle(OnlyList* pList)
{
	if (pList == nullptr ||pList->nSize == 0 /*|| pList->pHead == nullptr*/)
	{
		return false;
	}
	
	//////////////////////////////////////////////////////////////////////////
	//找到尾结点
	//////////////////////////////////////////////////////////////////////////
	ListNode* pTmpEndNode = pList->pHead;
	ListNode* pTmpPreEndNode = pTmpEndNode;
	//判断是否为空，不为空则循环，直到找到尾节点结束
	while (pTmpEndNode->pNext)	//查找节点的下一个节点指针是否为NULL
	{
		pTmpPreEndNode =  pTmpEndNode;			//存储本次循环节点,直到找到尾结点,即时尾结点的前一个节点
		pTmpEndNode   =  pTmpEndNode->pNext;	//存储本次循环节点的下一个节点指针，直到找到尾结点
	}
	///第一种方法---------------------------------------
	//把倒数第二个下一个指针域赋值为nullptr
	//释放尾结点空间
	free(pTmpPreEndNode->pNext);
	//free(pTmpEndNode);

	pTmpPreEndNode->pNext = nullptr;
	//有效个数减一
	pList->nSize--;

	//当只有一个有效元素时
	if (pList->nSize == 0)
	{
		pList->pHead = nullptr;
	}
	return true;
}

//在链表中删除指定索引的一个元素
bool DelOnlyListEleByIndex(OnlyList* pList,unsigned int index)		//index索引从1开始
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

	//当只有一个有效元素时
	if (pList->nSize == 0)
	{
		pList->pHead = nullptr;
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//修改元素
////////////////////////////////////////////////////////////////////////////////////////////////////
//在链表中修改指定索引的一个元素
bool UpdateOnlyListEleByIndex(OnlyList* pList,unsigned int index,void* data)		//index索引从1开始
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
	//赋值数据，把指针地址给改变了
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
		printf("第%d个元素是：%d\n",i,ret);
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