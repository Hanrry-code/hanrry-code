#include "hannan.h"

// ��Ҫ���ʹ�õı�����ʹ�þ�̬����
static int lcd;
static int lcd_w, lcd_h, lcd_bpp;
static struct fb_var_screeninfo  vsinfo;
static char *lcdmem;
static bool first = true;

void photo_key(char *bmp, int x, int y /* (x,y)��ͼƬ���Ͻǵ����� */)
{
	
	// 0������BMPͼƬ��ͷ����Ϣ����ȡ���������Ϣ
	int fd = open(bmp, O_RDWR);
	
	struct bitmap_header head;
	struct bitmap_info   info;

	bzero(&head, sizeof(head));
	bzero(&info, sizeof(info));
	read(fd, &head, sizeof(head));
	read(fd, &info, sizeof(info));

	// 1����ȡBMPͼƬ�ľ���ͼ�����ݣ�RGB��
	int rgb_size = head.size-sizeof(head)-sizeof(info);
	char *rgb = calloc(1, rgb_size);

	int n = 0;
	int total = 0;
	// ȷ�����ļ��е�RGB���ݶ���
	while(rgb_size > 0)
	{
		n = read(fd, rgb+total, rgb_size);

		rgb_size -= n;
		total    += n;
	}

	if(first)
	{
		// 2����LCD�豸
		lcd = open("/dev/fb0", O_RDWR);

		// 3����ȡLCD�豸��Ӳ���������ֱ��ʡ�ɫ�����
		bzero(&vsinfo, sizeof(vsinfo));
		ioctl(lcd, FBIOGET_VSCREENINFO, &vsinfo); // ��LCD�豸������Ϣ����vsinfo��

		
		// 4��ӳ���ڴ�
		lcd_w = vsinfo.xres;
		lcd_h = vsinfo.yres;
		lcd_bpp = vsinfo.bits_per_pixel;
		lcdmem = mmap(NULL, lcd_w * lcd_h * lcd_bpp/8,
				PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);

		first = false;
	}

	//bzero(lcdmem, lcd_w*lcd_h*lcd_bpp/8);
	int pad = (4-(info.width*3 % 4)) % 4; // pad = 0~3

	int img_line_size = info.width*3 + pad; // ͼƬһ�е����ֽ���
	int lcd_line_size = lcd_w * lcd_bpp/8 ; // �Դ�һ�е����ֽ���

	// �� rgb_r ָ�����һ��
	char *rgb_r = rgb + img_line_size*(info.height-1);

	// ���Դ�ָ��ָ��ָ������ʾλ�ã�x,y��
	char *tmp = lcdmem + (y*800+x) * 4;
	
	int w = (lcd_w-x)<info.width ? (lcd_w-x) : info.width;
	int h = (lcd_h-y)<info.height? (lcd_h-y) : info.height;

	// 5�����Ƶؽ�BMP�е�RGB���ݰᵽӳ���ڴ���
	for(int j=0; j<h; j++)
	{
		for(int i=0; i<w; i++)
		{
			memcpy(tmp+j*lcd_line_size+4*i, (rgb_r-j*img_line_size)+3*i, 3);
		}
	}

	// 6���ͷ���Ӧ��Դ
	free(rgb);
	close(fd);

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