#include "hannan.h"
#include "haxi.h"

int sumup(char *s)
{
	int sum = 0;

	for(int i=0; i<strlen(s); i++)
	{
		sum += s[i];
	}

	return sum;
}

bool is_primery(int n)
{
	for(int k=2; k*k<=n; k++)
	{
		if(n%k == 0)
			return false;
	}
	return true;
}

int primery(int max)
{
	if(max <= 1)
		return -1;

	for(int i=max; i>0; i--)
	{
		if(is_primery(i))
			return i;
	}
}


hash_table init_hash(int cap)
{
	if(cap <= 0)
		return NULL;

	hash_table ht = calloc(1, sizeof(*ht));
	if(ht != NULL)
	{
		ht->table    = calloc(cap, sizeof(hashnode *));
		if(ht->table == NULL)
		{
			free(ht);
			return NULL;
		}
		ht->capacity = cap;
		ht->primery  = primery(cap); // 不超过容量的最大素数
		printf("素数: %d\n", ht->primery);
	}
	return ht;
}

void hash_add(char *s, hash_table ht)
{
	// 新建一个节点，存入数据s
	hashnode *new = calloc(1, sizeof(hashnode));
	if(new != NULL)
	{
		new->data = s;
		new->next = NULL;
	}

	// 1，使用除留余数法，获得哈希地址
	int haddr = sumup(s) % ht->primery;
	//printf("sumup: %d\n", sumup(s));
	printf("位置为: %d\n", haddr);

	if(ht->table[haddr] == NULL)
	{
		// 将新节点置入哈希表
		ht->table[haddr] = new;
	}
	else
	{
		// 2，使用链地址法，解决冲突
		hashnode *tmp;
		for(tmp=ht->table[haddr]; tmp->next!=NULL; tmp=tmp->next);
		tmp->next = new;
	}
}

int hash_search(char *s, hash_table ht)
{
	// 1，使用除留余数法，获得哈希地址
	int haddr = sumup(s) % ht->primery;

	// 2，使用链地址法，查找冲突链表
	hashnode *tmp;
	for(tmp=ht->table[haddr]; tmp!=NULL; tmp=tmp->next)
	{
		if(!strcmp(tmp->data, s))
			return haddr;
	}
	return -1;
}
