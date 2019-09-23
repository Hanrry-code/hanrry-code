#include "hannan.h"
#include "bmp.h"

#include "list.h"
static char *lcdmem;

static int fd,lcd,lcd_w,lcd_h,lcd_bpp;
static bool first = true;




void getbmp(char *photograph,struct node *new)
{

	//printf("photograph:%s\n",photograph);
	char *r;

	// 0，分析BMP图片的头部信息，提取长宽深等信息
	fd = open(photograph, O_RDWR);

	struct bitmap_header head;
	struct bitmap_info  info;

	bzero(&head, sizeof(head));
	bzero(&info, sizeof(info));
	read(fd, &head, sizeof(head));
	read(fd, &info, sizeof(info));

	// 1，读取BMP图片的具体图像数据（RGB）
	int rgb_size = head.size-sizeof(head)-sizeof(info);
	r = calloc(1, rgb_size);

	int n = 0;
	int total = 0;
	// 确保将文件中的RGB数据读完
	while(rgb_size > 0)
	{
		n = read(fd, r+total, rgb_size);

		rgb_size -= n;
		total    += n;
	}
	//创建一个新节点 将图片数据保存在其中

	new->rgb = r;
	new->height = info.height;
	new->width = info.width;
	close(fd);

}

void showbmp(struct node *new)
{		

	// 打开LCD设备
	lcd = open("/dev/fb0", O_RDWR);
	// 获取LCD设备的硬件参数（分辨率、色深……）
	struct fb_var_screeninfo  vsinfo;
	bzero(&vsinfo, sizeof(vsinfo));
	ioctl(lcd, FBIOGET_VSCREENINFO, &vsinfo); // 将LCD设备参数信息放入svinfo中

	printf("屏幕分辨率: %d × %d\n", vsinfo.xres, vsinfo.yres);

	// 4，映射内存
	lcd_w = vsinfo.xres;
	lcd_h = vsinfo.yres;
	lcd_bpp = vsinfo.bits_per_pixel;
	lcdmem = mmap(NULL, lcd_w * lcd_h * lcd_bpp/8,
			PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);

	bzero(lcdmem, lcd_w*lcd_h*lcd_bpp/8);




	int w = lcd_w<new->width ? lcd_w : new->width;
	int h = lcd_h<new->height? lcd_h : new->height;

	int pad = (4-(new->width*3 % 4)) % 4; // pad = 0~3

	int img_line_size = new->width*3 + pad; // 图片一行的总字节数
	int lcd_line_size = lcd_w * lcd_bpp/8 ; // 显存一行的总字节数

	// 让 rgb_r 指向最后一行
	char *rgb_r = new->rgb + img_line_size*(new->height-1);
	char *lcdmem_r=lcdmem+lcd_line_size*(lcd_h/2-new->height/2)+(lcd_w/2-new->width/2)*lcd_bpp/8;
	bzero(lcdmem, 480*800*4);
	// 5，妥善地将BMP中的RGB数据搬到映射内存上
	int i,j;
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			memcpy(lcdmem_r+j*lcd_line_size+4*i, (rgb_r-j*img_line_size)+3*i, 3);
		}
	}
	printf("--------");
	// 6，释放相应资源

	// free(new->rgb);
	 close(lcd); 
}
void freelcd(void)
{	
	if(!first)
	{
		munmap(lcdmem, lcd_w * lcd_h * lcd_bpp/8);
		close(lcd);	
	}

	first = true;
}
