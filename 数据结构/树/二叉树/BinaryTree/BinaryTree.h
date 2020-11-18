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
		T				data;	//数据
		struct BinTreeNodeTag	*lChild;	//左
		struct BinTreeNodeTag	*rChild;	//右
	}Node, *pNode;

	pNode CreateNode(T data)
	{
		pNode newNode = new Node();
		newNode->data = data;
		newNode->lChild = nullptr;
		newNode->rChild = nullptr;
		return newNode;
	}

	// lf_rh true是往parentNode左子节点添加
    // lf_rh false是往parentNode右子节点添加
	pNode AddTreeNode(pNode parentNode,T data, bool lf_rh = true) 
	{
	
		pNode newNode = this->CreateNode(data);
		if ((parentNode != nullptr) && (newNode != nullptr))
		{
			if (lf_rh)
			{
				if (parentNode->lChild != nullptr)
				{
					printf("左子树结点不为空\r\n");
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
					printf("左子树结点不为空\r\n");
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

	// 先序遍历
	void PreOrder(pNode root)
	{

		if ((root != nullptr) && (this->root != nullptr))
		{
			// 暂时打印为数值型
			printf("%c\r\n", root->data);
			PreOrder(root->lChild);
			PreOrder(root->rChild);
		}
	}

	// 中序遍历
	void OverOrder(pNode root)
	{
		if ((root != nullptr) && (this->root != nullptr))
		{
			OverOrder(root->lChild);
			// 暂时打印为数值型
			printf("%c\r\n", root->data);
			OverOrder(root->rChild);
		}
	}

	// 后序遍历
	void PostOrder(pNode root)
	{
		if ((root != nullptr) && (this->root != nullptr))
		{
			PostOrder(root->lChild);
			PostOrder(root->rChild);
			// 暂时打印为数值型
			printf("%c\r\n", root->data);
		}
	}


	void SetRoot(pNode node)
	{
		this->root = node;
	}


private:
	int size;	//节点个数
	pNode root;		//根节点
};

#endif