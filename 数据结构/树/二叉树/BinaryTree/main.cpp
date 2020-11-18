#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

int main()
{
	CBinaryTree<char> bt;
	CBinaryTree<char>::pNode root = bt.CreateNode('A');
	bt.SetRoot(root);

	CBinaryTree<char>::pNode pB = bt.AddTreeNode(root, 'B');
	CBinaryTree<char>::pNode pC = bt.AddTreeNode(pB, 'C',false);
	CBinaryTree<char>::pNode pD = bt.AddTreeNode(pC, 'D');
	CBinaryTree<char>::pNode pE = bt.AddTreeNode(pC, 'E', false);
	CBinaryTree<char>::pNode pF = bt.AddTreeNode(root, 'F', false);
	CBinaryTree<char>::pNode pL = bt.AddTreeNode(pF, 'L');
	CBinaryTree<char>::pNode pM = bt.AddTreeNode(pF, 'M', false);
	CBinaryTree<char>::pNode pN = bt.AddTreeNode(pM, 'N');
	CBinaryTree<char>::pNode pQ = bt.AddTreeNode(pN, 'Q', false);
	bt.PreOrder(root);

	system("pause");
	return 0;
}