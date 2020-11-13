#ifndef __COMMUNICATE_H__
#define __COMMUNICATE_H__


#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        与上位机通讯                                                          *
 *****************************************************************************/
/////////////////////////////数据结构定义////////////////////////////////

#ifndef U16
#define U16 unsigned short
#endif

#ifndef U32
#define U32 unsigned int
#endif

// [[ 系统参数
#define MOF           8          // 最大机器人自由度+转台自由度

extern int DOF;  //机器人轴数+转台自由度

#ifndef _CPSTRITIO_
#define _CPSTRITIO_
typedef struct _CPSTRITIO
{
    double CPSTRITIO_56;      // 56轴补偿比率
    double CPSTRITIO_45;      // 45轴补偿比率
    double CPSTRITIO_46;      // 46轴补偿比率
}CPSTRITIO;
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

#ifndef TABLEPOSE
#define TABLEPOSE
// 转台角度表示：转台坐标系
typedef struct _tablePose
{
	double A1;     //第1轴转角,deg
	double A2;     //第2轴转角,deg
}TablePose;
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

//干涉区结构体
#ifndef INTFZONE
#define INTFZONE
typedef struct _IntfZone
{
	U16 ZoneID;			//干涉区号，0～5
	U16 Availablty;		//是否有效标志，1－有效，0－无效
	int RefCoord;		//参考坐标系：-1 －基坐标系，其他 － 用户坐标系号
	float PointMin[3];	//第一点
	float PointMax[3];	//第二点
}IntfZone;
#endif

//用户坐标系结构体
#ifndef USERFRAME
#define USERFRAME
typedef struct _UserFrame
{
	U16 UserID;			//用户坐标系号，0～9
	U16 Unused1;
	U32 Unused2;
	CartesianPose User;	//用户坐标系数据
}UserFrame;
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

#ifndef INPUTAUTODATA
#define INPUTAUTODATA
// 系统输入再现数据结构
typedef struct _inputAutoData
{
    // 程序名
    // 显示用到
    char name[20];//0

    // 译码的部编号
    // 实时同步用到
    unsigned int decode_id ;//20

    // [[ 段基本信息
    int Prog_SequNum;     // 当前程序段编号	//24
    int Prog_LineNum;     // 当前程序行编号     //28
    int Prog_Mark;        // 程序标识 0:非最后一行  1:单行或最后一行//32
    // ]]

    int Mode;             // 程序行模式, 运动行-1 | IO-2 | Delay-3 | 非程序行-4 |Wait-5|焊接-10  //36

    // [[ 运动行信息
    int Interp_Mode;      // 插补方式 - MOVJ 1 | MOVL 2 | 圆弧 3 | 整圆 4   //40

    int Joint_VelPct;     // 关节插补速度百分比   //44
	int PathSN;			  // 圆弧时指定是第一段还是第二段，0--整段，1--第一段，2--第二段//48
	int PathSN2;			  //52
	double JPos_Start[MOF]; // 起始点, 圆弧插补时用（明确赋值）  //空间变化
    double JPos_Mid[MOF];   // 中间点, 圆弧/抛物线插补时用  //空间变化
    double JPos_End[MOF];   // 目标点  //空间变化
    double Car_PVel;      // 笛卡尔插补位置速度, 0-默认//200
    double Car_GVel; 	  //208
    int Zone;             // 过渡等级, 0,1,2,3,4   //216

    int Move_IfHaveIn;    // 是否有输入指令//220
    int Move_InName;      // 输入编号//224
    int Move_WaitInT;     // 等待输入的时间//228

    int Move_IfHaveOut;   // 是否有输出指令//232
    int Move_OutName;     // 输出编号         //236
    int Move_OutTrigger;  // 输出触发方式//240
    // ]]

    // [[ IO行信息
    int IO_Mode;          // 1-输入 | 2-输出 3-模拟输入 4-模拟输出//244
    int IO_Name;          // IO编号//248
    int IO_Value;         // IO值, 1-true | 0-false//252
    // ]]
    int WaitTime;         // 等待时间, ms//256
	// Mode == 10 焊接
	// 1 ARCON
	// 2 ARCOF
	// 3 ARCCT 
	// 4 ARCSET
	// 5 AWELD
	// 6 VWELD

	// 11 ARCSET  av
	// 12 ARCSET  ac
	// 13 ARCSET  v
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
	int  acc_time;//ms
    /*// Mode == 10 焊接
	// 1 ARCON
	// 2 ARCOF
	// 3 ARCCT 
	// 4 ARCSET
	// 5 AWELD
	// 6 VWELD
	int SonMode;//order ;//260
	// 电流
	float Acc;//AC ;//264
	// 电压
	float Av;//AVP ;//268
	// 时间
	float T ;//272   ms
	// 速度
	float V ;//276
	// 1 ds
	// 2 es
	int  DsorDe;//if(
	float Distance;//dis;//284
	//288字节*/
    /*int SonMode;         //程序行模式
    int DsorDe;           //0-无效 1-Ds   2-De
    float Distance;     //距离mm
    float Av;              //电压V
    float Acc;            //电流A*/

}InputAutoData;
#endif

