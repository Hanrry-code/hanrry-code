#ifndef __BMP_H_
#define __BMP_H_
#include "hannan.h"

#define LCD "/dev/fb0"

#define BACKGROUND "./res/bmp/background.bmp"
#define BAR        "./res/bmp/bar.bmp"
#define LOGO       "./res/bmp/logo.bmp"
#define KEYON      "./res/bmp/key_on.bmp"
#define KEYOFF     "./res/bmp/key_off.bmp"


struct bitmap_header
{
	int16_t type;
	int32_t size; // �����ļ���С
	int16_t reserved1;
	int16_t reserved2;
	int32_t offbits; // bmpͼ������ƫ����
}__attribute__((packed));

struct bitmap_info
{
	int32_t size; // ���ṹ��С	
	int32_t width; // ��λ������
	int32_t height;// ��λ������
	int16_t planes; // ��Ϊ��

	int16_t bit_count; // ɫ��:24��1����=24λ=3�ֽڣ�
	int32_t compression;
	int32_t size_img; // bmp���ݴ�С��������4��������
	int32_t X_pel;
	int32_t Y_pel;
	int32_t clrused;
	int32_t clrImportant;
}__attribute__((packed));

struct rgb_quad
{
	int8_t blue;
	int8_t green;
	int8_t red;
	int8_t reserved;
}__attribute__((packed));


struct image_info
{
	int width;
	int height;
	int pixel_size;
};

void display(char *bmpfile, int x, int y);
void freelcd(void);
void photo_piano(char *bmp, int x, int y /* (x,y)��ͼƬ���Ͻǵ����� */);
void photo_key(char *bmp, int x, int y /* (x,y)��ͼƬ���Ͻǵ����� */);
void photo(char *cd_bmp);
#endif
