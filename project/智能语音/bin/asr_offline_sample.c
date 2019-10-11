#include "hannan.h"
#include "qisr.h"
#include "msp_cmn.h"
#include "msp_errors.h"
//#include "cJSON.h"
#define SAMPLE_RATE_16K     (16000)
#define SAMPLE_RATE_8K      (8000)
#define MAX_GRAMMARID_LEN   (32)
#define MAX_PARAMS_LEN      (1024)

const char * ASR_RES_PATH        = "fo|res/asr/common.jet"; //离线语法识别资源路径
const char * GRM_BUILD_PATH      = "res/asr/GrmBuilld"; //构建离线语法识别网络生成数据保存路径
const char * GRM_FILE            = "call.bnf"; //构建离线识别语法网络所用的语法文件
const char * LEX_NAME            = "contact"; //更新离线识别语法的contact槽（语法文件为此示例中使用的call.bnf）
typedef struct _UserData {
	int     build_fini; //标识语法构建是否完成
	int     update_fini; //标识更新词典是否完成
	int     errcode; //记录语法构建或更新词典回调错误码
	char    grammar_id[MAX_GRAMMARID_LEN]; //保存语法构建返回的语法ID
}UserData;


const char *get_audio_file(void); //选择进行离线语法识别的语音文件
int build_grammar(UserData *udata); //构建离线识别语法网络
int update_lexicon(UserData *udata); //更新离线识别语法词典
int run_asr(UserData *udata); //进行离线语法识别
int sockfd;
int connfd;
const char* get_audio_file(void)
{
	char buf[4*1024]={0};
	int read_ret = 1;
	int write_ret = 0;
	int read_total_num = 0;
	int write_total_num = 0;

	//创建一个wav文件
	
	int	fd = open("1.wav",O_RDWR|O_CREAT);
	lseek(fd,0, SEEK_SET);
	int fd_size;
	read(connfd, &fd_size, sizeof(fd_size));
	//读取数据
	while(read_ret)
	{
		bzero(buf, 4*1024);

		read_ret = read(connfd, buf, sizeof(buf));
		if(read_ret == -1)
			perror("read failed\n");
		write_ret = write(fd,buf,read_ret);

		read_total_num += read_ret;
		write_total_num += write_ret;
		if(read_total_num == fd_size)
			break;

	}
	close(fd);
	printf("read_total_num = %d\n",read_total_num);
	printf("write_total_num = %d\n",write_total_num);
	return "1.wav";
}

int build_grm_cb(int ecode, const char *info, void *udata)
{
	UserData *grm_data = (UserData *)udata;

	if (NULL != grm_data) {
		grm_data->build_fini = 1;
		grm_data->errcode = ecode;
	}

	if (MSP_SUCCESS == ecode && NULL != info) {
		printf("构建语法成功！ 语法ID:%s\n", info);
		if (NULL != grm_data)
			snprintf(grm_data->grammar_id, MAX_GRAMMARID_LEN - 1, info);
	}
	else
		printf("构建语法失败！%d\n", ecode);

	return 0;
}
int build_grammar(UserData *udata)
{
	FILE *grm_file                           = NULL;
	char *grm_content                        = NULL;
	unsigned int grm_cnt_len                 = 0;
	char grm_build_params[MAX_PARAMS_LEN]    = {NULL};
	int ret                                  = 0;

	grm_file = fopen(GRM_FILE, "rb");	
	if(NULL == grm_file) {
		printf("打开\"%s\"文件失败！[%s]\n", GRM_FILE, strerror(errno));
		return -1; 
	}

	fseek(grm_file, 0, SEEK_END);
	grm_cnt_len = ftell(grm_file);
	fseek(grm_file, 0, SEEK_SET);

	grm_content = (char *)malloc(grm_cnt_len + 1);
	if (NULL == grm_content)
	{
		printf("内存分配失败!\n");
		fclose(grm_file);
		grm_file = NULL;
		return -1;
	}
	fread((void*)grm_content, 1, grm_cnt_len, grm_file);
	grm_content[grm_cnt_len] = '\0';
	fclose(grm_file);
	grm_file = NULL;

	snprintf(grm_build_params, MAX_PARAMS_LEN - 1, 
			"engine_type = local, \
			asr_res_path = %s, sample_rate = %d, \
			grm_build_path = %s, ",
			ASR_RES_PATH,
			SAMPLE_RATE_16K,
			GRM_BUILD_PATH
		);
	ret = QISRBuildGrammar("bnf", grm_content, grm_cnt_len, grm_build_params, build_grm_cb, udata);

	free(grm_content);
	grm_content = NULL;

	return ret;
}
int update_lex_cb(int ecode, const char *info, void *udata)
{
	UserData *lex_data = (UserData *)udata;

	if (NULL != lex_data) {
		lex_data->update_fini = 1;
		lex_data->errcode = ecode;
	}

	if (MSP_SUCCESS == ecode)
		printf("更新词典成功！\n");
	else
		printf("更新词典失败！%d\n", ecode);

	return 0;
}

