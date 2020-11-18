#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

template<typename T>
class CBinaryTree
{
public:
	CBinaryTree() :size(0), root(nullptr)
	{
	};
	typedef struct BinTreeNodeTag
	{
		T				data;	//����
		struct BinTreeNodeTag	*lChild;	//��
		struct BinTreeNodeTag	*rChild;	//��
	}Node, *pNode;

	pNode CreateNode(T data)
	{
		pNode newNode = new Node();
		newNode->data = data;
		newNode->lChild = nullptr;
		newNode->rChild = nullptr;
		return newNode;
	}

	// lf_rh true����parentNode���ӽڵ����
    // lf_rh false����parentNode���ӽڵ����
	pNode AddTreeNode(pNode parentNode,T data, bool lf_rh = true) 
	{
	
		pNode newNode = this->CreateNode(data);
		if ((parentNode != nullptr) && (newNode != nullptr))
		{
			if (lf_rh)
			{
				if (parentNode->lChild != nullptr)
				{
					printf("��������㲻Ϊ��\r\n");
				}
				else
				{
					parentNode->lChild = newNode;
				}
			}
			else
			{
				if (parentNode->rChild != nullptr)
				{
					printf("��������㲻Ϊ��\r\n");
				}
				else
				{
					parentNode->rChild = newNode;
				}
			}
			return newNode;
		}

		return nullptr;
	}

	// �������
	void PreOrder(pNode root)
	{

		if ((root != nullptr) && (this->root != nullptr))
		{
			// ��ʱ��ӡΪ��ֵ��
			printf("%c\r\n", root->data);
			PreOrder(root->lChild);
			PreOrder(root->rChild);
		}
	}

	// �������
	void OverOrder(pNode root)
	{
		if ((root != nullptr) && (this->root != nullptr))
		{
			OverOrder(root->lChild);
			// ��ʱ��ӡΪ��ֵ��
			printf("%c\r\n", root->data);
			OverOrder(root->rChild);
		}
	}

	// �������
	void PostOrder(pNode root)
	{
		if ((root != nullptr) && (this->root != nullptr))
		{
			PostOrder(root->lChild);
			PostOrder(root->rChild);
			// ��ʱ��ӡΪ��ֵ��
			printf("%c\r\n", root->data);
		}
	}


	void SetRoot(pNode node)
	{
		this->root = node;
	}


private:
	int size;	//�ڵ����
	pNode root;		//���ڵ�
};

#endif