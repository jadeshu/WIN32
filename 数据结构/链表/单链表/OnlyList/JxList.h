/************************************************************************/
/* ���˵�������ϰ                                                       */
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
		T				pData;		//����
		struct _Node*	pNext;		//ǰ��ָ��
		struct _Node*	pPre;		//����ָ��
	}Node;
public:
	CJxList(void):m_nSize(0),m_pHead(nullptr),m_pTail(nullptr)
	{
	}

	~CJxList()
	{

	}

	//��ͷ��������
	bool AddBeginEle(T pdata)
	{
		//����һ���µĽڵ�
		Node* pNewNode = (Node*)malloc(sizeof(Node));

		//��������ָ�����
		pNewNode->pData = pdata;
		//���½ڵ�Ԫ�ص�ǰ��ָ��Ϊ��
		pNewNode->pPre = nullptr;

		//������ͷָ�븳���½ڵ����һ���ڵ��ָ��
		pNewNode->pNext = m_pHead;

		//�ѽڵ㸳��ͷָ��
		if (m_nSize == 0)
		{
			m_pTail = pNewNode;

		}
		else
		{
			m_pHead->pPre = pNewNode;
		}

		//���½ڵ��ָ�븳�������ͷָ��
		m_pHead = pNewNode;
		//����ڵ�����һ��
		m_nSize++;

		return true;
	}

	//ɾ�������ݲ�����ɾ������ֵ
	T	DelBeginEle()
	{
		if (m_nSize == 0 /*|| m_pHead == nullptr*/)
		{
			return false;
		}
	
		//��ʱ���������ͷָ��
		Node* pOldNode = m_pHead;
		//�������ͷָ����ָ�����һ���ڵ�ָ�븴�������ͷָ��
		m_pHead = pOldNode->pNext;
		if (m_nSize == 1)
		{
			m_pTail = nullptr;
		}
		else
		{
			m_pHead->pPre = nullptr;
		}
		
		//��Ч������һ
		m_nSize--;
	
		//�ͷſռ�
		//pTmp->pNext = nullptr;	//���п���
		T ret = pOldNode->pData;
		free(pOldNode);
		return ret;
	}

	//ɾ�������е�βԪ��
	T	DelEndEle()
	{
		if (m_nSize == 0 /*|| m_pHead == nullptr*/)
		{
			return false;
		}
		//��ʱ���������ͷָ��
		Node* pOldTail = m_pTail;
		m_pTail = pOldTail->pPre;

		//��Ч������һ
		m_nSize--;

		//�ͷſռ�
		//pTmp->pNext = nullptr;
		T ret = pOldTail->pData;
		free(pOldTail);
		return ret;
	}

	//ָ�������޸�һ������
	bool UpdataEleByIndex(unsigned int index,T data)		//index������1��ʼ
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
		//��ֵ����
		pTmpEndNode->pData = data;
		return true;
	}

	//ָ��������������
	T FindEleByIndex(unsigned int index)		//index������1��ʼ
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
		//��ֵ����
		return pTmpEndNode->pData;
	} 

	/*�����ݽڵ���Ϊ�ձ��ͷ�ԭ�ڵ�ռ�*/  
	void Clear()
	{
		Node* pTmpNext = m_pHead;	//��ʱ�ڵ�ָ��
		Node* pDelNode = m_pHead;	//ɾ���ڵ�ָ��
		while (pTmpNext!=m_pTail)
		{
			//������ʱ�ڵ�
			pDelNode = pTmpNext;
			//����ʱ�ڵ����һ���ڵ�ָ�뱣��
			pTmpNext = pTmpNext->pNext;
			//�ͷ��ڴ�
			free(pDelNode);
			m_nSize--;
		}

		free(m_pTail);
		m_nSize--;

		m_pHead = nullptr;
		m_pTail = nullptr;
		//m_nSize = 0;
	}

	/*���������С*/  
	int GetSize()
	{
		return m_nSize;
	}

	//�ж��Ƿ�Ϊ��
	bool IsEmpty(){ return (m_nSize ? false : true); }

private:
	unsigned int	m_nSize;	//Ԫ�ظ���
	Node*			m_pHead;	//ͷָ��
	Node*			m_pTail;	//βָ��
};


#endif