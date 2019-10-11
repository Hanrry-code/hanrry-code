#include"hannan.h"
void tc(void);
void recorder_make_wav(void);
int show_id(char *json);
char cd_bmp[3][30] = {"/IOT/hannan/mp3/1.bmp","/IOT/hannan/mp3/2.bmp","/IOT/hannan/mp3/3.bmp"};
static int mp3_numbers;
static int bmp_numbers;
int sockfd,rt;
pthread_t tid;
struct timeval timeout={10,0};//设置发送超时

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
		//录音，生成wav文件
		recorder_make_wav();
		//打开wav文件，读取pcm数据并将数据发送给服务端
		char buf[4*1024]={0};
		int read_ret = 1;
		int write_ret = 0;
		int read_total_num = 0;
		int write_total_num = 0;
		
		printf("%d\n",__LINE__);
		int	fd_wav = open("record.wav",O_RDWR|O_CREAT);
		//移动到文件最尾端，获取文件大小
		int fd_size = lseek(fd_wav,0, SEEK_END);
		lseek(fd_wav,0, SEEK_SET);
		//发送过去转换为文字	
		write(sockfd,&fd_size,4);
		//设置发送超时
		 rt = setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,(const char *)&timeout,sizeof timeout);
		 if(rt < 0)
		 {
		  perror("setsockopt SO_RCVTIMEO:");
		 
		 }
		while(1)
		{

			bzero(buf, 4*1024);

			read_ret = read(fd_wav, buf, sizeof(buf));
			if(read_ret == 0)
				break;
			write_ret = write(sockfd,buf,read_ret);
			read_total_num += read_ret;
			write_total_num += write_ret;

		}
		close(fd_wav);
		printf("read_total_num = %d\n",read_total_num);
		printf("write_total_num = %d\n",write_total_num);
		
		//等待对方返回
		int ret;
		read(sockfd,&(ret),sizeof(ret));
		printf("ret :%d\n",ret);
		if(ret == 0)
		{
			printf("音频解析失败,重新获取\n");
			continue;
		}
		else
		{
			
		
 
			usleep(20000);
			//读取音频解析结果
			read_ret = 1;
			write_ret = 0;
			read_total_num = 0;

			bzero(buf, 4*1024);

			read_ret = read(sockfd, buf, sizeof(buf));
			 //设置接收超时
			 rt = setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(const char *)&timeout,sizeof timeout);
			 if(rt < 0)
			 {
			  perror("setsockopt SO_RCVTIMEO:");
			 
			 }
			printf("%s\n",buf);
		
		
			int id = show_id(buf);
			printf("id:%d\n",id);
			//暂停
			if(id == 1001)
			{
				if(m_pause == false)
				{
					music_pause();
					m_pause = true;
				}

			}
			//继续
			else if(id == 1002)
			{

				if(m_pause == true)
				{
					music_continue();
					m_pause = false;
				}
			}
			//切换上一首
			else if(id == 1003)
			{
				//播放上一首歌曲信号
				music_prev(mp3_numbers);
				music_continue();
				printf("向父进程%d发送信息\n",getppid());
			}
			//播放下一首
			else if(id == 1004)
			{
				//播放下一首歌曲信号
				music_next(mp3_numbers);
				music_continue();
				printf("向父进程%d发送信息\n",getppid());
			}
			//播放写真
			else if(id == 1005)
			{
				printf("%d\n",__LINE__);

				int i_tc;
				// 启动一条并发的线程，去单独播放写真

				pthread_create(&tid, // 成功创建线程之后，其ID号将会被存储在tid中
						//&attr,// 指定线程的启动属性，NULL代表不设定任何特殊属性
						NULL,// 指定线程的启动属性，NULL代表不设定任何特殊属性
						tc_bmp,    // 指定线程的执行函数
						NULL);// 线程执行函数的参数

			}
			//关闭写真
			else if(id == 1006)
			{

				pthread_cancel(tid);
				pthread_join(tid, NULL);
				music_continue();
			}
			//关闭播放器
			else if(id == 1007)
			{
				music_exit();
				//break;
			}
		}
	}
}
int main(int argc, char **argv)
{
	if(argc != 4)
	{
		printf("Usage: %s <MP3_path> <ip> <port>\n", argv[0]);
		exit(1);
	}
	//建立tcp协议
	// TCP

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[2],
			(struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[3]));

	// 连接对端
	connect(sockfd, (struct sockaddr *)&srvaddr,
			sizeof srvaddr);

	photo_plus(cd_bmp[2]);
	sleep(1);
	//显示一张图片
	photo(cd_bmp[b]);


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
	DIR *dp = opendir(argv[1]);
	chdir(argv[1]);
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
	return 0;
}























