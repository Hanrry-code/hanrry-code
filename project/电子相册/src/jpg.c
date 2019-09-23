#include "hannan.h"
#include "jpeglib.h"
#include "list.h"

static int lcd;
static int lcd_w;
static int lcd_h;
static int lcd_bpp;
static int screen_size;
static struct fb_var_screeninfo vsinfo;
static char *lcdmem;
static int k;


void getjpg(char *photograph,struct node *new)
{
	printf("photograph:%s\n",photograph);
	int x,y;
	// 第一次显示图片的时候，就准备好LCD设备

	lcd = open("/dev/fb0", O_RDWR);

	bzero(&vsinfo, sizeof(vsinfo));
	ioctl(lcd, FBIOGET_VSCREENINFO, &vsinfo); // 获取了LCD的硬件参数

	lcd_w = vsinfo.xres;
	lcd_h = vsinfo.yres;
	lcd_bpp =  vsinfo.bits_per_pixel;
	screen_size = lcd_w * lcd_h * lcd_bpp/8;

	lcdmem = mmap(NULL, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);





	int jpgfd = open(photograph, O_RDONLY);
	int jpg_size = lseek(jpgfd, 0L, SEEK_END);
	lseek(jpgfd, 0L, SEEK_SET);

	char *jpg_buffer = calloc(1, jpg_size);

	// 完整地读完了 a.jpg 文件的内容，妥妥地放到了 jpg_buffer 中
	int total = jpg_size;
	while(total > 0)
	{
		int n = read(jpgfd, jpg_buffer+(jpg_size-total), total);
		total -= n;
	}

	close(jpgfd);


	// JPG  ==>  RGB

	// 声明解压缩结构体，以及错误管理结构体
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	// 使用缺省的出错处理来初始化解压缩结构体
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	// 配置该cinfo，使其从jpg_buffer中读取jpg_size个字节
	// 这些数据必须是完整的JPEG数据
	jpeg_mem_src(&cinfo, jpg_buffer, jpg_size);


	// 读取JPEG文件的头，并判断其格式是否合法
	int ret = jpeg_read_header(&cinfo, true);
	if(ret != 1)
	{
		fprintf(stderr, "[%d]: jpeg_read_header failed: "
				"%s\n", __LINE__, strerror(errno));
		exit(1);
	}


	// 开始解码
	jpeg_start_decompress(&cinfo);



	// 图片的每一行所包含的字节数
	int row_stride = cinfo.output_width * cinfo.output_components;

	// 根据图片的尺寸大小，分配一块相应的内存rgb_buffer
	// 用来存放从jpg_buffer解压出来的图像数据
	unsigned char *rgb_buffer = calloc(1, row_stride*cinfo.output_height);

	// 循环地将图片的每一行读出并解压到rgb_buffer中
	int line = 0;
	while(cinfo.output_scanline < cinfo.output_height)
	{
		unsigned char *buffer_array[1];
		buffer_array[0] = rgb_buffer +
			(cinfo.output_scanline) * row_stride;
		jpeg_read_scanlines(&cinfo, buffer_array, 1);
	}

	// 解压完了，将jpeg相关的资源释放掉
	//	jpeg_finish_decompress(&cinfo);
	//	jpeg_destroy_decompress(&cinfo);
	//	free(jpg_buffer);


	// 恭喜！现在rgb_buffer中就已经有图片对应的RGB数据了

	new->red = vsinfo.red.offset;
	new->green = vsinfo.green.offset;
	new->blue = vsinfo.blue.offset;
	new->rgb_buf = rgb_buffer;
	new->lcd = lcdmem;
	// cinfo中保存了图片文件的尺寸信息
	new->width = cinfo.output_width; // 宽
	new->height = cinfo.output_height; // 高	
	k = 0;
	printf("w:%d", new->width );
	printf("h:%d", new->height);
	if(cinfo.output_width>lcd_w)
	{
		printf("OK");
		k = new->width/(lcd_w) > new->height/(lcd_h) ? new->width/(lcd_w):new->height/(lcd_h);
	}
	else if(cinfo.output_height>lcd_h)
	{
		printf("OK");
		k = new->width/(lcd_w) > new->height/(lcd_h) ? new->width/(lcd_w):new->height/(lcd_h);
	}
	printf("%d,000\n",k);
	k = k+1;
	x = (lcd_w-new->width/k)/2;//计算居中显示的坐标
	y = (lcd_h-new->height/k)/2;
	new->stride= row_stride;
	new->x = x;
	new->y = y;
	new->k = k;
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(jpg_buffer);
	
	

}		

void showjpg(struct node *new)
{

	char *lcdtmp = new->lcd;
	char *rgbtmp = new->rgb_buf;

	//lcdtmp +=  (new->y*lcd_w+ new->x)*(new->bpp/8);




	// 将rgb数据妥善地放入lcdmem

	bzero(lcdtmp , 480*800*4);
	lcdtmp += (lcd_w*lcd_bpp/8)*new->y; // lcd显存指针向下偏移一行

	printf("%d\n",new->k );
	int i,j;
	for(j=0; j<new->height/new->k ; j++)
	{
		for(i=0; i<new->width/new->k ; i++)
		{
			memcpy(lcdtmp + 4*(i+new->x) + new->red/8,  rgbtmp + new->k *3*i+ 0, 1);
			memcpy(lcdtmp + 4*(i+new->x) + new->green/8, rgbtmp + new->k *3*i + 1, 1);
			memcpy(lcdtmp + 4*(i+new->x) + new->blue/8,   rgbtmp + new->k *3*i + 2, 1);
		}

		lcdtmp += (lcd_w*lcd_bpp/8); // lcd显存指针向下偏移一行
		rgbtmp += new->k *(new->stride); // rgb指针向下偏移一行
	}

	// 释放相应的资源
	//free(new->rgb_buf);
	//close(new->lcd);
}

void freelcd_jpg(void)
{

	munmap(lcdmem, screen_size);
	close(lcd);

}
