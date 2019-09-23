//编写一个程序，封装对触摸屏的常规操作，比如单击、双击、左右滑动。手指做出以上动作之后，让开发板终端输出相应的文字提示。
#ifndef _TC_H_
#define _TC_H_

#include "hannan.h"

#define CLICK 1
#define DCLICK 2
#define RIGHT 3
#define LEFT 4
#define UP 5
#define DOWN 6

clock_t start,end;
int get_xy(int *x,int *y);

#endif
