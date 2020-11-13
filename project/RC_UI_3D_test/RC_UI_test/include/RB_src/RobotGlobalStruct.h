#ifndef __ROBOTGLOBALSTRUCT_H__
#define __ROBOTGLOBALSTRUCT_H__


#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        宏定义                                                             *
 *****************************************************************************/
#include "RobotError.h"
#include "Communicate.h"



#define RELEASE_MODE		0	//正常运行发布版
#define PC_TEST_MODE		1	//PC裸机测试版
#define OFFLINE_TEST_MODE	2	//内部脱机测试版
#define DSP_STATE_TEST			//测试DSP内部状态用
#define MaxServoNum			7	//最大从站数，用于内部脱机测试版
#define IOBoard_EN			1	// IO从站是否有效

#define DebugIfLostLine          0

//#define PROGRAM_VERSION OFFLINE_TEST_MODE //RELEASE_MODE//OFFLINE_TEST_MODE//

#define ARM_WAIT_DELAY 1 //0xFFFFFFFF

//#ifndef TEST_ROBOT_CONTROL  // 测试专用
//#define TEST_ROBOT_CONTROL
//#endif

#define MaxCompensatePulse        (100*gs_State.Motor_Precision[i]/10000)

#define PeriodCompensatePulse        (2*gs_State.Motor_Precision[i]/10000)

#define MAX_INTRFZONE_NUM 6
#define MAX_USERFRAME_NUM 10

/* 循环数组的前一个元素下标 */
#define Array_PreID(CurrID, Array_Size) (((CurrID) > 0) ? ((CurrID) - 1) : ((Array_Size) - 1))

// [[ 插补参数
#define INTERP_MOTION_JERK     10000     // 加加速度
#define INTERP_JOINT_DEGREE        4     // 关节插补曲线Degree
#define INTERP_FIFO_LENTH          40//24//12// 6// 插补点队列长度
#define INTERP_JOINT_MAXVELPCT  0.95     // 关节 插补最大速度百分比, 95%
#define INTERP_TEACH_MAXVELPCT  0.10     // 示教最大速度百分比, 20%
#define INTERP_TEACH_MAXCVEL     250     // 笛卡尔示教最大速度, mm/s
#define INTERP_TEACH_MAXGVEL      10     // 笛卡尔示教最大姿态速度, deg/s
#define INTERP_ZONE_GRADE          4     // 过渡段最大等级
#define INTERP_ZONE_ACCPCT       1.0     // 过渡段加速度百分比, 100%
#define INTERP_SINGULARITY_ZONE  5.0     // 奇异区域大小, deg
#define JOINT_CART_TRANSF_EN	   1	 // 关节与笛卡尔过渡开关
// ]] 

// [[ 系统参数
#define MOF           8          // 最大机器人自由度+转台自由度

extern int DOF;  //机器人轴数+转台自由度

//#if PROGRAM_VERSION==RELEASE_MODE||PROGRAM_VERSION==OFFLINE_TEST_MODE
#define INTERP_T	   0.004     // 插补周期,s
#define POS_T          0.001     // 位控周期,s
//#else
//#define INTERP_T       0.016     // (test)插补周期,s
//#define POS_T          0.004     // (test)位控周期,s
//#endif
#define RT_LITTLE    0.000001    // 系统可识别的最小正量
#define SERR          0.00001    // 误差允许范围
#define POS_SERR      0.00036    // 关节位置误差允许范围, 1cts - 0.00036(减速比100)
#define POS_PRECISION       1    // 轴位置精度, 伺服相关
#ifndef PI
#define PI      3.1415926535898  // 圆周率
#endif
#define PI2     6.2831853071796  // 2倍圆周率  
#define PI_RAD  0.0174532925199  // 角度转换为弧度参数
#define PI_DEG 57.2957795130823  // 弧度转换为角度参数
// ]]
#ifndef ERR_STOP_T
#define ERR_STOP_T      0.5//  1.000 //秒s
#endif

