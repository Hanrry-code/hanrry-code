#include "head4audio.h"
#include "hannan.h"
// 根据本系统的具体字节序处理的存放格式
#if   __BYTE_ORDER == __LITTLE_ENDIAN

#define RIFF ('F'<<24 | 'F'<<16 | 'I'<<8 | 'R'<<0)
#define WAVE ('E'<<24 | 'V'<<16 | 'A'<<8 | 'W'<<0)
#define FMT  (' '<<24 | 't'<<16 | 'm'<<8 | 'f'<<0)
#define DATA ('a'<<24 | 't'<<16 | 'a'<<8 | 'd'<<0)

#define LE_SHORT(val) (val) 
#define LE_INT(val)   (val) 

#elif __BYTE_ORDER == __BIG_ENDIAN

#define RIFF ('R'<<24 | 'I'<<16 | 'F'<<8 | 'F'<<0)
#define WAVE ('W'<<24 | 'A'<<16 | 'V'<<8 | 'E'<<0)
#define FMT  ('f'<<24 | 'm'<<16 | 't'<<8 | ' '<<0)
#define DATA ('d'<<24 | 'a'<<16 | 't'<<8 | 'a'<<0)

#define LE_SHORT(val) bswap_16(val) 
#define LE_INT(val)   bswap_32(val) 

#endif

wav_format *wav = NULL;
int fd;
int wav_fd;
#define DURATION_TIME 3
bool bow=1;
bool start=1;
pcm_container *sound ;
// 准备WAV格式参数
void prepare_wav_params(wav_format *wav)
{
	wav->format.fmt_id = FMT;
	wav->format.fmt_size = LE_INT(16);
	wav->format.fmt = LE_SHORT(WAV_FMT_PCM);
	wav->format.channels = LE_SHORT(1);         // 声道数目
	wav->format.sample_rate = LE_INT(16000);    // 采样频率
	wav->format.bits_per_sample = LE_SHORT(16); // 量化位数
	wav->format.block_align = LE_SHORT(wav->format.channels
			* wav->format.bits_per_sample/8);
	wav->format.byte_rate = LE_INT(wav->format.sample_rate
			* wav->format.block_align);
	wav->data.data_id = DATA;
	/* wav->data.data_size = LE_INT(DURATION_TIME
	 * wav->format.byte_rate); // 码率 */
	wav->head.id = RIFF;
	wav->head.format = WAVE;
	wav->head.size = LE_INT(36 + wav->data.data_size);
}

// 设置WAV格式参数
void set_wav_params(pcm_container *sound, wav_format *wav)
{
	// 1：定义并分配一个硬件参数空间
	snd_pcm_hw_params_t *hwparams;
	snd_pcm_hw_params_alloca(&hwparams);

	// 2：初始化硬件参数空间
	snd_pcm_hw_params_any(sound->handle, hwparams);

	// 3：设置访问模式为交错模式（即帧连续模式）
	snd_pcm_hw_params_set_access(sound->handle, hwparams,
			SND_PCM_ACCESS_RW_INTERLEAVED);

	// 4：设置量化参数
	snd_pcm_format_t pcm_format = SND_PCM_FORMAT_S16_LE;
	snd_pcm_hw_params_set_format(sound->handle,
			hwparams, pcm_format);
	sound->format = pcm_format;

	// 5：设置声道数目
	snd_pcm_hw_params_set_channels(sound->handle,
			hwparams, LE_SHORT(wav->format.channels));
	sound->channels = LE_SHORT(wav->format.channels);

	// 6：设置采样频率
	// 注意：最终被设置的频率被存放在来exact_rate中
	uint32_t exact_rate = LE_INT(wav->format.sample_rate);
	snd_pcm_hw_params_set_rate_near(sound->handle,
			hwparams, &exact_rate, 0);

	// 7：设置buffer size为声卡支持的最大值
	snd_pcm_uframes_t buffer_size;
	snd_pcm_hw_params_get_buffer_size_max(hwparams,
			&buffer_size);
	snd_pcm_hw_params_set_buffer_size_near(sound->handle,
			hwparams, &buffer_size);

	// 8：根据buffer size设置period size
	snd_pcm_uframes_t period_size = buffer_size / 4;
	snd_pcm_hw_params_set_period_size_near(sound->handle,
			hwparams, &period_size, 0);

	// 9：安装这些PCM设备参数
	snd_pcm_hw_params(sound->handle, hwparams);

	// 10：获取buffer size和period size
	// 注意：他们均以 frame 为单位 （frame = 声道数 * 量化级）
	snd_pcm_hw_params_get_buffer_size(hwparams,
			&sound->frames_per_buffer);
	snd_pcm_hw_params_get_period_size(hwparams,
			&sound->frames_per_period, 0);

	// 11：保存一些参数
	sound->bits_per_sample =
		snd_pcm_format_physical_width(pcm_format);
	sound->bytes_per_frame =
		sound->bits_per_sample/8 * wav->format.channels;

	// 12：分配一个周期数据空间
	sound->period_buf =
		(uint8_t *)calloc(1,
				sound->frames_per_period * sound->bytes_per_frame);
}

