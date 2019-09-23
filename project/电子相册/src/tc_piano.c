//编写一个程序，封装对触摸屏的常规操作，比如单击、双击、左右滑动。手指做出以上动作之后，让开发板终端输出相应的文字提示
#include "hannan.h"
#include "tc.h"
static char piano_bmp2[3][30] = {"/IOT/hannan/piano/1.bmp","/IOT/hannan/piano/2.bmp","/IOT/hannan/piano/3.bmp"};



//获取触摸屏坐标
	//获取触摸屏坐标
	int piano_get_xy(int *x1,int *y1)
	{
		int a = 0;
		int click_flag=0; //点击标志位
		long time_start; //奇次点击时间
		long time_end;  //偶次点击时间
		
		int x,y,x_n,y_n,x_c,y_c,x_slip,y_slip;
		
		// 打开触摸屏设备文件  /dev/input/event0
		int ts_fd;
		ts_fd = open("/dev/input/event0",O_RDONLY);
		
		if(ts_fd == -1)
		{
			printf("open ts failed\n");
		}
		
		// 用于接收触摸屏产生的所有的信息
		struct input_event tsbuf;
		bzero(&tsbuf,sizeof(tsbuf));
		
		while(1)
		{
			read(ts_fd,&tsbuf,sizeof(tsbuf));
		
			if(tsbuf.type == EV_ABS && tsbuf.code == ABS_X)
			{
				x = tsbuf.value*800/1024;
				*x1 = x;
			}
			if(tsbuf.type == EV_ABS && tsbuf.code == ABS_Y)
			{
				y = tsbuf.value*480/600;
				*y1 = y;
			}
			
			//判断当前的释放状态，触摸屏按下和释放是模拟按键的
			if(tsbuf.type == EV_KEY && tsbuf.code == BTN_TOUCH )
			{
				
				//按下
				if(tsbuf.value == 1)
				{
					if(x >= 5 && x<=70 && y >= 47 && y<=280)
					{
						union sigval var;
						b=0;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 5, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 70 && x<=135 && y >= 47 && y<=280)
					{
						union sigval var;
						b=1;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 70, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 135 && x<200 && y >= 47 && y<=280)
					{
						union sigval var;
						b=2;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 135, 47);
					
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 200 && x<=265 && y >= 47 && y<=280)
					{
						union sigval var;
						b=3;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 200, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 265 && x<=330 && y >= 47 && y<=280)
					{
						union sigval var;
						b=4;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 265, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 330 && x < 395 &&y >= 47 && y<=280)
					{
						union sigval var;
						b=5;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 330, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 395 && x<=460 && y >= 47 && y<=280)
					{
						union sigval var;
						b=6;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 395, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 460 && x<=525 && y >= 47 && y<=280)
					{
						union sigval var;
						b=7;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 460, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 525 && x<=590 && y >= 47 && y<=280)
					{
						union sigval var;
						b=8;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 525, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 590 && x<=655 && y >= 47 && y<=280)
					{
						union sigval var;
						b=9;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 590, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 655 && x<=720 && y >= 47 && y<=280)
					{
						union sigval var;
						b=10;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 655, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					else if(x >= 720 && x<=785 && y >= 47 && y<=280)
					{
						union sigval var;
						b=11;
						var.sival_int = b;
						photo_key(piano_bmp2[1], 720, 47);
						
						sigqueue(getppid(), 10, var);
						
					}
					
				}
				else
				{
					
					x_n = x;
					y_n = y;
					
					x_slip = x_c - x_n;  //x轴滑动
					y_slip = y_c - y_n;  //y轴滑动
					
					
					//从下往上滑动
					if(y_slip > 100)
					{
						printf("向上滑动\n");
						a = 1;
					}
					
					//从上往下滑动
					if(y_slip < -100)
					{
						printf("向下滑动\n");
						a = 2;
					}
					
					//从右往左滑动
					if(x_slip > 150)
					{
						printf("向左滑动\n");
						a = 3;
					}
					
					//从左往右滑动
					if(x_slip < -150)
					{
						printf("向右滑动\n");
						 a = 4;
					}
					
					
				}
				
			}
			if(tsbuf.type == EV_KEY)
			{
				if(tsbuf.code == BTN_TOUCH && tsbuf.value == 0)
				{
					printf("手指松开了\n");
					
					if(x >= 5 && x<=70 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 5, 47);
						
						
						
					}
					else if(x >= 70 && x<=135 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 70, 47);
						
						
						
					}
					else if(x >= 135 && x<200 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 135, 47);
					
						
						
					}
					else if(x >= 200 && x<=265 && y >= 47 && y<=280)
					{
					
						photo_key(piano_bmp2[2], 200, 47);
						
						
					}
					else if(x >= 265 && x<=330 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 265, 47);
						
						
						
					}
					else if(x >= 330 && x < 395 &&y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 330, 47);
						
						
						
					}
					else if(x >= 395 && x<=460 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 395, 47);
						
						
						
					}
					else if(x >= 460 && x<=525 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 460, 47);
						
						
						
					}
					else if(x >= 525 && x<=590 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 525, 47);
						
					
						
					}
					else if(x >= 590 && x<=655 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 590, 47);
						
						
					}
					else if(x >= 655 && x<=720 && y >= 47 && y<=280)
					{
					
						photo_key(piano_bmp2[2], 655, 47);
			
					}
					else if(x >= 720 && x<=785 && y >= 47 && y<=280)
					{
						
						photo_key(piano_bmp2[2], 720, 47);
						
						
						
					}
					
					
					break;
				}
			}
			
		}
		return a;
	}