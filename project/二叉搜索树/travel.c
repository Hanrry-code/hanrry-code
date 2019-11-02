#include "commonheader.h"
#include "head4tree.h"

#define QUEUE_NODE_DATATYPE linktree
#include "head4queue.h"

void pre_travel(linktree root, void (*handler)(linktree))
{
	if(root == NULL)
		return;
	
	handler(root);
	pre_travel(root->lchild, handler);
	pre_travel(root->rchild, handler);
}

void mid_travel(linktree root, void (*handler)(linktree))
{
	if(root == NULL)
		return;
	
	mid_travel(root->lchild, handler);
	handler(root);
	mid_travel(root->rchild, handler);
}

void post_travel(linktree root, void (*handler)(linktree))
{
	if(root == NULL)
		return;

	post_travel(root->lchild, handler);
	post_travel(root->rchild, handler);
	handler(root);
}

void level_travel(linktree root, void (*handler)(linktree))
{
	if(root == NULL)
		return;

	linkqueue q;
	q = init_queue();

	en_queue(q, root);

	linktree tmp;
	while(1)
	{
		if(!out_queue(q, &tmp))
			break;

		handler(tmp);

		if(tmp->lchild != NULL)
			en_queue(q, tmp->lchild);
		if(tmp->rchild != NULL)
			en_queue(q, tmp->rchild);
	}
}