snd_pcm_uframes_t read_pcm_data(pcm_container *sound, snd_pcm_uframes_t frames)
{
	snd_pcm_uframes_t exact_frames = 0;
	snd_pcm_uframes_t n = 0;

	uint8_t *p = sound->period_buf;
	while(frames > 0)	
	{
		n = snd_pcm_readi(sound->handle, p, frames);

		frames -= n;
		exact_frames += n;
		p += (n * sound->bytes_per_frame);
	}

	return exact_frames;
}

uint32_t total_bytes = 0;

// 从PCM设备录取音频数据，并写入fd中
void recorder(int fd, pcm_container *sound, wav_format *wav)
{
	// 1：写WAV格式的文件头
	/*
	   write(fd, &wav->head, sizeof(wav->head));
	   write(fd, &wav->format, sizeof(wav->format));
	   write(fd, &wav->data, sizeof(wav->data));
	   */
	// 2：写PCM数据
	//uint32_t total_bytes = wav->data.data_size;
	uint32_t total_bytes = 0;
	//lseek(fd,SEEK_SET,sizeof(wav->head)+sizeof(wav->format)+sizeof(wav->data));
	while(1)
	{
		
		//uint32_t total_frames = total_bytes / (sound->bytes_per_frame)/*确定值*/;
		snd_pcm_uframes_t n = sound->frames_per_period;/*确定值*/

		uint32_t frames_read = read_pcm_data(sound, n);
		write(fd, sound->period_buf, frames_read * sound->bytes_per_frame);
		total_bytes += (frames_read * sound->bytes_per_frame);
		if(0==bow)
		{
			bow = 1;
			break;
		}
			
	}
	lseek(fd,SEEK_SET,0);
	wav->data.data_size = total_bytes;
	write(fd, &wav->head, sizeof(wav->head));
	write(fd, &wav->format, sizeof(wav->format));
	write(fd, &wav->data, sizeof(wav->data));
}

void *click(void *arg)
{
	// 4: 开始从PCM设备录制音频数据
	//    并且以WAV格式写到fd中
	recorder(wav_fd, sound, wav);
	
	pthread_exit(0);
}

int show_id(char *json)
{
	//printf("%d\n",__LINE__);
	cJSON *root = cJSON_Parse(json);
	cJSON *ws = cJSON_GetObjectItem(root, "ws");
	cJSON *wsi = cJSON_GetArrayItem(ws, 0);
	cJSON *cw = cJSON_GetObjectItem(wsi, "cw");
	cJSON *cwi = cJSON_GetArrayItem(cw, 0);
	cJSON *id = cJSON_GetObjectItem(cwi, "id");
	return id->valueint;

}
void recorder_make_wav(void)
{

	printf("请输入按下说话\n");

	
	// 1：打开WAV格式文件
	wav_fd = open("record.wav", O_CREAT|O_WRONLY|O_TRUNC, 0777);
	if(wav_fd == -1)	
	{
		perror("open() error");
		exit(1);
	}
	
	// 2: 打开PCM设备文件
	sound = calloc(1, sizeof(pcm_container));
	int ret = snd_pcm_open(&sound->handle, "default",
			SND_PCM_STREAM_CAPTURE, 0);
	if(ret != 0)
	{
		printf("[%d]: %d\n", __LINE__, ret);
		perror("snd_pcm_open( ) failed");
		exit(1);
	}

	// 3: 准备并设置WAV格式参数
	wav = calloc(1, sizeof(wav_format)); // 头
	prepare_wav_params(wav);
	set_wav_params(sound, wav);
	
	
	int tp=open("/dev/input/event0",O_RDWR);
	struct input_event buf_1;
	
	while(1)
	{
		bzero(&buf_1, sizeof(buf_1));
		read(tp,&buf_1,sizeof(buf_1));

		
		if(buf_1.type==EV_KEY)
		{
			if(buf_1.code == BTN_TOUCH)
			{
				if(buf_1.value>0)
				{
					pthread_t tid;
					pthread_create(&tid, NULL, click, NULL);
					
				}
				if(buf_1.value==0)
				{	
					bow=0;
					printf("松开\n");
					close(tp);
					close(wav_fd);
					break;
				}
			}
		}
	}
	
	

	// 5: 释放相关资源
	snd_pcm_drain(sound->handle);
	snd_pcm_close(sound->handle);
	

	free(sound->period_buf);
	free(sound);
	free(wav);
	close(wav_fd);
	close(ret);
	/* //播放该音频
	char cmd_buf[64]={0};

	sprintf(cmd_buf,"aplay record.wav \n");
	system(cmd_buf);
 */
}