int update_lexicon(UserData *udata)
{
	const char *lex_content                   = "丁伟\n黄辣椒";
	unsigned int lex_cnt_len                  = strlen(lex_content);
	char update_lex_params[MAX_PARAMS_LEN]    = {NULL}; 

	snprintf(update_lex_params, MAX_PARAMS_LEN - 1, 
			"engine_type = local, text_encoding = UTF-8, \
			asr_res_path = %s, sample_rate = %d, \
			grm_build_path = %s, grammar_list = %s, ",
			ASR_RES_PATH,
			SAMPLE_RATE_16K,
			GRM_BUILD_PATH,
			udata->grammar_id);
	return QISRUpdateLexicon(LEX_NAME, lex_content, lex_cnt_len, update_lex_params, update_lex_cb, udata);
}

int run_asr(UserData *udata)
{
	char asr_params[MAX_PARAMS_LEN]    = {NULL};
	char *rec_rslt               = NULL;
	const char *session_id             = NULL;
	const char *asr_audiof             = NULL;
	FILE *f_pcm                        = NULL;
	char *pcm_data                     = NULL;
	long pcm_count                     = 0;
	long pcm_size                      = 0;
	int last_audio                     = 0;
	int aud_stat                       = MSP_AUDIO_SAMPLE_CONTINUE;
	int ep_status                      = MSP_EP_LOOKING_FOR_SPEECH;
	int rec_status                     = MSP_REC_STATUS_INCOMPLETE;
	int rss_status                     = MSP_REC_STATUS_INCOMPLETE;
	int errcode                        = -1;

	asr_audiof = get_audio_file();
	f_pcm = fopen(asr_audiof, "rb");
	if (NULL == f_pcm) {
		printf("打开\"%s\"失败！[%s]\n", f_pcm, strerror(errno));
		goto run_error;
	}
	fseek(f_pcm, 0, SEEK_END);
	pcm_size = ftell(f_pcm);
	fseek(f_pcm, 0, SEEK_SET);
	pcm_data = (char *)malloc(pcm_size);
	if (NULL == pcm_data)
		goto run_error;
	fread((void *)pcm_data, pcm_size, 1, f_pcm);
	fclose(f_pcm);
	f_pcm = NULL;

	//离线语法识别参数设置
	snprintf(asr_params, MAX_PARAMS_LEN - 1, 
			"engine_type = local, \
			asr_res_path = %s, sample_rate = %d, \
			grm_build_path = %s, local_grammar = %s, \
			result_type = json, result_encoding = UTF-8, ",
			ASR_RES_PATH,
			SAMPLE_RATE_16K,
			GRM_BUILD_PATH,
			udata->grammar_id
		);
	session_id = QISRSessionBegin(NULL, asr_params, &errcode);
	if (NULL == session_id)
		goto run_error;
	printf("开始识别...\n");

	while (1) {
		unsigned int len = 6400;

		if (pcm_size < 12800) {
			len = pcm_size;
			last_audio = 1;
		}

		aud_stat = MSP_AUDIO_SAMPLE_CONTINUE;

		if (0 == pcm_count)
			aud_stat = MSP_AUDIO_SAMPLE_FIRST;

		if (len <= 0)
			break;

		printf(">");
		fflush(stdout);
		errcode = QISRAudioWrite(session_id, (const void *)&pcm_data[pcm_count], len, aud_stat, &ep_status, &rec_status);
		if (MSP_SUCCESS != errcode)
			goto run_error;

		pcm_count += (long)len;
		pcm_size -= (long)len;
		
		//检测到音频结束
		if (MSP_EP_AFTER_SPEECH == ep_status)
			break;

		usleep(150 * 1000); //模拟人说话时间间隙
	}
	//主动点击音频结束
	QISRAudioWrite(session_id, (const void *)NULL, 0, MSP_AUDIO_SAMPLE_LAST, &ep_status, &rec_status);

	free(pcm_data);
	pcm_data = NULL;
	int send ;
	//获取识别结果
	while (MSP_REC_STATUS_COMPLETE != rss_status && MSP_SUCCESS == errcode) {
		rec_rslt = QISRGetResult(session_id, &rss_status, 0, &errcode);
		usleep(150 * 1000);
	}
	printf("\n识别结束：\n");
	printf("=============================================================\n");
	if (NULL != rec_rslt)
	{
		printf("%s\n", rec_rslt);
		send = 1;
		write(connfd,&send,sizeof(send));
		//将获取到的结果发回去
		char buf_send[4*1024]={0};

		int write_ret1 = 0;

		write_ret1 = write(connfd,rec_rslt,sizeof(buf_send));
		printf("write_ret1 = %d\n",write_ret1);

	}
		
	else
		
		{
			printf("没有识别结果！\n");
			send = 0;
			write(connfd,&(send),sizeof(send));
		}
	printf("=============================================================\n");
	

	
	

	goto run_exit;

run_error:
	if (NULL != pcm_data) {
		free(pcm_data);
		pcm_data = NULL;
	}
	if (NULL != f_pcm) {
		fclose(f_pcm);
		f_pcm = NULL;
	}
run_exit:
	QISRSessionEnd(session_id, NULL);
	return errcode;
}



