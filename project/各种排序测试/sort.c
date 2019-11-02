#include "hannan.h"

int comp_count = 0; // 数据比较次数
int swap_count = 0; // 数据交换次数
//将读取到的数据打印出来
void show(int data[], int len)
{
	int i;
	for(i=0; i<len; ++i)
	{
		printf("%d\t", data[i]);
	}
	printf("\n");
}

//实现两个数的位置交换
void swap(int *a, int *b)
{
	swap_count++;

	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
//选择排序法(找出最小的数 并依次进行交换)
void selection_sort(int data[], int len)
{
	for(int i=0; i<len; i++)
	{
		int min=i;

		for(int j=i+1; j<len; j++)
		{
			comp_count++;
			if(data[j] < data[min])
				min = j;
		}

		swap(&data[i], &data[min]);
	}
}
//冒泡排序
void bubble_sort(int data[], int len)
{
	int k=0;
	while(1)
	{
		bool done = true;

		int i;
		for(i=0; i<len-1-k; i++)
		{
			comp_count++;

			if(data[i] <= data[i+1])
			{
				continue;
			}
		
			swap(&data[i], &data[i+1]);
			done = false;
		}

		if(done)
			break;
		k++;
	}
}


int partition(int data[], int len)
{
	if(len <= 1)
		return 0;

	int i = 0;
	int j = len-1;
	while(i < j)
	{
		// 从右向左比较，顺序j--，逆序交换
		comp_count++;
		while(data[i]<=data[j] && i<j)
			j--;
		swap(&data[i], &data[j]);

		// 从左向右比较，顺序i++，逆序交换
		comp_count++;
		while(data[i]<=data[j] && i<j)
			i++;
		swap(&data[i], &data[j]);
	}

	return i;
}
//快速排序法
void quick_sort(int data[], int len)
{
	if(len <= 1)
		return;

	int pivot = partition(data, len);

	quick_sort(data, pivot);
	quick_sort(data+pivot+1, len-pivot-1);
}

//插入排序法
void insertion_sort(int data[], int len)
{
	if(len <= 1)
		return;

	int i, j;
	for(i=1; i<len; i++)
	{
		int tmp = data[i];

		for(j=i-1; j>=0; j--)
		{
			comp_count++;
			if(data[j] < tmp)
			{
				break;
			}
			else
			{
				swap_count++;
				data[j+1] = data[j];
			}
		}
		swap_count++;
		data[j+1] = tmp;
	}
}



//合并文件
void merge(int begin, int end)
{
	if(end - begin <= 0)
		return;

	// 将 begin+1 ... end 全部合并成 begin+1
	merge(begin+1, end);

	// 从begin.txt和begin+1.txt，每次读取一行
	// 将最小的放到一个临时文件中
	 printf("正在合并%d.txt + %d.txt ...\n", begin, begin+1);

	// 根据文件的命名，准备好两个待合并的文件名
	char f1[10];
	char f2[10];
	bzero(f1, 10);
	bzero(f2, 10);

	snprintf(f1, 10, "%d.txt", begin);
	snprintf(f2, 10, "%d.txt", begin+1);
	
	FILE *fp1 = fopen(f1, "r");
	FILE *fp2 = fopen(f2, "r");
	if(fp1 == NULL || fp2 == NULL)
	{
		perror("fopen 失败");
		exit(0);
	}
	FILE *fp3 = fopen("tmp.txt","w");
	
	int n1,n2;
	if(fscanf(fp1, "%d", &n1) == EOF)
	{
		fclose(fp1);
		fclose(fp2);

		remove(f1);
		rename(f2, f1);
		return;
	}
	if(fscanf(fp2, "%d", &n2) == EOF)
	{
		fclose(fp1);
		fclose(fp2);

		remove(f2);
		return;
	}
	
	while(1)
	{
		if(n1<n2)
		{
			fprintf(fp3,"%d\n",n1);
			if(fscanf(fp1, "%d", &n1) == EOF)
			{
				fprintf(fp3, "%d\n", n2);
				
				break;
			}
		}
		else
		{
			fprintf(fp3,"%d\n",n2);
			if(fscanf(fp2, "%d", &n2) == EOF)
			{
				fprintf(fp3, "%d\n", n1);
				
				break;
			}
		}
	}
	
	// f取还剩下数据未读完的那个文件
	FILE *f = feof(fp1) ? fp2 : fp1;
	int n ;
	
	while(1)
	{
		if(fscanf(f, "%d", &n) == EOF)
			break;
			
		fprintf(fp3, "%d\n", n);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	// 最后将临时文件，更名为begin.txt
	
	int a = remove(f1);
	int b = remove(f2);
	rename("tmp.txt", f1);
}

int main(void)
{
	FILE *fp = fopen("numbers.txt", "r");
	if(fp == NULL)
	{
		perror("fopen numbers.txt failed");
		exit(0);
	}
	//定义100000个int型空间
	int *data = calloc(100*1000,sizeof(int));
	//读取文本内容 一次读取10万个数据
	bool finish = false;
	int k;
	for(k=1; ;k++)
	{
		int i;
		for(i = 0;i<100*1000; i++)
		{
			
			if(fscanf(fp, "%d", &data[i]) == EOF)
			{
				
				if(feof(fp))
				{
					finish = true;
					break;
				}

				if(ferror(fp))
				{
					perror("fscanf error");
					exit(0);
				}
			}
		}
		
		quick_sort(data, i);
		char filename[10];
		bzero (filename,10);
		snprintf(filename,10,"%d.txt",k); 
		
		//将分类好的数字存放到新的文件中
		FILE *fp_sorted = fopen(filename,"w");
		for(int j = 0;j<i;j++)
		{
		
			//fprintf(fp_sorted,"%d\n",data[j]);
			fprintf(fp_sorted,"%d\n",data[j]);
		}
		fclose(fp_sorted);
		if(finish == true)
		{
			printf("%d",__LINE__);
			break;
		}
		
	}
	free(data);
	fclose(fp);
	
	
	//合并生成的小文件
	merge(1, k-1);
	rename("1.txt","finist_sort_numbers.txt");
	printf("finish!\n");
	return 0;
	
}





















