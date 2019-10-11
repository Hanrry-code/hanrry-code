#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/soundcard.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <syslog.h>
#include <dirent.h>
#include <assert.h>
#include <semaphore.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) 
{
	
	// TCP
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1],
		(struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	// 连接对端
	 connect(sockfd, (struct sockaddr *)&srvaddr,
				sizeof srvaddr);

	
	char msg[1024];
	
	//写入数据
	printf("%d\n",__LINE__);
	printf("请输入您要转成语音的话\n");
	bzero(msg, 1024);
	fgets(msg, 1024, stdin);

	write(sockfd, msg, strlen(msg));
	
	char buf[4*1024]={0};
	int read_ret = 1;
	int write_ret = 0;
	int read_total_num = 0;
	int write_total_num = 0;
	
		//创建一个wav文件
	
	int	fd = open("tts_sample.wav",O_RDWR|O_CREAT);
	//读取数据
	while(read_ret)
	{
		bzero(buf, 4*1024);
		
		read_ret = read(sockfd, buf, sizeof(buf));
		if(read_ret == -1)
			perror("read failed\n");
		write_ret = write(fd,buf,read_ret);
	
		read_total_num += read_ret;
		write_total_num += write_ret;
		
	}
	close(fd);
	printf("read_total_num = %d\n",read_total_num);
	printf("write_total_num = %d\n",write_total_num);
	
	
	
	//播放该音频
	char cmd_buf[64]={0};

	sprintf(cmd_buf,"aplay tts_sample.wav \n");
	system(cmd_buf);
	
	

	printf("客户端已经断开了连接\n");
	



	return 0;
}

