#include"hannan.h"



void music_play(void *pmusic_path)
{
	char cmd_buf[64]={0};

	sprintf(cmd_buf,"madplay %s -A -35\n",pmusic_path);
	system(cmd_buf);
}

void music_pause(void)
{
	union sigval var;
	system("killall -STOP madplay ");	
	b=1;
	var.sival_int = b;
	sigqueue(getppid(), 10, var);

}

void music_continue(void)
{
	union sigval var;
	system("killall -CONT madplay ");	
	b=0;
	var.sival_int = b;
	sigqueue(getppid(), 12, var);

}

void music_stop(void)
{

	/* 关掉madplay进程 */
	system("killall -9 madplay");

}
void music_exit(void)
{
	system("killall -9 madplay");
	system("killall -9 main");
}


void music_next(int mp3_numbers)
{
	union sigval var;

	music_stop();
	if(k == mp3_numbers-1)
	{
		k=0;
	}
	else
	{
		k++;
	}
	var.sival_int = k;

	// 发送一个携带额外参数的信号
	sigqueue(getppid(), 2, var);
	printf("%d k:%d mp3_numbers:%d\n",__LINE__,k,mp3_numbers);
}
void music_prev(int mp3_numbers)
{
	union sigval var;
	music_stop();
	if(k == 0)
	{
		k=mp3_numbers-1;
	}
	else
	{
		k--;
	}
	var.sival_int = k;

	// 发送一个携带额外参数的信号
	sigqueue(getppid(), 3, var);
	printf("%d k:%d\n",__LINE__,k);
}

void cd_music(int sig, siginfo_t *info, void *arg)
{
	printf("%d\n",__LINE__);

	music_play(pmusic_path[info->si_int]);
	printf("%d\n",info->si_int);

}
