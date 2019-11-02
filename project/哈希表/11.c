#include "hannan.h"
#include "haxi.h"


//产生随机字符串
char *random_string(void)
{
	char *s = calloc(1, 19);

	char ch[] = {'a', 'A'};
	for(int i=0; i<5; i++)
	{
		s[i] = ch[rand()%2]+rand()%26;
	}

	printf("随机字符串: %s\n", s);
	return s;
}
void show(hash_table ht)
{
	printf("hash table:\n");
	printf("**********************");
	printf("======================");
	for(int i = 0;i<ht->capacity;i++)
	{
		printf("【%02d】", i);
		for(hashnode *tmp=ht->table[i]; tmp!=NULL; tmp=tmp->next)
		{
			printf("--> \"%s\" ", tmp->data);
		}
		printf("\n");
	}
	printf("======================\n");
	printf("**********************\n");
}
int main(void)
{
	
	//创建一个容量不超过100的空哈希表
	hash_table ht = init_hash(50);
	//1.造表：将若干随机字符串放入哈希表中
	srand(time(NULL));
	for(int i=0; i<30; i++)
	{
		hash_add(random_string(), ht);
		
		printf("======================");
		show(ht);
		usleep(300*1000);
	}
	
	
	//2.查表：按要求查到所需字符串的位置
	while(1)
	{
		printf("你想要查询的字符串:");
		char s[20];
		bzero(s, 20);
		fgets(s, 20, stdin);

		int pos = hash_search(strtok(s, "\n"), ht);
		if(pos == -1)
		{
			printf("无此字符串，请重新输入.\n");
			continue;
		}

		printf("位置是【%d】\n", pos);
	}

	return 0;
}
