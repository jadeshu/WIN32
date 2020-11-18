
#define MAX_TREE_NODE 100		//最大节点数, 即数组边界
#define MAX_TREE_DEGREE 3	//树的度
//////////////////////////////////////////////////////////////////////////
//实现是通过结构体的数组
//孩子表示法
//优点：求子节点方便
//数据重复
struct ChildTreeNode
{
	void *data;				//数据

	int childIndex[MAX_TREE_DEGREE];	//该节点的子节点(孩子节点)在数组中的索引
	//指向子节点的指针变量,无子节点为NULL，有则继续指向下一个新子节点
	//ChildTreeNode*  pChildNext;
};

struct ChildTree 
{
	ChildTreeNode treeNode[MAX_TREE_NODE];	//节点数组(所有节点集合)
	int nCount;							//有效节点个数
};
//////////////////////////////////////////////////////////////////////////

int main()
{
	return 0;
}