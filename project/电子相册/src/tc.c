//编写一个程序，封装对触摸屏的常规操作，比如单击、双击、左右滑动。手指做出以上动作之后，让开发板终端输出相应的文字提示
#include "hannan.h"
#include "tc.h"



//获取触摸屏坐标
	//获取触摸屏坐标
	int get_xy(int *x1,int *y1)
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
					x_c = x;
					y_c = y;
					
					if(click_flag==0) //奇次点击
					{
						time_start=time(0);
						click_flag=1; 
						
					}
					else if(click_flag==1)
					{
						time_end=time(0);
						click_flag=0;
					}
					
					
					
					if(time_start==time_end) //在1s内完成两次点击
					{
						printf("双击\n");
						return 2;
						break;
						
					}
					else
					{
						printf("单击\n" );
						
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
					/* if(y_slip < -100)
					{
						printf("向下滑动\n");
					} */
					
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
					break;
				}
			}
			
		}
		return a;
	}