// [[ 运动状态
#define RUN_MODE_TEACH     1     // 示教模式
#define RUN_MODE_AUTO      2     // 再现模式
#define RUN_MODE_6DFORCE      3     // 6维力传感器拖动 模式
#define RUN_MODE_ERR       0     // 错误模式
#define RUN_DIR_POS        1     // 正方向
#define RUN_DIR_STOP       0     // 无方向
#define RUN_DIR_NEG       -1     // 负方向
#define RUN_STATE_RUNNING  1     // 正在运动
#define RUN_STATE_STOP     0     // 停止
#define RUN_STOPMODE_HOLD  0     // 暂停
#define RUN_STOPMODE_STOP  1     // 停止
#define RUN_LIM_POS        1     // 正极限
#define RUN_LIM_NOT        0     // 无极限
#define RUN_LIM_NEG       -1     // 负极限
#define RUN_SIN_YES        1     // 奇异状态
#define RUN_SIN_NO         0     // 非奇异

#define TEACH_STOP 1
#define TEACH_RUN  2
// ]]

// [[ 坐标系
// [[ 示教坐标系 - 速度模式/位置模式
#define COORDINATE_JOINT_VEL   1    // 关节坐标系
#define COORDINATE_WORLD_VEL   2    // 世界坐标系
#define COORDINATE_TOOL_VEL    3    // 工具坐标系
#define COORDINATE_USER_VEL    4    // 用户坐标系

	#define COORDINATE_TABLE_VEL   5    // 转台坐标系
#define COORDINATE_JOINT_POS  11    // 关节坐标系
#define COORDINATE_WORLD_POS  12    // 世界坐标系
#define COORDINATE_TOOL_POS   13    // 工具坐标系
#define COORDINATE_USER_POS   14    // 用户坐标系
	#define COORDINATE_TABLE_POS  15    // 转台坐标系
// ]]

// [[ 轴状态
#define MOTOR_ENABLE       1     // 使能
#define MOTOR_DISABLE      0     // 非使能
// ]]


// [[ 程序相关
#define PROG_MODE_MOVE         1     // Move
#define PROG_MODE_IO           2     // IO
#define PROG_MODE_DELAY        3     // Delay
#define PROG_MODE_NOTHING      4     // 非程序行
#define PROG_MODE_WAIT      5    // Wait
#define PROG_MODE_WELD      10    // 焊接
#define PROG_MODE_PULSE    12
#define PROG_IOMODE_Ds   8
#define PROG_IOMODE_De   9

#define PROG_order_ARCON    1  
#define PROG_order_ARCOFF    2 
#define PROG_order_ARCCT    3 
#define PROG_order_ARCSET    4 
#define PROG_order_AWELD    5 
#define PROG_order_VWELD    6 
#define PROG_order_ARCSETAVP    11 
#define PROG_order_ARCSETACC    12
#define PROG_order_ARCSETVEL    13


#define PROG_DsorDe_DisDs      1    // 焊接
#define PROG_DsorDe_DisDe      2    // 焊接
#define PROG_DsorDe_DisDsSlow      3    // 焊接
#define PROG_DsorDe_DisDeSlow      4   // 焊接
#define PROG_DsorDe_TimeDs      8   // 焊接
#define PROG_DsorDe_TimeDe      9    // 焊接
#define PROG_DsorDe_TimeDsSlow     10    // 焊接
#define PROG_DsorDe_TimeDeSlow      11   // 焊接

#define PROG_INTERP_JOINT      1     // 关节插补
#define PROG_INTERP_LINEAR     2     // 直线插补
#define PROG_INTERP_ARC        3     // 圆弧插补
#define PROG_INTERP_CIRCLE     4     // 整圆插补
#define PROG_INTERP_PARABOLA   5     // 抛物线插补 
#define PROG_INTERP_QUINTIC    6     // 五次多项式插补

#define PROG_VELMODE_EULER     1  // 欧拉角速度模式
#define PROG_VELMODE_ANGLE     2  // 角速度模式

