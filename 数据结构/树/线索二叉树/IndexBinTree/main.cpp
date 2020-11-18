#include <stdio.h>
#include <tchar.h>
#include <malloc.h>

typedef TCHAR EChar;

typedef struct _BinTreeNode
{
	EChar data;
	bool ltag;		//false时指向孩子，true时是表示前驱后继线索
	bool rtag;
	struct _BinTreeNode *lChild;
	struct _BinTreeNode *rChild;
}BinTreeNode,*BinTree;

void createBinTree(BinTree *T)
{
	EChar c;
	_tscanf(_T("%c"),&c);

	if (c == _T(' '))
	{
		*T = nullptr;
	}
	else
	{
		*T = (BinTree)malloc(sizeof(BinTreeNode));
		(*T)->data = c;
		(*T)->ltag = (*T)->rtag = false;
		
		createBinTree(&((*T)->lChild));
		createBinTree(&((*T)->rChild));
	}
}
int main()
{
	BinTree r;
	createBinTree(&r);
 	return 0;
}