#include "hannan.h"
#include "tc.h"
#include "list.h"

void freelcd(void);
void getjpg(char *photograph,struct node *new);
int get_xy(int *x,int *y);
void showbmp(struct node *new);
void showjpg(struct node *new);
void getbmp(char *UIphotograph,struct node *new);
void UI(int k1,bool *first);
void piano(char *argv);
int piano_get_xy(int *x1,int *y1);
static int x,y;
static int k1 = 0;
static bool first = true;

void shoudong_show(struct node* head)
{
	struct list_head *p = head->list.next;
	struct node *s = list_entry(p, struct node, list);
	if(strstr(s->pic_path,".bmp"))
	{
		printf("s->path ");
		showbmp(s); 
	}
	if(strstr(s->pic_path,".jpg"))
		showjpg(s);
	while(1)
	{

		int slip = get_xy(&x,&y);

		if(slip == 4)
		{	

			p = p->prev;
			if(p == &head->list)
				p = p->prev;

		}
		else if(slip == 3)
		{	
			p = p->next;
			if(p == &head->list)
				p = p->next;
		}
		else if(slip == 1)
		{	
			UI(4,&first);
			break;
		}
		s = list_entry(p, struct node, list);
		if(strstr(s->pic_path,".bmp"))
		{
			printf("s->path ");
			showbmp(s); 
		}
		if(strstr(s->pic_path,".jpg"))
			showjpg(s);


	}
	
}
void auto_show(struct node* head)
{
	struct list_head *p = &head->list;
	struct node *s = list_entry(p, struct node, list);

	while(1)
	{


		if(p->next !=&head->list)
		{	
			p = p->next;
			if(p == &head->list)
				p = p->next;


			s = list_entry(p, struct node, list);
			if(strstr(s->pic_path,".bmp"))
			{
				printf("s->path ");
				showbmp(s); 
			}
			if(strstr(s->pic_path,".jpg"))
				showjpg(s);

		}
		else
		{
			printf("已经显示到最后一张图片\n");

			break;
		}
		sleep(1);
	}

	UI(4,&first);


}

int main(int argc, char **argv) 
{



	UI(k1,&first);


	if(argc != 4)
	{
		printf("参数有误！！再见！\n");
		exit(0);
	}
	struct stat info;
	bzero(&info, sizeof(info));
	if(stat(argv[1], &info) == -1)
	{
		perror("获取指定文件属性失败");
		exit(0);
	}
	if(!S_ISDIR(info.st_mode))
	{
		printf("给我的不是目录！走人！\n");
		exit(0);
	}	

	/*	以上是判断给予的参数是否有误*/

	while(1)
	{
		int j_tc = get_xy(&x,&y);
		if((x-240)*(x-240) + (y-80)*(y-80) < 50*50)
		{
			UI(4,&first);
			DIR *dp = opendir(argv[1]);
			chdir(argv[1]);
			struct dirent *ep;


			int i = 0;

			// 1，初始化一条空链表
			struct node *head = init_list();

			while(1)
			{

				ep = readdir(dp);
				if(ep == NULL)
					break;

				if(strstr(ep->d_name + strlen(ep->d_name) - 3, "jpg")!=NULL)
				{

					//printf("%s\n", ep->d_name);
					// 创建新节点,并将图片信息保存于该节点中
					struct node *new = new_node();
					strcpy(new->pic_path , ep->d_name);
					getjpg(ep->d_name,new);
					list_add_tail(&new->list, &head->list);	

				}
				if(strstr(ep->d_name + strlen(ep->d_name) - 3, "bmp")!=NULL)
				{
					struct node *new = new_node();
					strcpy(new->pic_path , ep->d_name);
					getbmp(ep->d_name,new);
					list_add_tail(&new->list, &head->list);	

				}
			}
			show(head);
			while(1)
			{
				
				int i_tc = get_xy(&x,&y);
				
				if(x>=520&&x<=750&&y>=60&&y<=240)
					shoudong_show(head);

				else if(x>=100 && x<=350 && y>=270 && y<=440 )
					auto_show(head);
				else if(i_tc == 1)
				{
					UI(2,&first);
					break;
				}
			}
		}
		else if((x-85)*(x-85) + (y-90)*(y-90) < 50*50)
		{
			mp3(argv[2]);
			UI(2,&first);
		}
		else if((x-400)*(x-400) + (y-90)*(y-90) < 50*50)
		{
			piano(argv[3]);
			UI(2,&first);
		}
		
		else if(j_tc == 1)
		{
			system("killall -9 main");
		}
	}
		
		
	return 0; 
}