#define PROG_MARK_MIDLINE      0     // 中间行
#define PROG_MARK_FIRSTLINE    0     // 首行
#define PROG_MARK_LASTLINE     3     // 末行
#define PROG_MARK_SINGLELINE   1     // 单行
#define PROG_MARK_CONTINUE	   2     // 单行
#define PROG_COMM_CANREAD      2     // 程序可读
#define PROG_COMM_READOVER     3     // 读程序完成
#define PROG_RUN_NOTSTART      0     // 未运行
#define PROG_RUN_ON            1     // 正在运行
#define PROG_RUN_OVER          2     // 运动结束
#define PROG_RUN_STOP          3     // 运动停止
#define PROG_RUN_ERROR        -1     // 运动错误

#define PROG_PLAN_NODATA       1     // 无数据
#define PROG_PLAN_WAITING      2     // 等待
#define PROG_PLAN_PROCESSING   3     // 程序正在规划
#define PROG_PLAN_COMPLETED    4     // 程序规划完成

#define PROG_TRANSMODE_YES     1     // 过渡段
#define PROG_TRANSMODE_NO      0     // 非过渡段
// ]]

// [[状态常量宏定义
#define STATE_COMPLETED			 0		// 代码处理完成
#define STATE_BLOCKCOMPLETED	 1		// 代码行完成
#define STATE_FILECOMPLETED		 2		// 代码文件完成
#define STATE_PROCESSING		 3		// 代码正在处理
#define STATE_WAITING			 4		// 等待下载代码文件
#define STATE_FEEDHOLD			 5		// 暂停
#define STATE_RESET			     8		// 复位
#define STATE_WARNING            9      // 警告
#define STATE_NOHOME            10      // 非回零
#define STATE_DECPROCESS		11      // 
// ]]


// IO相关
#define AOUT_VOLT_MAX			10
#define AIN_VOLT_MAX			10
#define ANALOG_PREC				4096	// 10位精度


#define NMI  0
#define TIMER1  1
#define TIMER2  2
#define IDLE  3
#define ON   1
#define OFF  0

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

#define SYSTEM_OK    0   // 系统正常
#define SYSTEM_ERR  -1   // 系统有误

#ifndef SYSTEM_TRUE
#define SYSTEM_TRUE  1
#endif
#ifndef SYSTEM_FALSE
#define SYSTEM_FALSE 0
#endif
#define Square(n)   ((n) * (n))              // 平方
#define Cube(n)     ((n) * (n) * (n))        // 立方

#ifndef Max
#define Max(a,b)    (((a) > (b)) ? (a) : (b))
#endif
#define Max3(a,b,c) Max(Max(a,b), (c))
#ifndef Min
#define Min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

// DSP定时器，单位-POS_T插补周期
typedef struct _dsp_Timer
{
	U16 Count[4];
	/*U16 NmiCount;
	U16 Timer1Count;
	U16 Timer2Count;
	U16 IdleCount;*/
	
}DSP_Timer;

#ifndef CARTESIANPOSE
#define CARTESIANPOSE
// 机器人位姿表示：笛卡尔坐标系表示
typedef struct _cartesianPose
{
	double X;     // 位置X,mm
	double Y;     // 位置Y,mm
	double Z;     // 位置Z,mm
	double W;     // 姿态W,deg
	double P;     // 姿态P,deg
	double R;     // 姿态R,deg
}CartesianPose;
#endif

#ifndef JOINTPOSE
#define JOINTPOSE
// 机器人关节角度表示：关节坐标系表示
typedef struct _jointPose
{
	double S;      // 轴S转角,deg
	double L;      // 轴L转角,deg
	double U;      // 轴U转角,deg
	double R;      // 轴R转角,deg
	double B;      // 轴B转角,deg
	double T;      // 轴T转角,deg
}JointPose;
#endif

#ifndef LINKDIMENSION
#define LINKDIMENSION
// 机器人连杆参数结构
typedef struct _linkDimension
{
	double A1;           // a1,mm
	double A2;           // a2,mm
	double A3;           // a3,mm
	double D3;           // d3,mm
	double D4;           // d4,mm
	double Df;           // df,mm
	
}LinkDimension;
#endif

