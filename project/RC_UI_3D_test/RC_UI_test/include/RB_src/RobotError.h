#ifndef __ROBOTERROR_H__
#define __ROBOTERROR_H__


#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        错误宏定义                                                         *
 *****************************************************************************/
#ifndef int8
#define int8 signed char
#endif
#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef U16
#define U16 unsigned short 
#endif

#ifndef U32
#define U32 unsigned int
#endif

#ifndef Boolean
#define Boolean unsigned short
#endif




#define public_function
#define private_function
#define public_variable

///////////////////////////////////////////////////////////////////// 报错处理宏
// [[ 通讯错误
#define ERR_COMM_LINK   	3000001	// Link通讯错误
#define ERR_COMM_NOMDT  	3000002	// 无MDT数据
#define ERR_GRIPCOMM    	3000003	// 手爪通讯错误
#define ERR_GRIPDISABLE 	2000004	// 手爪未使能
#define ERR_LINKAGEINIT 	3000005	// Linkage初始化错误
#define ERR_SERIALCOMM  	3000006	// 串口通讯错误
#define ERR_USERFRAMESET  	2000007	// 用户坐标系设置异常
#define ERR_COMM_DATA	  	3000008	// 通讯数据异常
#define ERR_COMM_ALM        3000009 // 伺服报警
#define ERR_COMM_DATA_TEST	  	3900008	// 通讯数据异常
// ]]

// [[ 程序错误
#define ERR_PROG_PARA   	2001000	// 输入运动参数有误
#define ERR_PROG_POINT  	2001001	// 输入点数据有误
#define ERR_PROG_PLIM   	2001002	// 输入点处于极限
#define ERR_PROG_PSINGU 	2001003	// 输入点处于奇异位形
#define ERR_PROG_POUT   	2001004	// 输入点超出工作空间
#define ERR_PROG_PINLIN 	2001005	// 圆弧三点共线
#define ERR_PROG_PCLOSE 	2001006	// 圆弧三点过近
#define ERR_PROG_PMIDERR    2001007 // 圆弧中间点错误
#define ERR_PROG_TABLE_ZONE   2001010  //转台旋转使用到过渡
// ]]

// [[ 规划错误
#define ERR_PLAN_BUFF		3002000	// 缓冲区错误
#define ERR_PLAN_NOENDLINE	2002001	// 无结尾行
#define ERR_PLAN_PLIM		2002002	// 位置极限
#define ERR_PLAN_NOINV		2002003	// 无逆解
#define ERR_PLAN_SPEED		2002004	// 加减速规划错误
#define ERR_PLAN_VELLIM		2002005	// 规划速度超限
#define ERR_PLAN_BUFF_EMPTY	3002006	// 缓冲区空
#define ERR_PLAN_NOMATRIX		2002007	// 无矩阵
#define ERR_PLAN_NOINVMATRIX		2002008	// 无逆矩阵
#define ERR_PLAN_LOSTCODE		2002018	// 指令ID丢失
#define ERR_PLAN_PUTPRJ		2002019	// 路径缓冲区指令ID丢失
#define ERR_PLAN_GETPRJ		2002020	// 轨迹缓冲区指令ID丢失
#define ERR_PLAN_ENQELEM		2002021	// 插补缓冲区入队指令ID丢失
#define ERR_PLAN_DEQELEM		2002022	// 插补缓冲区出队指令ID丢失
#define ERR_PLAN_DEQELEMLOST		2002023	// 插补缓冲区出队指令行丢失
#define ERR_PLAN_LOSTLINE		2002024	// 指令行丢失
// ]]

// [[ 运动错误
#define ERR_EMGSTOP			2003000	// 紧急停止
#define ERR_CMODESTOP		2003001	// 运动模式改变急停
#define ERR_USINGU			2003002	// J3奇异状态
#define ERR_BSINGU			2003003	// J5奇异状态
#define ERR_UNSINGU			1003004	// J3接近奇异位形
#define ERR_BNSINGU			1003005	// J5接近奇异位形
#define ERR_OWORKSPACE		2003006	// 超出工作空间
#define ERR_DATAEMPTY		2003007	// 数据空穴, 位置突变
#define ERR_INTERPMODE		2003008	// 插补模式错误
#define ERR_OTC_CIA_APPRCH	2003009	// 机器人即将进入干涉区
#define ERR_JOINT_NOSYNC	2003010	// 电机转角和关节值超差
// ]]