#ifndef INPUTTEACHDATA
#define INPUTTEACHDATA
// 输入示教数据结构定义
typedef struct _inputTeachData
{
    int Stop; 	// 示教状态 stop-1 run - 2
    int Coor; 	// 速度方式：关节--1、直角--2、工具--3、工件--4；定长方式：关节--11、直角--12、工具--13、工件--14
    int Aix;  	// 轴1-6
    int Vel;  	// 速度百分比
    int Dir;  	// 方向 -1/1 
    int Acc;  	// 加速度
	double Pos;	// 定长示教下位移长度，角度量单位：deg，平移量单位：mm
}InputTeachData;
#endif

#ifndef JOINTINTPARA
#define JOINTINTPARA
typedef struct _jointIntPara
{
    short int S;
    short int L;
    short int U;
    short int R;
    short int B;
    short int T;
}JointIntPara;
#endif

#ifndef ALARMINFORMSTRUCT
#define ALARMINFORMSTRUCT
typedef struct _alarmInformStruct
{
    int Err_Comm; // 通讯错误编号
    int Err_Plan; // 规划错误
    int Err_Run;  // 运行错误
    int Err_Lim;  // 极限
    int Alm_Ser;  // 伺服错误
    int OTC_CIA;  // 干涉区
}AlarmInformStruct;
#endif

typedef struct _alarmQueue
{
    int Err_Num;                         //  ?μí3±¨?ˉêy
    int Err_Number[10];  // ?μí3±¨?ˉo?
}AlarmQueue;

#ifndef PROGRAMINFORMSTRUCT
#define PROGRAMINFORMSTRUCT
// 程序状态
typedef struct _programInformStruct
{
	int Prog_State; // 1. 运动：当前程序运动状态, 0无运行, 1正在运行, 2运动结束, 其它-运动错误
	                // 2. 规划：0正常, 其它-规划错误。行号和段号只在规划错误时有效
	int CurrLine_State;	//当前行状态, 0 无运行, 1 正在运行, 2 运动结束, 其它-运动错误
    // 程序名
    // 显示用到
    char name[20];
	
    // 译码的部编号
    // 实时同步用到
    unsigned int decode_id ;
	int Prog_SequNum;// 所属程序段号
	int Prog_LineNum;// 所属程序行号
	int IfTransSeg;  // 是否是过渡段
}ProgramInformStruct;

#endif

#ifndef PROGRAMRUNSTRUCT
#define PROGRAMRUNSTRUCT
// 程序状态
typedef struct _programRunInformStruct
{
   	 // 实时同步用到
	double time;      //该轨迹已运行时间
	double totaltime;//该轨迹运行总时间
	double len; //该轨迹已运行长度
	double totallen;//该轨迹运行总长度
	
}ProgramRunInformStruct;

#endif

typedef struct  _SYSTEMSTATUS
{
	U16 pEStop;        
	U16 pMode;       
    U16 intCanUse; 
    U16 intMode; 
	U16 pStop;       
    U16 pReset; 
	U16 pEnable;   
    U16 pAbort;
	U16 pPctAutoVel;
    U16 pHold;
	U32 DSPStateLight;
}SYSTEMSTATUS;

#ifndef IOCARDCTRL
#define IOCARDCTRL
typedef struct _IoCardCtrl
{
	U32 DigitalSignal[2];			 
	U32 AnalogSignal[2];         
	U16 CardADC[4];
}IoCardCtrl;
#endif

#ifndef IOARMCTRL
#define IOARMCTRL
typedef struct _IoArmCtrl
{
	U32 DigitalSignal[2];	//64位IO		       
	U16 Control;//控制位，1-ARM IO指令有效 2-DSP读取后置为2
}IoArmCtrl;
#endif