#ifndef PROGRAMINFORMSTRUCT
#define PROGRAMINFORMSTRUCT
// 程序状态
typedef struct _programInformStruct
{
	int Prog_State; // 1. 运动：当前程序运动状态, 0无运行, 1正在运行, 2运动结, 其它-运动错误
	                // 2. 规划：0正常, 其它-规划错误。行号和段号只在规划错误时有效
	int CurrLine_State;	//当前行状态, 0 无运行, 1 正在运行, 2 运动结束, 其它-运动错误
    // 程序名
    // 显示用到
    char name[20];
	
    // 译码的部编号
    // 实时同步用到
    unsigned int decode_id ;
	int Prog_SequNum;// 所属序段号
	int Prog_LineNum;// 所属程序行号
	int IfTransSeg;  // 是否是过渡段
}ProgramInformStruct;
#endif


#ifndef TABLECONFIGT
#define TABLECONFIGT
//转台配置
typedef struct _TableConfigT
{
	CartesianPose Pos1;  //第1轴坐标系
	CartesianPose Pos2;  //第2轴坐标系
}TableConfigT;
#endif

typedef struct _globalState
{
/////////////////////////////////////////////////////////////////////// 参数设置
	int Acc_Time;              // 加速时间, ms

// [[ 笛卡尔
	double Car_MaxPVel;          // 笛卡尔位置最大速度, mm/s
	double Car_MaxGVel;          // 笛卡尔姿态最大速度, deg/s
	double Car_MaxPAcc;          // 笛卡尔位置加速度
	double Car_MaxGAcc;          // 笛卡尔姿态加速度
	double Car_StopPDec;         // 笛卡尔位置停止减速度
	double Car_StopGDec;         // 笛卡尔姿态停止减速度
	LinkDimension Robot_Link;    // 机器人连杆参数
	CartesianPose Robot_Tool;    // 工具坐标系参数
	CartesianPose Robot_User;    // 用户坐标系参数
// ]] 笛卡尔

// [[ 关节空间
	double Joint_MaxVel[MOF];    // 关节最大速度限制, deg/s*s
	double Joint_StopDec[MOF];   // 关节停止减速度, deg/s*s
	double Joint_PLim[MOF];      // 关节正极限, deg
	double Joint_NLim[MOF];      // 关节负极限, deg
	double Joint_MaxAcc[MOF];    // 关节最大加速度, deg/s*s
// ]] 关节空间

// [[ 轴空间
	double Motor_Ratio[MOF];     // 轴减速比
	double Motor_AbsZero[MOF];   // 轴绝对零点, 电机转角
	int Motor_Precision[MOF];    // 轴精度, cts/round
	int Motor_Dir[MOF];          // 轴方向, "1"-电机方向与关节方向一致, "-1"-不一致
// ]] 轴空间

/////////////////////////////////////////////////////////////////////// 反馈数据
	CartesianPose Car_ActPos; // 机器人实际位姿
	double Joint_ActPos[MOF]; // 关节实际位置
	double Joint_ActVel[MOF]; // 关节实际速度
	double Motor_ActCurr[MOF];// 轴实际电流
	double Motor_ActPos[MOF]; // 轴实际转角
	double Joint_CurrentPos[MOF]; // 路径规划的当前位置
	double Joint_CalculPos[MOF];
	double Car_ActVel[MOF];   // 笛卡尔实际速度
	
	double Car_CmdPos[MOF];// 机器人实际位姿
	double Car_CmdVel[MOF]; // 笛卡尔实际速度
	double Joint_CmdPos[MOF];//当前关节指令位置
       double Joint_CmdVel[MOF];//当前关节指令速度

    short Joint_Dir[MOF];     // 关节运动方向  :显示诊断用
	short Flag_PLim[MOF];     // 关节位置极限标志, 正极限(1)/非极限(0)/负极限(-1)
    short Joint_State[MOF];   // 关节运动状态  :显示诊断用
    short Flag_Enable[MOF];   // 使能标志  :显示诊断用
    short Flag_VLim[MOF];     // 关节速度极限标志  :显示诊断用

	double Table_MaxVel;  //转台轴最大合成旋转速度,  deg/s
	double Table_MaxAcc;  //转台轴最大合成最大加速度,  deg/s.s
    double Table_StopDec;
	TableConfigT Table_ConfigT;   //转台配置
	int Table_Gt;

/////////////////////////////////////////////////////////////////////// 全局状态
// [[ 输入
	U16 Mode;           // 示教(1)/再现(2) - // ARM设置值：1 或 2
	U16 Stop;           // 停止(1)         - // ARM设置值：1
	U16 Hold;           // 暂停(1)/继续(0) - // ARM设置值：1 或 0
	U16 AlarmClear;          // 复位(1)         - // ARM设置值：1
	U16 EStop;          // 急停(1)         - // ARM设置值：1
	U16 Abort;          // 取消运动(1)     - // ARM设置值：1
	U16 MachineStop;    // 锁定(1)/解除(0) - // ARM设置值：1 或 0
	U16 Pct_AutoVel;    // 再现运动速度百分比, 可在运动过程中设置
// ]] 输入

// [[ 当前状态
	U16 MotionMode;     // 当前运动模式 - 示教(1)/再现(2)/错误(0)
	U16 JogCoordinate;  // 手动坐标系选择 - 关节(1)/基(2)/工具(3)/用户(4)
	U16 In_Motion;      // 正在运动标志(1)
	U16 Singularity;    // 奇异位形(1)
	U16 MotorEnable;    // 轴使能(1)
// ]] 当前状态
	/* DSPState[0]-停止状态，DSPState[1]-暂停状态, DSPState[2]-总线状态*/
	char DSPState[4];
// [[ 程序状态
	ProgramInformStruct Prog_Run;  // 程序当前运动状态, 在插补时更新
	ProgramInformStruct Prog_Plan; // 程序当前状态, 在规划错误时更新
// ]] 程序状态

// [[ 错误信息
	AlarmInformStruct Err;    // 错误信息, 在程序执行过程中更新
}GlobalState;

