#include"hannan.h"

char cd_bmp[3][30] = {"/IOT/hannan/mp3/1.bmp","/IOT/hannan/mp3/2.bmp","/IOT/hannan/mp3/3.bmp"};
static int mp3_numbers;
static int bmp_numbers;
void cd_b(int sig, siginfo_t *info, void *arg)
{
	printf("%d\n",__LINE__);

	b = info->si_int;

	printf("%d\n",info->si_int);
	photo(cd_bmp[b]);
}
//子线程专门播放图片
void *tc_bmp(void *arg)
{

	int i_bmp;
	while(1)
	{
		if(i_bmp == bmp_numbers-1)
		{
			i_bmp =0;
		}
		else
		{
			i_bmp++;
		}
		photo_plus(bmp_path[i_bmp]);
		pthread_testcancel();
		sleep(1);
	}

}

void tc(void)
{

	while(1)
	{
			int tc_g = get_xy(&x,&y);
		printf("x:%d,y:%d\n",x,y);

		if((x-400)*(x-400) + (y-450)*(y-450) < 45*45)
		{
			if(m_pause == false)
			{
				music_pause();
				m_pause = true;
			}
			else
			{
				music_continue();
				m_pause = false;
			}
		}
		else if((x-760)*(x-760) + (y-20)*(y-20) < 50*50)
		{
			music_exit();
			break;
		}
		else if((x-460)*(x-460) + (y-450)*(y-450) < 35*35)
		{
			music_next(mp3_numbers);
			music_continue();
			printf("向父进程%d发送信息\n",getppid());
		}	
		else if((x-340)*(x-340) + (y-450)*(y-450) < 35*35)
		{
			music_prev(mp3_numbers);
			music_continue();
			printf("向父进程%d发送信息\n",getppid());
		}
		
		//触碰到左上角时显示歌手写真
		else if((x-40)*(x-40) + (y-40)*(y-40) < 40*40)
		{

			int i_tc;
			// 启动一条并发的线程，去单独播放写真
			pthread_t tid;
			pthread_create(&tid, // 成功创建线程之后，其ID号将会被存储在tid中
					//&attr,// 指定线程的启动属性，NULL代表不设定任何特殊属性
					NULL,// 指定线程的启动属性，NULL代表不设定任何特殊属性
					tc_bmp,    // 指定线程的执行函数
					NULL);// 线程执行函数的参数

			i_tc = get_xy(&x,&y);
			if(i_tc == 5)
			{
				pthread_cancel(tid);
				pthread_join(tid, NULL);
				music_continue();
			}
		}
		/* else if(tc_g == 1)
		{
			music_up();
			printf("增加音量2\n");
		}
		else if(tc_g == 2)
		{
			music_down();
			printf("降低音量2\n");
		} */
	}
}
void mp3(char *argv)
{

	photo_plus(cd_bmp[2]);
	usleep(300000);

	//显示一张图片
	photo(cd_bmp[b]);

	
	struct stat info;
	bzero(&info, sizeof(info));
	if(stat(argv, &info) == -1)
	{
		perror("获取指定文件属性失败");
		exit(0);
	}
	

	/*	以上是判断给予的参数是否有误*/
	DIR *dp = opendir(argv);
	chdir(argv);
	struct dirent *ep;

	while(1)
	{

		ep = readdir(dp);
		if(ep == NULL)
			break;

		else if(strstr(ep->d_name + strlen(ep->d_name) - 3, "mp3")!=NULL)
		{

			strcpy(pmusic_path[mp3_numbers] , ep->d_name);
			mp3_numbers++;

		}
		else if(strstr(ep->d_name + strlen(ep->d_name) - 3, "bmp")!=NULL)
		{

			strcpy(bmp_path[bmp_numbers] , ep->d_name);
			bmp_numbers++;

		}

	}
	printf("歌曲数目:%d\n",mp3_numbers);
	for(int j;j < mp3_numbers;j++ )
	{
		printf("%s\n",pmusic_path[j]);
	}
	printf("歌手写真:%d张\n",bmp_numbers);
	for(int j = 0;j < bmp_numbers;j++ )
	{

		printf("%s\n",bmp_path[j]);
	}

	// 父进程专门接受消息和播放音乐
	pid = fork();
	if(pid > 0)
	{
		printf("父进程pid:%d\n",getpid());

		struct sigaction act1;
		bzero(&act1, sizeof(act1));


		act1.sa_sigaction = cd_music;
		act1.sa_flags |= SA_SIGINFO;

		// 准备好接受一个带额外参数的信号
		sigaction(SIGINT, &act1, NULL);

		sigaction(SIGQUIT, &act1, NULL);
		struct sigaction act2;
		bzero(&act2, sizeof(act2));


		act2.sa_sigaction = cd_b;
		act2.sa_flags |= SA_SIGINFO;

		sigaction(SIGUSR1, &act2, NULL);

		sigaction(SIGUSR2, &act2, NULL);
		music_play(pmusic_path[0]);

		while(1)
		{
			pause();
		}

	}
	if(pid == 0)
	{
		tc();

	}

}























