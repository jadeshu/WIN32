
#define MAX_TREE_NODE	100		//���ڵ���, ������߽�
#define MAX_TREE_DEGREE 3		//���Ķ�
//////////////////////////////////////////////////////////////////////////
//ʵ����ͨ���ṹ�������
//˫�׺��ӱ�ʾ��
//�ŵ㣺��.�ӽڵ㷽��
struct ChildTreeNode
{
	int childIndex;			//�ӽڵ��������е�������
	ChildTreeNode *pNext;	//ָ����һ���ӽڵ�ָ��
};
struct TreeNode
{
	void *data;				//����
	int parentIndex;		//˫��λ�������е�������
	
	ChildTreeNode*  pChildNext;	//ָ���ӽڵ��ָ�����,���ӽڵ�ΪNULL���������ָ����һ�����ӽڵ�
	//int childIndex[MAX_TREE_DEGREE];	//�ýڵ���ӽڵ�(���ӽڵ�)�������е�����
};

struct ChildTree 
{
	TreeNode treeNode[MAX_TREE_NODE];	//�ڵ�����(���нڵ㼯��)
	int nCount;							//��Ч�ڵ����
};
//////////////////////////////////////////////////////////////////////////


int main()
{
	return 0;
}