typedef struct STRC_DelayCtrl
{
	int Req;	//请求延时标志
	int DlyTime;//延时时间

}UD_DelayCtrl;

//IO闪灯内部参数
typedef struct STRC_DSPStateLightParam
{
	unsigned int TotleTimes;
	unsigned int BlinkTimes;
	unsigned int CurrTimes;
	unsigned int IsBlinkSrart;
}UD_DSPStateLightParam;

//焊接控制结构
typedef struct STRC_WeldControl
{

       int WaitTime;         // 等待时间, ms//256
	// Mode == 10 焊接
	// 1 ARCON
	// 2 ARCOF
	// 3 ARCCT 
	// 4 ARCSET
	// 5 AWELD
	// 6 VWELD
	int order ;      
	// 电流
	float AC ;
	// 电压
	float AVP ;
	// 时间
	float T ;
	// 速度
	float V ;
	// 1 ds
	// 2 es
	int  dis_type;    
	float dis;
   /* int WaitTime;         // 等待时间, ms
    int SonMode;         //程序行模式
    int DsorDe;           //0-无效 1-Ds(Distance)   2-De(Distance)  3-渐变4-Ds(Time) 5-De(Time) 6
    float Distance;     //距离mm
    float Av;              //电压V
    float Acc;            //电流A
    unsigned int IfOutPut; //是否输出  0-不输出   1-输出*/
    float  CurrentAvp;
    float  CurrentAcc;
   // float  Vel;
    U32 IO_Mode;          // 1-输入 | 2-输出
    U32 IO_Name;          // IO编号
    U32 IO_Value;         // IO值, 1-true | 0-false
}WeldControl;

typedef struct
{
    int Fx;
    int Fy;
    int Fz;
    int Mx;
    int My;
    int Mz;
    int Status_Code;
    int Sample_Count;
    int Stop;
    double Acc;
    double Ratio;
} From_Sensor_t;


extern GlobalState gs_State;  // 全局状态
extern DSP_Timer gs_timer;    // DSP定时器

#ifdef __cplusplus
}
#endif
#endif

