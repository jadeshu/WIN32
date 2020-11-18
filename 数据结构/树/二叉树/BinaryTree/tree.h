#ifndef __TREE_H__
#define __TREE_H__

typedef struct biTreeNode_ {
	void* data;
	struct biTreeNode_ *lchild;
	struct biTreeNode_ *rchild;
} biTreeNode;

typedef struct {
	unsigned int size;
	//void (*compare)(const void* key1, const void* key2);
	void (*destroy)(void *data);
	biTreeNode *root;
}BiTree;

#define bitree_size(tree) ((tree)->size)
#define bitree_root(tree) ((tree)->root)
#define bitree_data(node) ((node)->data) 
#define bitree_left(node) ((node)->lchild)
#define bitree_right(node) ((node)->rchild)


void 
bitree_init(BiTree *tree, void(*destroy)(void *data))
{
	tree->size = 0;
	tree->destroy = destroy;
	tree->root = nullptr;
}

void 
bitree_destroy(BiTree *tree)
{
	memset(tree, 0, sizeof(BiTree));
}

// node为NULL时，则新节点为根节点
// ERROR -1
// OK  0
int 
bitree_ins_left(BiTree *tree, biTreeNode *node, void *data)
{
	biTreeNode** position;
	if (node == nullptr)
	{
		if (bitree_size(tree) > 0)
		{
			return -1;
		}
		position = &(tree->root);
	}
	else 
	{
		if (bitree_left(node) !=  nullptr)
		{
			return -1;
		}
		position = &(node->lchild);
	}

	biTreeNode* new_node = (biTreeNode*)malloc(sizeof(biTreeNode));
	if (new_node == nullptr)
	{
		return -1;
	}

	new_node->data = data;
	new_node->lchild = new_node->rchild = nullptr;
	*position = new_node;

	tree->size++;
	return 0;
}

int
bitree_ins_right(BiTree *tree, biTreeNode *node, void *data)
{
	biTreeNode **position,*new_node;
	if (node == nullptr)
	{
		if (bitree_size > 0)
		{
			return -1;
		}
		position = &(tree->root);
	}
	else
	{
		if (bitree_right(node) != nullptr)
		{
			return -1;
		}
		position = &(node->rchild);
	}
	if ((new_node = (biTreeNode*)malloc(sizeof(biTreeNode))) == nullptr)
	{
		return -1;
	}

	new_node->data = data;
	new_node->lchild = new_node->rchild = nullptr;
	*position = new_node;
	tree->size++;
	return 0;
}


#endif