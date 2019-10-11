#ifndef _LIST_H_
#define _LIST_H_
#include "hannan.h"
#include "kernel_list.h"
// 定义大结构体
struct node
{	
	
	char music_path[20];


	struct list_head list;
};
struct node *init_list();
struct node *new_node();
void show(struct node* head);
#endif
