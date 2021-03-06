#ifndef __COMMON_H
#define __COMMON_H

// 基本常用头文件
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

#endif
