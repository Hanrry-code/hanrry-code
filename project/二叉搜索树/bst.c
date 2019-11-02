#include "head4tree.h"
#include "drawtree.h"

#define LQ_NODE_TYPE linktree
#include "queue2.h"

linktree bst_insert(linktree root, linktree new)
{
	if(new == NULL)
		return root;

	if(root == NULL)
		return new;

	if(new->data > root->data)
	{
		root->rchild = bst_insert(root->rchild, new);
	}
	else if(new->data < root->data)
	{
		root->lchild = bst_insert(root->lchild, new);
	}
	else
	{
		printf("%ld is already exist.\n", new->data);
	}

	return root;
}

/*
linktree bst_find(linktree root, tn_datatype data)
{
	if(root == NULL)
		return NULL;

	if(data < root->data)
		return bst_find(root->lchild, data);
	else if(data > root->data)
		return bst_find(root->rchild, data);
	else
		return root;
}
*/

linktree bst_remove(linktree root, tn_datatype n)
{
	if(root == NULL)
		return NULL;

	if(n < root->data)
		root->lchild = bst_remove(root->lchild, n);
	else if(n > root->data)
		root->rchild = bst_remove(root->rchild, n);
	else
	{
		linktree tmp;
		if(root->lchild != NULL)
		{
			for(tmp=root->lchild; tmp->rchild!=NULL;
			    tmp=tmp->rchild);

			root->data = tmp->data;
			root->lchild = bst_remove(root->lchild, tmp->data);
		}
		else if(root->rchild != NULL)
		{
			for(tmp=root->rchild; tmp->lchild!=NULL;
			    tmp=tmp->lchild);

			root->data = tmp->data;
			root->rchild = bst_remove(root->rchild, tmp->data);
		}
		else
		{
			free(root);
			return NULL;
		}
	}
	return root;
}

void travel_mid(linktree root)
{
	if(root == NULL)
		return;
	travel_mid(root->lchild);
	travel_mid(root->rchild);
}

void travel_pos(linktree root)
{
	if(root == NULL)
		return;
	printf("%ld\t", root->data);
	travel_pos(root->lchild);
	travel_pos(root->rchild);
}

void travel_pre(linktree root)
{
	if(root == NULL)
		return;

	printf("%ld\t", root->data);
	travel_pre(root->lchild);
	travel_pre(root->rchild);
}


// 创建一个新的队列节点，用来存放BST节点指针
struct node2 *new_node2(linktree p)
{
	struct node2* new = calloc(1, sizeof(struct node2));
	if(new != NULL)
	{
		new->data = p;
		new->next = NULL;
	}
	return new;
}
// 按层遍历
void travel_level(linktree root)
{
	if(root == NULL)
		return;

	// 初始化一个专门用来存放BST节点指针的空队列
	linkqueue2 q = init_queue2();

	struct node2 *new = new_node2(root);
	en_queue2(new, q);

	struct node2 *tmp;
	while(!is_empty2(q))
	{
		tmp = out_queue2(q);

		printf("%ld\n", tmp->data->data);

		if(tmp->data->lchild != NULL)
		{
			struct node2 *new = new_node2(tmp->data->lchild);
			en_queue2(new, q);
		}
		if(tmp->data->rchild != NULL)
		{
			struct node2 *new = new_node2(tmp->data->rchild);
			en_queue2(new, q);
		}
	}
}



int main(void)
{
	linktree root;
	root = NULL;

	printf("输入大于0的数插入节点\n");
	printf("输入小于0的数删除节点\n");
	printf("输入0退出程序\n");

	int n;
	while(1)
	{
		scanf("%d", &n);

		if(n > 0)
		{
			// 创建一个新的BST的节点
			linktree new = new_node(n);
			root = bst_insert(root, new);
		}
		
		else if(n < 0)
		{
			root = bst_remove(root, -n);
		}
		
		if(n == 0)
			break;

		// 画一个网页显示二叉树的样子
		draw(root);
	}

	// 用火狐打开网页看看
	system("firefox *.html &");

	// 以不同的方式遍历二叉树
	//travel_pre(root); // 先
	//travel_mid(root); // 中
	//travel_pos(root); // 后

	travel_level(root); // 按层遍历

	return 0;
}
