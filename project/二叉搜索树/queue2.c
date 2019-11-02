#include "queue2.h"
#include "hannan.h"

// 入队
void en_queue2(struct node2 *new, linkqueue2 q)
{
	if(is_empty2(q))
	{
		q->front = q->tail = new;
	}
	else
	{
		q->tail->next = new;
		q->tail = new;
	}

	q->size++;
}

// 出队
// 成功：返回队头节点指针
// 失败：返回NULL
struct node2 *out_queue2(linkqueue2 q)
{
	if(is_empty2(q))
		return NULL;

	if(q->size == 1)
		q->tail = NULL;

	struct node2 *tmp = q->front;
	q->front = q->front->next;
	q->size--;
	tmp->next = NULL;

	return tmp;
}

// 判断是否是空队列
bool is_empty2(linkqueue2 q)
{
	return q->size == 0;
}

// 初始化一个空队列
linkqueue2 init_queue2()
{
	// 分配一个管理结构体
	linkqueue2 q = calloc(1, sizeof(queue2));

	q->front = q->tail = NULL;
	q->size = 0;
}

// 遍历队列元素
void travel2(linkqueue2 q, void (*func)(void *))
{
	struct node2 *tmp;
	for(tmp=q->front; tmp!=NULL; tmp=tmp->next)
	{
		// 处理tmp指向的节点
		func(&tmp->data);
	}
}


// 获取队列当前元素个数


// 销毁队列


