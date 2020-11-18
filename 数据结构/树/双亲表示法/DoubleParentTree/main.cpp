#include <stdio.h>

/************************************************************************/
/* 双亲表示法															*/
/************************************************************************/
//实现是通过结构体的数组
//优点：求根节点方便
#define MAX_TREE_NODE 100
struct ParentTreeNode
{
	void *data;		//数据
	//	无父节点为-1,其余位置号为数组的索引
	int  parentNum;	//双亲位于数组中的索引号
};

struct ParentTree 
{
	ParentTreeNode treeNode[MAX_TREE_NODE];	//节点数组(所有节点集合)
	int nCount;							//有效节点个数
};

//////////////////////////////////////////////////////////////////////////
//添加节点
void AddTreeNode(void *data)
{

}

//////////////////////////////////////////////////////////////////////////
//双亲孩子表示法
//优点：求父和子节点都很方面
//


//////////////////////////////////////////////////////////////////////////
int main()
{

	return 0;
}