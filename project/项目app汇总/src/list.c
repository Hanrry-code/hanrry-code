#include "list.h"
#include "hannan.h"
struct node *init_list()
{

	struct node *head = calloc(1, sizeof(struct node));
	if(head != NULL)
	{
		//head->list.prev = &head->list;
		//head->list.next = &head->list;

		INIT_LIST_HEAD(&head->list);
	}

	return head;
}
void show(struct node* head)
{
	struct list_head *pos;
	struct node *p;
	//遍历内核链表
	list_for_each(pos,&head->list)
	{
		p=list_entry(pos,struct node,list);
		printf("%s\t",p->pic_path);
	}
	printf("\n");
}
struct node *new_node()
{
	struct node *new = calloc(1, sizeof(struct node));
	if(new != NULL)
	{
		new->k =0;
		new->rgb = NULL;
		new->width =0;
		new->height = 0;
		new->red = 0;
		new->green = 0;
		new->blue = 0;
		new->lcd = NULL;
		new->rgb_buf = NULL;	
		new->stride = 0;
		new->x = 0;
		new->y = 0;


		// 让新节点内部的小结构体自己指向自己
		INIT_LIST_HEAD(&new->list);
	}

	return new;
}
