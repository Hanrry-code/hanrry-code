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

	// 0������BMPͼƬ��ͷ����Ϣ����ȡ���������Ϣ
	fd = open(photograph, O_RDWR);

	struct bitmap_header head;
	struct bitmap_info  info;

	bzero(&head, sizeof(head));
	bzero(&info, sizeof(info));
	read(fd, &head, sizeof(head));
	read(fd, &info, sizeof(info));

	// 1����ȡBMPͼƬ�ľ���ͼ�����ݣ�RGB��
	int rgb_size = head.size-sizeof(head)-sizeof(info);
	r = calloc(1, rgb_size);

	int n = 0;
	int total = 0;
	// ȷ�����ļ��е�RGB���ݶ���
	while(rgb_size > 0)
	{
		n = read(fd, r+total, rgb_size);

		rgb_size -= n;
		total    += n;
	}
	//����һ���½ڵ� ��ͼƬ���ݱ���������

	new->rgb = r;
	new->height = info.height;
	new->width = info.width;
	close(fd);

}

void showbmp(struct node *new)
{		

	// ��LCD�豸
	lcd = open("/dev/fb0", O_RDWR);
	// ��ȡLCD�豸��Ӳ���������ֱ��ʡ�ɫ�����
	struct fb_var_screeninfo  vsinfo;
	bzero(&vsinfo, sizeof(vsinfo));
	ioctl(lcd, FBIOGET_VSCREENINFO, &vsinfo); // ��LCD�豸������Ϣ����svinfo��

	printf("��Ļ�ֱ���: %d �� %d\n", vsinfo.xres, vsinfo.yres);

	// 4��ӳ���ڴ�
	lcd_w = vsinfo.xres;
	lcd_h = vsinfo.yres;
	lcd_bpp = vsinfo.bits_per_pixel;
	lcdmem = mmap(NULL, lcd_w * lcd_h * lcd_bpp/8,
			PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);

	bzero(lcdmem, lcd_w*lcd_h*lcd_bpp/8);




	int w = lcd_w<new->width ? lcd_w : new->width;
	int h = lcd_h<new->height? lcd_h : new->height;

	int pad = (4-(new->width*3 % 4)) % 4; // pad = 0~3

	int img_line_size = new->width*3 + pad; // ͼƬһ�е����ֽ���
	int lcd_line_size = lcd_w * lcd_bpp/8 ; // �Դ�һ�е����ֽ���

	// �� rgb_r ָ�����һ��
	char *rgb_r = new->rgb + img_line_size*(new->height-1);
	char *lcdmem_r=lcdmem+lcd_line_size*(lcd_h/2-new->height/2)+(lcd_w/2-new->width/2)*lcd_bpp/8;
	bzero(lcdmem, 480*800*4);
	// 5�����Ƶؽ�BMP�е�RGB���ݰᵽӳ���ڴ���
	int i,j;
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			memcpy(lcdmem_r+j*lcd_line_size+4*i, (rgb_r-j*img_line_size)+3*i, 3);
		}
	}
	printf("--------");
	// 6���ͷ���Ӧ��Դ

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
