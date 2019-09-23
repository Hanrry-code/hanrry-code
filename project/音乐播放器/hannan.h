#ifndef __HANNAN_H
#define __HANNAN_H


#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

// 全局错误码
#include <errno.h>

// 文件IO操作
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

// 数学库
#include <math.h>

// 目录
#include <dirent.h>

// 触摸屏
#include <linux/input.h>

// 液晶屏
#include <sys/mman.h>
#include <linux/fb.h>

// 动态链接动态库
#include <dlfcn.h>

//多任务
#include <syslog.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
// 自定义头文件
#include "tc.h"
#include "bmp.h"
 #include "music.h" 
// 消息队列专属的结构体
pid_t pid;
static int x,y,k = 0,b = 0 ;
static bool m_pause = false;

char pmusic_path[50][10];
char bmp_path[10][10];


struct msgbuf
{
	long type;
	char data[10][10];
};


#define F2Z 100


#endif
