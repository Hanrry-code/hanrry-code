#include "hannan.h"
#include "bmp.h"
#include "tc.h"
//无特效显示图片
void photo12(char *UIphotograph)
{
	int lcd_fd;
	lcd_fd = open("/dev/fb0",O_RDWR);
	if (lcd_fd == -1)
	{

		perror("打开文件失败\n");

	}

	int bmp_fd;
	bmp_fd = open(UIphotograph,O_RDONLY);
	if (bmp_fd == -1)
	{

		perror("打开文件失败\n");

	}

	// 映射内存
	

	int *p = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE,MAP_SHARED,lcd_fd,0);
	char bmpbuf[800*480*3];
	int lcdbuf[480][800];

	lseek(bmp_fd,54,SEEK_SET);

	read(bmp_fd,bmpbuf,800*480*3);


	// 妥善地将BMP中的RGB数据搬到映射内存上
	int x,y;

	//进行像素点的颜色对应和填充
	for(y = 0;y < 480;y++)
		for(x = 0;x < 800;x++)
			lcdbuf[479-y][x] = bmpbuf[(y*800+x)*3] << 0 | bmpbuf[(y*800+x)*3+1] << 8 | bmpbuf[(y*800+x)*3+2] << 16; 

	//显示
	for(y = 0;y < 480;y++)
		for(x = 0;x < 800;x++)
			*(p + y * 800 + x) = lcdbuf[y][x];


	
	close(lcd_fd);
	close(bmp_fd);
	munmap(p, 800*480*4);


}



//百叶窗特效显示图片
void photo3(char *UIphotograph)
{
	int bmp_fd;
	bmp_fd = open(UIphotograph,O_RDONLY);
	if (bmp_fd == -1)
	{

		perror("打开文件失败\n");

	}


	// 映射内存
	int lcd_fd;
	lcd_fd = open("/dev/fb0",O_RDWR);
	if (lcd_fd == -1)
	{

		perror("打开文件失败\n");

	}


	int *p = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE,MAP_SHARED,lcd_fd,0);
	char bmpbuf[800*480*3];
	int lcdbuf[480][800];

	lseek(bmp_fd,54,SEEK_SET);

	read(bmp_fd,bmpbuf,800*480*3);





	//百叶窗
	{
		int x,y,i,n=10;//改变n的值就能改变百叶窗的窗叶数量，但是要能被480整除
		//进行像素点的颜色对应和填充
		for(y = 0;y < 480;y++)
			for(x = 0;x < 800;x++)
				lcdbuf[479-y][x] = bmpbuf[(y*800+x)*3] << 0 | bmpbuf[(y*800+x)*3+1] << 8 | bmpbuf[(y*800+x)*3+2] << 16; 
		//从上至下
		for(y = 0;y < 480/n;y++)
		{
			for(i = 0;i < n;i++)
				for(x = 0;x < 800;x++)
					*(p + (y + i*480/n) * 800 + x) = lcdbuf[y+i*480/n][x];

			usleep(10000);
		}	
	}
	//write(lcd_fd,lcdbuf,800*480*4);
	close(lcd_fd);
	close(bmp_fd);
	munmap(p, 800*480*4);

}

void UI(int k,bool *first)
{
	
	char UIphotograph[6][20] = {"firstphoto.bmp","secondphoto.bmp","thirdphoto.bmp","forthphoto.bmp","fifthphoto.bmp","sixthphoto.bmp"};
	
	int x,y;
	//当UI是第一次被调用时
	if(*first == true)
	{
		photo12(UIphotograph[k]);
		//接受触摸屏的数据
		int x_slip = get_xy(&x,&y);

		//判断触摸屏触摸的地方是否在特定区域 且是否向右滑动
		if(x_slip == 4 && (y > 300 && y <= 480 ))
		{
			printf("%d\n",__LINE__);
			k++;
		}
		printf("%d","%d\n",x,y);

		//显示密码界面
		photo12(UIphotograph[k]);

		//如果实现密码，则开启功能模块

		while(1)
		{
			int l = 0;
			get_xy(&x,&y);
			if((x-390)*(x-390) + (y-430)*(y-430) < 40*40)
				l++;
			usleep(200*1000);
			get_xy(&x,&y);
			if((x-290)*(x-290) + (y-340)*(y-340) < 40*40)
				l++;
			usleep(200*1000);

			get_xy(&x,&y);
			if((x-490)*(x-490) + (y-150)*(y-150) < 40*40)
				l++;
			usleep(200*1000);

			get_xy(&x,&y);
			if((x-290)*(x-290) + (y-150)*(y-150) < 40*40)
				l++;
			if(l==4)
				break;
			else
				printf("密码错误，请重试！\n");
		}
		
		k++;
		photo12(UIphotograph[k]);
		k++;
		photo3(UIphotograph[k]);
		*first = false;
		/* char *buf = calloc(1,250);
		
		getcwd(buf,250);
		printf("%s\n",buf);
		free(buf); */
	}
	//返回主页面
	else
	{
		chdir("/IOT/hannan");
		char *buf = calloc(1,250);
		
		getcwd(buf,250);
		printf("%s\n",buf);
		free(buf);
		
		photo12(UIphotograph[k]);
		k++;
		photo3(UIphotograph[k]);
		
	}
	
}









