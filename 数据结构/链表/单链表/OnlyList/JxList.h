/************************************************************************/
/* 个人单链表练习                                                       */
/************************************************************************/
#ifndef _JXLIST_H_
#define _JXLIST_H_

#include <stdlib.h>

template<typename T>
class CJxList
{
protected:
	typedef struct _Node
	{
		T				pData;		//数据
		struct _Node*	pNext;		//前驱指针
		struct _Node*	pPre;		//后驱指针
	}Node;
public:
	CJxList(void):m_nSize(0),m_pHead(nullptr),m_pTail(nullptr)
	{
	}

	~CJxList()
	{

	}

	//在头增加数据
	bool AddBeginEle(T pdata)
	{
		//创建一个新的节点
		Node* pNewNode = (Node*)malloc(sizeof(Node));

		//复制数据指针变量
		pNewNode->pData = pdata;
		//把新节点元素的前驱指针为空
		pNewNode->pPre = nullptr;

		//把链表头指针赋给新节点的下一个节点的指针
		pNewNode->pNext = m_pHead;

		//把节点赋给头指针
		if (m_nSize == 0)
		{
			m_pTail = pNewNode;

		}
		else
		{
			m_pHead->pPre = pNewNode;
		}

		//把新节点的指针赋给链表的头指针
		m_pHead = pNewNode;
		//链表节点增加一个
		m_nSize++;

		return true;
	}

	//删除首数据并返回删除的数值
	T	DelBeginEle()
	{
		if (m_nSize == 0 /*|| m_pHead == nullptr*/)
		{
			return false;
		}
	
		//临时储存链表的头指针
		Node* pOldNode = m_pHead;
		//把链表的头指针所指向的下一个节点指针复制链表的头指针
		m_pHead = pOldNode->pNext;
		if (m_nSize == 1)
		{
			m_pTail = nullptr;
		}
		else
		{
			m_pHead->pPre = nullptr;
		}
		
		//有效个数减一
		m_nSize--;
	
		//释放空间
		//pTmp->pNext = nullptr;	//可有可无
		T ret = pOldNode->pData;
		free(pOldNode);
		return ret;
	}

	//删除链表中的尾元素
	T	DelEndEle()
	{
		if (m_nSize == 0 /*|| m_pHead == nullptr*/)
		{
			return false;
		}
		//临时储存链表的头指针
		Node* pOldTail = m_pTail;
		m_pTail = pOldTail->pPre;

		//有效个数减一
		m_nSize--;

		//释放空间
		//pTmp->pNext = nullptr;
		T ret = pOldTail->pData;
		free(pOldTail);
		return ret;
	}

	//指定索引修改一个数据
	bool UpdataEleByIndex(unsigned int index,T data)		//index索引从1开始
	{
		if (index > (m_nSize) || m_nSize <= 0)
		{
			return false;
		}
		Node* pTmpEndNode = m_pHead;
		for (unsigned int i=0; i< (index-1); i++)
		{
			pTmpEndNode = pTmpEndNode->pNext;
		}
		//赋值数据
		pTmpEndNode->pData = data;
		return true;
	}

	//指定索引查找数据
	T FindEleByIndex(unsigned int index)		//index索引从1开始
	{
		if (index > (m_nSize) || index <= 0)
		{
			return (T)0;
		}
		Node* pTmpEndNode = m_pHead;
		for (unsigned int i=0; i< (index-1); i++)
		{
			pTmpEndNode = pTmpEndNode->pNext;
		}
		//赋值数据
		return pTmpEndNode->pData;
	} 

	/*将数据节点置为空表，释放原节点空间*/  
	void Clear()
	{
		Node* pTmpNext = m_pHead;	//临时节点指针
		Node* pDelNode = m_pHead;	//删除节点指针
		while (pTmpNext!=m_pTail)
		{
			//保存临时节点
			pDelNode = pTmpNext;
			//将临时节点的下一个节点指针保存
			pTmpNext = pTmpNext->pNext;
			//释放内存
			free(pDelNode);
			m_nSize--;
		}

		free(m_pTail);
		m_nSize--;

		m_pHead = nullptr;
		m_pTail = nullptr;
		//m_nSize = 0;
	}

	/*返回链表大小*/  
	int GetSize()
	{
		return m_nSize;
	}

	//判断是否为空
	bool IsEmpty(){ return (m_nSize ? false : true); }

private:
	unsigned int	m_nSize;	//元素个数
	Node*			m_pHead;	//头指针
	Node*			m_pTail;	//尾指针
};


#endif