#include "hannan.h"

static int piano_numbers;
static int x,y;
char piano_mp3[12][20];

static char piano_bmp[5][50] = {"/IOT/hannan/piano/background.bmp","/IOT/hannan/piano/2.bmp","/IOT/hannan/piano/3.bmp","/IOT/hannan/piano/logo.bmp","/IOT/hannan/piano/bar.bmp"};



void *show_piano(void *arg)
{
	system("killall -9 madplay");
	
	int p = *(int *)arg;
	usleep(10000);
	music_play(piano_mp3[p]);
	
}
void f(int sig, siginfo_t *info, void *arg)
{
	
	
	printf("%d\n",__LINE__);

	b = info->si_int;

	printf("%d\n",info->si_int);
	
	// ����һ���������̣߳�ȥ��������д��
	pthread_t tid;
	pthread_create(&tid, NULL,show_piano, &b);// �߳�ִ�к����Ĳ���

}
void tc_piano(void)
{
	piano_get_xy(&x,&y);
	
}


void piano(char *argv)
{
	//��ʾ����ͼƬ
	photo_key(piano_bmp[0], 0, 0);
	photo_key(piano_bmp[4], 0, 0);
	photo_key(piano_bmp[3], 229, 370);
	for(int i = 0;i<12;i++)
		photo_key(piano_bmp[2], 65*i+5, 47);
	struct stat info;
	bzero(&info, sizeof(info));
	if(stat(argv, &info) == -1)
	{
		perror("��ȡָ���ļ�����ʧ��");
		exit(0);
	}
	

	/*	�������жϸ���Ĳ����Ƿ�����*/
	DIR *dp = opendir(argv);
	chdir(argv);
	struct dirent *ep;
	
	while(1)
	{

		ep = readdir(dp);
		if(ep == NULL)
		{
			break;
			
		}
		
		else if(strstr(ep->d_name + strlen(ep->d_name) - 3, "mp3")!=NULL)
		{

			strcpy(piano_mp3[piano_numbers] , ep->d_name);
			piano_numbers++;

		}
		
	}
	printf("��������Ŀ:%d\n",piano_numbers);
	for(int j;j < piano_numbers;j++ )
	{
		printf("%s\n",piano_mp3[j]);
	}
	

	// ������ר�Ž�����Ϣ�Ͳ�������
	pid = fork();
	if(pid > 0)
	{
		printf("������pid:%d\n",getpid());

		struct sigaction act1;
		bzero(&act1, sizeof(act1));


		act1.sa_sigaction = f;
		act1.sa_flags |= SA_SIGINFO;

		// ׼���ý���һ��������������ź�
		sigaction(SIGUSR1, &act1, NULL);


		while(1)
		{
			pause();
		}

	}
	if(pid == 0)
	{
		while(1)
		{
			int tc_piano = piano_get_xy(&x,&y);
			if(tc_piano == 1)
			{
				break;
			}
		}

	}

}
