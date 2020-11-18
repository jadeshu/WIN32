
#define MAX_TREE_NODE	100		//最大节点数, 即数组边界
#define MAX_TREE_DEGREE 3		//树的度
//////////////////////////////////////////////////////////////////////////
//实现是通过结构体的数组
//双亲孩子表示法
//优点：求父.子节点方便
struct ChildTreeNode
{
	int childIndex;			//子节点在数组中的索引号
	ChildTreeNode *pNext;	//指向下一个子节点指针
};
struct TreeNode
{
	void *data;				//数据
	int parentIndex;		//双亲位于数组中的索引号
	
	ChildTreeNode*  pChildNext;	//指向子节点的指针变量,无子节点为NULL，有则继续指向下一个新子节点
	//int childIndex[MAX_TREE_DEGREE];	//该节点的子节点(孩子节点)在数组中的索引
};

struct ChildTree 
{
	TreeNode treeNode[MAX_TREE_NODE];	//节点数组(所有节点集合)
	int nCount;							//有效节点个数
};
//////////////////////////////////////////////////////////////////////////


int main()
{
	return 0;
}