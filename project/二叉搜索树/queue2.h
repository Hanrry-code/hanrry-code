#ifndef __QUEUE_H
#define __QUEUE_H

#include "hannan.h"

#ifndef LQ_NODE_TYPE
#define LQ_NODE_TYPE int // 队列节点数据默认int
#endif

typedef LQ_NODE_TYPE datatype;

// 队列节点
struct node2
{
	datatype data;
	struct node2 *next;
};


// 队列管理结构体
typedef struct 
{
	struct node2 *front;
	struct node2 *tail;

	int size;
}queue2, *linkqueue2;


void en_queue2(struct node2 *new, linkqueue2 q);
struct node2 *out_queue2(linkqueue2 q);
bool is_empty2(linkqueue2 q);
linkqueue2 init_queue2();

void travel2(linkqueue2 q, void (*func)(void *));
//                              钩子函数
//                              回调函数

#endif
