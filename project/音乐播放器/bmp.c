#include "hannan.h"
//无特效显示图片
void photo(char *cd_bmp)
{
	int bmp_fd;
	bmp_fd = open(cd_bmp,O_RDWR);


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


	//无特效显示图片

	// 妥善地将BMP中的RGB数据搬到映射内存上
	int x1,y1;

	//进行像素点的颜色对应和填充
	for(y1 = 0;y1 < 480;y1++)
		for(x1 = 0;x1 < 800;x1++)
			lcdbuf[479-y1][x1] = bmpbuf[(y1*800+x1)*3] << 0 | bmpbuf[(y1*800+x1)*3+1] << 8 | bmpbuf[(y1*800+x1)*3+2] << 16; 

	//显示
	for(y1 = 0;y1< 480;y1++)
		for(x1 = 0;x1 < 800;x1++)
			*(p + y1 * 800 + x1) = lcdbuf[y1][x1];





	close(lcd_fd);
	close(bmp_fd);
	munmap(p, 800*480*4);

}
void photo_plus(char *bmp_path)
{
	int bmp_fd;
	bmp_fd = open(bmp_path,O_RDWR);


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




	//渐变显示

	int x,y,i,n;
	//进行像素点的颜色对应和填充
	for(n = 1;n <= 100;n++)
	{	
		//进行像素点的颜色对应和填充
		for(y = 0;y < 480;y++)
			for(x = 0;x < 800;x++)
				lcdbuf[479-y][x] = (bmpbuf[(y*800+x)*3]*n/100) << 0 | (bmpbuf[(y*800+x)*3+1]*n/100) << 8 | (bmpbuf[(y*800+x)*3+2]*n/100) << 16; 

		//显示
		for(y = 0;y < 480;y++)
			for(x = 0;x < 800;x++)
				*(p + y * 800 + x) = lcdbuf[y][x];


	}


	close(lcd_fd);
	close(bmp_fd);
	munmap(p, 800*480*4);

}

