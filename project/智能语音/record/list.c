#include "list.h"
#include "hannan.h"
struct node *init_list()
{

	struct node *head = calloc(1, sizeof(struct node));
	if(head != NULL)
	{
		
		INIT_LIST_HEAD(&head->list);
	}

	return head;
}
void show(struct node* head)
{
	struct list_head *pos;
	struct node *p;
	//�����ں�����
	list_for_each(pos,&head->list)
	{
		p=list_entry(pos,struct node,list);
		printf("%s\t",p->music_path);
	}
	printf("\n");
}
struct node *new_node()
{
	struct node *new = calloc(1, sizeof(struct node));
	if(new != NULL)
	{
		new->music_path[20];


		// ���½ڵ��ڲ���С�ṹ���Լ�ָ���Լ�
		INIT_LIST_HEAD(&new->list);
	}

	return new;
}
