
#define MAX_TREE_NODE 100		//���ڵ���, ������߽�
#define MAX_TREE_DEGREE 3	//���Ķ�
//////////////////////////////////////////////////////////////////////////
//ʵ����ͨ���ṹ�������
//���ӱ�ʾ��
//�ŵ㣺���ӽڵ㷽��
//�����ظ�
struct ChildTreeNode
{
	void *data;				//����

	int childIndex[MAX_TREE_DEGREE];	//�ýڵ���ӽڵ�(���ӽڵ�)�������е�����
	//ָ���ӽڵ��ָ�����,���ӽڵ�ΪNULL���������ָ����һ�����ӽڵ�
	//ChildTreeNode*  pChildNext;
};

struct ChildTree 
{
	ChildTreeNode treeNode[MAX_TREE_NODE];	//�ڵ�����(���нڵ㼯��)
	int nCount;							//��Ч�ڵ����
};
//////////////////////////////////////////////////////////////////////////

int main()
{
	return 0;
}