int main(int argc, char* argv[])
{
	// 1，创建TCP套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);


	// 2，准备地址结构体
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	bzero(&addr, len);

	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(atoi(argv[1]));

	// 3，绑定地址到指定的通信端点
	bind(sockfd, (struct sockaddr *)&addr, len);

	// 4，设定监听状态
	// 注意:
	//      只有处于监听状态的TCP套接字，才能接受对端的链接请求
	//      参数3规定的是该通信端点能同时接收连接请求的数量
	//      注意不是链接请求的总数
	listen(sockfd, 3);

	// 5，静静地等待对端的链接...
	struct sockaddr_in peeraddr;
	len = sizeof(peeraddr);
	bzero(&peeraddr, len);
	connfd = accept(sockfd, (struct sockaddr *)&peeraddr, &len);

	printf("连接成功，对端地址: %s: %hu\n",
			inet_ntoa(peeraddr.sin_addr),
			ntohs(peeraddr.sin_port));


	const char *login_config    = "appid = 5d8ad5c1"; //登录参数
	UserData asr_data; 
	int ret                     = 0 ;


	ret = MSPLogin(NULL, NULL, login_config); //第一个参数为用户名，第二个参数为密码，传NULL即可，第三个参数是登录参数
	if (MSP_SUCCESS != ret) {
		printf("登录失败：%d\n", ret);
		goto exit;
	}

	memset(&asr_data, 0, sizeof(UserData));
	printf("构建离线识别语法网络...\n");
	ret = build_grammar(&asr_data);  //第一次使用某语法进行识别，需要先构建语法网络，获取语法ID，之后使用此语法进行识别，无需再次构建
	if (MSP_SUCCESS != ret) {
		printf("构建语法调用失败！\n");
		goto exit;
	}
	while (1 != asr_data.build_fini)
		usleep(300 * 1000);
	if (MSP_SUCCESS != asr_data.errcode)
		goto exit;
	printf("离线识别语法网络构建完成，开始识别...\n");	

	
	while(1)
	{
		//调用识别函数
		ret = run_asr(&asr_data);
	
		 if (MSP_SUCCESS != ret) {
			printf("离线语法识别出错: %d \n", ret);
			goto exit;
		}

		printf("更新离线语法词典...\n");
		ret = update_lexicon(&asr_data);  //当语法词典槽中的词条需要更新时，调用QISRUpdateLexicon接口完成更新
		if (MSP_SUCCESS != ret) {
			printf("更新词典调用失败！\n");
			goto exit;
		}
		while (1 != asr_data.update_fini)
			usleep(300 * 1000);
		if (MSP_SUCCESS != asr_data.errcode)
			goto exit;
		printf("更新离线语法词典完成，开始识别...\n");
		if (MSP_SUCCESS != ret) {
			printf("离线语法识别出错: %d \n", ret);
			goto exit;
		}

	}

exit:
	MSPLogout();
 
	return 0;
}