/*
//#define COMM_BASIC  0xB0004000
extern int COMM_BASIC;

extern U16* m_pDSPVersion;		//版本号，共12个元素

extern U16* m_pUserFrameControl;	//控制位：0 － 待命，1 － 请求更新用户坐标系
extern UserFrame* m_pUserFrame;//工具坐标系

extern U16* m_pIntfZoneControl;	//控制位：0 － 待命（初始化或者DSP接收完数据后置0），1 － 请求更新干涉区
extern IntfZone* m_pIntfZone;//干涉区

extern U16* m_pIntfZoneEnter;//是否进入干涉区标志：0 bit～5 bit，0－未进入，1－已进入
//extern U32* m_pDSPStateLight;
extern U16* m_pCPSTRITIOControl;    //补偿比率读写控制  1-DSP可读 0-DSP读完成 
extern CPSTRITIO *m_pCPSTRITIO;//三个double

extern U32 DSPStateLight;
extern volatile U16* m_pMode;       // 运动模式 - 示教(1)/再现(2)
extern volatile U16* m_pStop;       // 停止(1)
extern volatile U16* m_pAlarmClear;      // 复位(1)
extern volatile U16* m_pEnable;     // 使能(1) / 非使能(0)
extern volatile U16* m_pReset;      // 取消(1)
extern volatile U16* m_pMachineLock;// 机械锁定(1)
extern volatile U16* m_pPctAutoVel; // 再现速度百分比(20-100)
extern volatile U16* m_pHold;       // 暂停(1) / 继续(0)
extern volatile U16* m_pDSPState;
extern volatile U16* m_pInitOk;
extern volatile U16* m_pEStop;	//急停信号
extern volatile U16* m_pEnableKey; 
/////////////////////////////////////////////// 设置参数 (ARM-DSP) 0x0200-0x0520
extern U16* m_pAbsZeroControl;     // 设置绝对零点控制位, 1-关节, 2-轴
extern JointPose* m_pJointAbsZero; // 关节绝对零点

// [[ 关节空间
extern U16* m_pJointControl;      // 关节参数控制位
extern JointPose* m_pJointMaxAcc;// 关节最大加速度
extern JointPose* m_pJointMaxVel; // 关节最大速度
extern JointPose* m_pJointStopDec;// 关节停止减速度, deg/s*s
extern JointPose* m_pJointPLim;   // 关节正极限, deg
extern JointPose* m_pJointNLim;   // 关节负极限, deg
// ]]

// [[ 轴空间 ,电机数据
extern U16* m_pMotorControl;      // 轴参数控制位
extern JointPose* m_pMotorRatio;  // 轴减速比
extern JointPose* m_pMotorAbsZero;// 轴绝对零点, 电机转角
extern int* m_pMotorPrec;         // 轴精度, cts/round
extern U16* m_pMotorDir;          // 轴方向, 按位控制, 与关节方向一致时为1, 不一致为0
// ]]

extern int* m_pAccTime;  // 加速时间, ms

// [[ 笛卡尔空间
extern U16* m_pCarControl;     // 笛卡尔参数控制位
extern double* m_pCarMaxPVel;  // 笛卡尔位置最大速度, mm/s
extern double* m_pCarMaxGVel;  // 笛卡颂畲笏俣? deg/s
extern double* m_pCarMaxPAcc;  // 笛卡尔位置加速度
extern double* m_pCarMaxGAcc;  // 笛卡尔姿态加速度
extern double* m_pCarStopPDec; // 笛卡尔位置停止减速度
extern double* m_pCarStopGDec; // 笛卡尔姿态停止减速度
//]]

// [[ 机器人
extern U16* m_pRobotControl;        // 笛卡尔参数控制位
extern LinkDimension* m_pRobotLink; // 机器人连杆参数
extern CartesianPose* m_pRobotTool; // 工具坐标系参数
extern CartesianPose* m_pRobotUser; // 用户坐标系参数
// ]]


/////////////////////////////////////////////// 示教数据 (ARM-DSP) 0x0520-0x0560
extern U16* m_pTeachControl;         // 示教控制
extern InputTeachData* m_pTeachData; // 示教数据


/////////////////////////////////////////////// 再现数据 (ARM-DSP) 0x0560-0x0d00
//分配100K的空间给译码缓冲区 100k=0x19000  412k=421888=0x67000
extern U32* m_pAutoControl;         // 再现控制
extern InputAutoData* m_pAutoData;  // 再现数据


/////////////////////////////////////////////// 反馈参数 (DSP-ARM) 0x0d00-0x0e00
extern CartesianPose* m_pCarActPos; // 机器人实际位姿
extern JointPose* m_pJointActPos;   // 关节实际位置
extern JointPose* m_pJointActVel;   // 关节实际速度
extern JointPose* m_pJointActCurr;  // 轴实际电流
extern JointPose* m_pMotorActPos;   // 轴实际转角


extern JointIntPara* m_pJointDir;   // 关节运动方向
extern JointIntPara* m_pJointState; // 关节运动状态
extern JointIntPara* m_pFlagEnable; // 使能标志
extern JointIntPara* m_pFlagVLim;   // 关节速度极限标志
extern JointIntPara* m_pFlagPLim;   // 关节位置极限标志, 正极限(1)/非极限(0)/负极限(-1)

extern AlarmQueue* m_pAlarmQueue; // 错误状态

extern ProgramInformStruct* m_pProgRunInform;  // 程序运动状态
extern ProgramInformStruct* m_pProgPlanInform; // 程序规划错误状态
extern ProgramRunInformStruct* m_pRunInform;
//extern U32*m_pIoIn;  // I/O输入，32位
//extern U32*m_pIoOut; // I/O输出，32位

extern IoCardCtrl* m_IoInputCtrl;
extern IoArmCtrl* ARMClrIO;
extern IoArmCtrl* ARMSetIO;
extern IoCardCtrl* m_IoOutputCtrl;

extern float *Avp;
extern float *Acc;

extern int* PulseSendSum;
extern int* PulseSendNum;

extern SYSTEMSTATUS* SystemRunState;

extern short int* OverFlowCount;

extern short int*  TestRam;

/////////////////////////////////////////////// 设置参数

// [[ 转台空间
extern TablePose* m_pTableJointMaxAcc; // 关节最大允许加速度, deg/s*s
extern TablePose* m_pTableJointMaxVel; // 转台最大速度
extern TablePose* m_pTableJointStopDec; // 转台停止减速度, deg/s*s
extern TablePose* m_pTableJointPLim; // 转台正极限, deg
extern TablePose* m_pTableJointNLim; // 转台负极限, deg
// ]]

// [[ 轴空间 ,电机数据
extern TablePose* m_pTableMotorRatio; // 轴减速比
extern TablePose* m_pTableMotorAbsZero; // 轴绝对零点, 电机转角
extern int* m_pTableMotorPrec1; // 轴精度, cts/round
extern int* m_pTableMotorPrec2; // 轴精度, cts/round
extern U32* m_pTableMotorDir; 

// [[ 转台空间
extern double* m_pTableMaxVel;  //转台轴最大合成旋转速度,  deg/s
extern double* m_pTableMaxAcc;  //转台轴最大合成最大加速度,  deg/s.s
// ]]

//[[ 转台配置
extern TableConfigT* m_pTableConfigT;
extern int * m_pTableAxisNum;
//]]

/////////////////////////////////////////////// 反馈参数 

extern TablePose* m_pTableJointActPos;   // 关节实际位置  16字节
extern TablePose* m_pTableJointActVel;   // 关节实际速度  16字节
extern TablePose* m_pTableJointActCurr;  // 轴实际电流  16字节
extern TablePose* m_pTableMotorActPos;   // 轴实际转角  16字节

extern short int* m_pTableJointDir1;   // 关节1运动方向  2字节
extern short int* m_pTableJointDir2;   // 关节2运动方向  2字节

extern short int* m_pTableJointState1;   // 关节1运动状态  2字节
extern short int* m_pTableJointState2;   // 关节2运动状态  2字节

extern short int* m_pTableFlagEnable1; // 使能1标志  2字节
extern short int* m_pTableFlagEnable2; // 使能2标志  2字节

extern short int* m_pTableFlagVLim1; // 关节1速度极限标志  2字节
extern short int* m_pTableFlagVLim2; // 关节2速度极限标志  2字节

extern short int*  m_pTableFlagPLim1;   // 关节位置极限标志, 正极限(1)/非极限(0)/负极限(-1)  2字节
extern short int*  m_pTableFlagPLim2;   // 关节位置极限标志, 正极限(1)/非极限(0)/负极限(-1)  2字节
*/

#ifdef __cplusplus
}
#endif

#endif
