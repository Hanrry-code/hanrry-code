#ifndef _HAXI_H_
#define _HAXI_H_
#include "hannan.h"
//哈希表的节点
typedef struct node
{
	char *data;
	struct node *next;
}hashnode;


// 哈希表管理结构体
typedef struct
{
	hashnode **table; // 指向哈希表入口
	int capacity;    // 哈希表总容量

	int primery; // 除留余数法最大素数
}*hash_table;
hash_table init_hash(int cap);
int sumup(char *s);
void hash_add(char *s, hash_table ht);
int hash_search(char *s, hash_table ht);
bool is_primery(int n);
#endif