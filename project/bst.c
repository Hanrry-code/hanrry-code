#include "common.h"

typedef struct node
{
	int data;

	struct node *lchild;
	struct node *rchild;

}treenode, *linktree;


// 将新节点new，插入到以root为根的二叉搜索树中
// 返回插入新节点之后，新的BST的根节点指针
linktree bst_insert(linktree new, linktree root)
{
	if(root == NULL)
	{
		return new;
	}

	// 插到左孩子中去
	if(new->data < root->data)
	{
		root->lchild = bst_insert(new, root->lchild);
	}

	// 插到右孩子中去
	else if(new->data > root->data)
	{
		root->rchild = bst_insert(new, root->rchild);
	}

	else
	{
		printf("%d已经存在！\n", root->data);
	}

	return root;
}

// 将以root为根的二叉树中的data节点删除
linklist bst_remove(int data, linktree root)
{
	if(root == NULL)
		return NULL;

	// 要删的节点，在树的左子树的某个位置
	if(data < root->data)
	{
		// 在左子树中删除可能存在的节点data，并更新左子树
		root->lchild = bst_remove(data, root->lchild)
	}

	// 要删的节点，在树的右子树的某个位置
	if(data > root->data)
	{
		// 在右子树中删除可能存在的节点data，并更新右子树
		root->rchild = bst_remove(data, root->rchild)
	}

	// 要删的就是root
	if(data == root->data)
	{
		// 1，有左子树
		if(root->lchild != NULL)
		{
			// a. 找到左子树中最大的节点lmax
			linktree lmax;
			for(lmax=root->lchild; lmax->rchild!=NULL;lmax=lmax->rchild);

			// b. 替换
			root->data = lmax->data;	

			// c. 删除左子树中的lmax
			root->lchild = bst_remove(lmax->data, root->lchild);
		}

		// 2，无左子树，但有右子树
		else if(root->rchild != NULL)
		{
			// a. 找到右子树中最小的节点rmin
			linktree rmin;
			for(rmin=root->rchild; rmin->lchild!=NULL; rmin=rmin->lchild);

			// b. 替换
			root->data = rmin->data;	

			// c. 删除右子树中的rmin
			root->rchild = bst_remove(rmin->data, root->rchild);
		}

		// 3，叶子节点
		else
		{
			free(root);
			return NULL;
		}
	}

	return root;
}

int main(void)
{
	// 空树
	struct node *root = NULL;


	// 循环地将一些数据插入BST中
	int n;
	while(1)
	{
		scanf("%d", &n);

		if(n == 0)
			break;

		if(n > 0)
		{
			linktree new = new_node(n);
			root = bst_insert(new, root);
		}
		else if(n < 0)
		{
			// 在二叉树root中将节点n删除
			// 删掉之后可能会改变root的指向（比如root指向NULL）
			// 因此需要返回值来更新root
			root = bst_remove(-n, root);
		}
	}

	// 显示这棵树
	draw(root);
}