// [[ 速度极限
#define ERR_SVLIM			2004000	// J1轴速度超限
#define ERR_LVLIM			2004001	// J2轴速度超限
#define ERR_UVLIM			2004002	// J3轴速度超限
#define ERR_RVLIM			2004003	// J4轴速度超限
#define ERR_BVLIM			2004004	// J5轴速度超限
#define ERR_TVLIM			2004005	// J6轴速度超限
// ]]

// [[ 伺服错误
#define SV_SALM				2005000	// J1轴伺服报警
#define SV_LALM				2005001	// J2轴伺服报警
#define SV_UALM				2005002	// J3轴伺服报警
#define SV_RALM				2005003	// J4轴伺服报警
#define SV_BALM				2005004	// J5轴伺服报警
#define SV_TALM				2005005	// J6轴伺服报警
#define SV_NOZERO			2005006 // 零点丢失
#define SV_DISABLE			2005007 // disable
// ]] 

// [[ 软极限报警
#define OTS_SSLIMP   	 	2006001	// J1+软限位
#define OTS_LSLIMP			2006002	// J2+软限位
#define OTS_USLIMP			2006003	// J3+软限位
#define OTS_RSLIMP			2006004	// J4+软限位
#define OTS_BSLIMP			2006005	// J5+软限位
#define OTS_TSLIMP			2006006	// J6+软限位
#define OTS_T1SLIMP			2006007	// T1+软限位
#define OTS_T2SLIMP			2006008	// T2+软限位

#define OTS_SSLIMN			2006021	// J1-软限位
#define OTS_LSLIMN			2006022	// J2-软限位
#define OTS_USLIMN			2006023	// J3-软限位
#define OTS_RSLIMN			2006024	// J4-软限位
#define OTS_BSLIMN			2006025	// J5-软限位
#define OTS_TSLIMN			2006026	// J6-软限位
#define OTS_T1SLIMN			2006027	// T1-软限位
#define OTS_T2SLIMN			2006028	// T2-软限位


#define OTS_SNSLIMP 		1006001	// S+接近软极限, 报警, 并提前减速
#define OTS_LNSLIMP 		1006002	// L+接近软极限
#define OTS_UNSLIMP 		1006003	// U+接近软极限
#define OTS_RNSLIMP 		1006004	// R+接近软极限
#define OTS_BNSLIMP			1006005	// B+接近软极限
#define OTS_TNSLIMP 		1006006	// T+接近软极限
#define OTS_T1NSLIMP		1006007	// T1+接近软极限
#define OTS_T2NSLIMP 		1006008	// T2+接近软极限

#define OTS_SNSLIMN 		1006021	// S-接近软极限
#define OTS_LNSLIMN 		1006022	// L-接近软极限
#define OTS_UNSLIMN 		1006023	// U-接近软极限
#define OTS_RNSLIMN 		1006024	// R-接近软极限
#define OTS_BNSLIMN 		1006025	// B-接近软极限
#define OTS_TNSLIMN 		1006026	// T-接近软极限
#define OTS_T1NSLIMN 		1006027	// T1-接近软极限
#define OTS_T2NSLIMN 		1006028	// T2-接近软极限
// ]] 软极限报警

// [[ 示教错误
#define ERR_TEACH_COOR  	2007000	// 示教坐标系错误
#define ERR_TEACH_COOR_DATA  	2007001	// 示教坐标系错误
// ]]

// 干涉区报警
#define ERR_OTC_CIA_ENTER	2008000	// 机器人进入干涉区
#define ERR_OTC_CIA_DATA	2008001	// 干涉区设置数据异常

//　初始化错误
#define ERR_ARMInit			3009000	// ARM初始化错误
#define ERR_ZERO_LOST		3009001 // 机器人零点异常

// IO错误
#define ERR_IO_VALUE_OUT	2010001	// IO输出值错误
#define ERR_IO_VALUE_IN		2010002	// IO输入值错误
#define ERR_IO_TYPE			2010003	// IO点类型错误
#define ERR_IO_INDEX		2010004	// IO点编号错误
#define ERR_IO_WRITE		2010005	// IO写错误

#ifdef __cplusplus
}
#endif
#endif
