#ifndef __ROBOTINTERPOLATION_H__
#define __ROBOTINTERPOLATION_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        规划及插补控制函数                                                 *
 *****************************************************************************/
#include "RobotGlobalStruct.h"
#include "RobotKinematics.h"
#include "SpeedProcess.h"
#include "RobotQueue.h"
#include "RobotErrorPlan.h"
#include "RobotVelControl.h"

#define PATH_BUF_MAX_LEN        17//6//5  // 路径缓冲区长度
#define TRAJECTORY_BUF_LEN_MIN  18//6  // 轨迹缓冲区最小长度
#define TRAJECTORY_BUF_LEN_MAX 36//14//12//10  // 轨迹缓冲区最大长度

#ifndef ABS
#define ABS(a)		((a)>=0?(a):(-(a)))
#endif
#define Count(n)    (((n) + PATH_BUF_MAX_LEN) % PATH_BUF_MAX_LEN) // 路径缓冲区计数器
#define Cnt(n)    (((n) + TRAJECTORY_BUF_LEN_MAX) % TRAJECTORY_BUF_LEN_MAX)
//------------------------------- 结构定义 ----------------------------------//
// MOVJ路径特征
typedef struct _jointPathFeature
{
	double JPos_Start[MOF];  // 起点
	double JPos_Mid1[MOF];
	double JPos_Mid2[MOF];
	double JPos_End[MOF];    // 末点
	double JVel_Cons[MOF];   // 匀速度

	double Time;
}JointPathFeature;

// 空间向量
typedef struct _vectorStruct
{
	double X;   // 向量x
	double Y;   // 向量y
	double Z;   // 向量z
	double Con; // 常量
}VectorStruct;

// 笛卡尔路径特征
typedef struct _cartesianPathFeature
{
	double JPos_Start[MOF];   // 起点关节角
	double JPos_Mid[MOF];     // 圆弧中间点关节角
	double JPos_End[MOF];     // 末点关节角

	CartesianPose CPos_Start; // 起点位姿
	CartesianPose CPos_Mid;   // 圆弧中间点位姿
	CartesianPose CPos_End;   // 末点位姿

	double Car_PAcc;          // 线加速度
	double Car_PVel;          // 期望线速度
	double PosLen;            // 路径长度, 直线长度或圆弧弧长
	double Car_GAcc;          // 姿态加速度
	double Car_GVel;          // 期望姿态速度
	double GesAng;            // 姿态角
	Boolean Flag_Reverse;

	double Time;
	VectorStruct Line_Vector; // 直线单位向量, 常量Con = 1
	double Angle_Vector[2];  //旋转单位向量
	double Car_Vec;      //笛卡尔长度分量

	PoseMatrix   Arc_Matrix;  // 圆弧UVW新坐标系矩阵
	VectorStruct Arc_Centre;  // 圆心坐标及半径
	double       Arc_Radian;  // 圆弧的弧度
	double       Arc_MidLen;  // 圆弧中间点对应的弧长

}CartesianPathFeature;

// 路径
typedef struct _interpPathStruct
{
	InputAutoData Input;

	JointPathFeature  JointPath;
	CartesianPathFeature CartePath;
}InterpPathStruct;


// 轨迹
typedef struct _InterpTrajectoryStruct
{
	// 程序名
    // 显示用到
    char name[20];
	
    // 译码的部编号
    // 实时同步用到
    unsigned int decode_id ;

	//------------------- 段信息 --------------------//
	int Prog_SequNum;         // 当前程序段编号	
	int Prog_LineNum;         // 当前程序行编号
	int Prog_Mark;            // 程序标志, 1-start/2-end/0-mid	
	int Mode;                 // 程序行模式, 运动行-1 | IO-2 | Delay-3
	int Interp_Mode;          // 插补方式 - MOVJ 1 | MOVL 2 | MOVC 3 | MOVP 4
	int IfTransSeg;           // 是否是过渡段, 1是/0否

	//------------------ 运动参数 --------------------//
	double TotleTime;		  //当前行总时间
	double Time;              // 总时间

	double JPos_Start[MOF];   // 始点关节角
	double JPos_End[MOF];     // 末点关节角
	
// [[ 关节插补
	double JVel_Start[MOF];   // MOVJ 关节初速度
	double JVel_End[MOF];     // MOVJ 关节末速度
// ]]

// [[ 笛卡尔插补
	CartesianPose CPos_Start;   // 始点位姿
	CartesianPose CPos_End;     // 末点位姿
	PoseMatrix    Arc_Matrix;   // 圆弧UVW新坐标系矩阵
	VectorStruct  Arc_Centre;   // 圆心坐标及半径
	double        Arc_Len_Start;// 圆弧起始点弧长
	SpdTrajStruct Traj_CPos;    // 位置轨迹, 非过渡段使用
	SpdTrajStruct Traj_CGes;    // 姿态轨迹
	Boolean          Ges_Reverse;  // 姿态反向插补标志, 1反向 | 0正向
	double        CVel_Start[MOF];// 位置初速度, 过渡段使用
	double        CVel_End[MOF];  // 位置末速度, 过渡段使用

	double Car_Vec;      //笛卡尔长度分量

	VectorStruct Line_Vector; // 直线单位向量, 常量Con = 1
// ]]

	//------------------ 运动参数 --------------------//
	// [[ IO行信息
	int IO_Mode;          // 1-输入 | 2-输出
	int IO_Name;          // IO编号
	int IO_Value;         // IO值, 1-true | 0-false
	// ]]
	int WaitTime;         // 等待时间, ms

	// Mode == 10 焊接
	// 1 ARCON
	// 2 ARCOF
	// 3 ARCCT 
	// ----4 ARCSET----11,12,13
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
       /*int SonMode;         //程序行模式
       int DsorDe;           //0-无效 1-Ds   2-De
       float Distance;     //距离mm
       float Av;              //电压V
       float Acc;            //电流A*/
}InterpTrajectoryStruct;


// 路径缓冲区
typedef struct _path_Buffer
{
	InterpPathStruct Data[PATH_BUF_MAX_LEN];   
	U16 Start;
	U16 End;
	U16 Now;
	
	U16 Num;
}Path_Buffer;


// 轨迹缓冲区
typedef struct _trajectory_Buffer
{
	InterpTrajectoryStruct Data[TRAJECTORY_BUF_LEN_MAX];
	U16 Start;
	U16 End;
}Trajectory_Buffer;


// 关节空间插补结构体
typedef struct _jointInterpStruct
{
	int Degree;     // 插补拟合曲线的最高次幂
	double Pos0[MOF]; // 第一点数据
	double Pos1[MOF]; // 第二点
	double Pos2[MOF]; // 第三点
	double Pos3[MOF]; // 第四点
	double Pos4[MOF]; // 第五点 
	int Num;        // 每周期插补点数
	int Count;      // 插补点计数
}JointInterpStruct;


//------------------------------- 函数说明 ----------------------------------//
public_function // 正逆解
	int Minimize_RadRot(double start, double* end);
	int Get_ForwardPos(IN double* jpos, OUT CartesianPose* cpos);
	int Get_InversePos(IN CartesianPose* cpos, IN double* jcurrpos, OUT double* jpos);
	int Get_ForwardVel(IN double* jpos, IN double* jvel, OUT double* cvel);
	int Get_InverseVel(IN double* jpos, IN double* cvel, OUT double* jvel);
	int Get_InverseVel_SinAvoid(IN double* jpos, IN double* cvel, OUT double* jvel);


public_function
	void Init_Interpolation(double* pos);          // 再现初始化
	int Plan_Path(InterpPathStruct *path);         // 路径规划
	int Plan_Trajectory(IN Path_Buffer* p, OUT Trajectory_Buffer* buf); // 轨迹规划
	int Interpolation(Trajectory_Buffer* p, Queue* q); // 插补
	
	// 关节空间轨迹规划
	void Init_JointInterp(double* pos, int degree);          // 初始化关节插补
int Get_JointInterpData(Queue* que, ElemType* elem, double* posval, double* spdval); // 获取关节插补数据


private_function  // 轨迹缓冲区
	int  Get_TrajectoryBufNum(IN Trajectory_Buffer *buf);
	Boolean Put_TrajectoryBuffer(IN Trajectory_Buffer *buf, IN  InterpTrajectoryStruct *msg);
	Boolean Get_TrajectoryBuffer(IN Trajectory_Buffer *buf, OUT InterpTrajectoryStruct *msg);

	void Clear_PathBuffer      (IN Path_Buffer* buf);
	void Clear_TrajectoryBuffer(IN Trajectory_Buffer* buf);

private_function  // 路径规划
	Boolean Read_TrajectoryBuffer(IN Trajectory_Buffer *buf, 
						  OUT InterpTrajectoryStruct *msg);
	// MOVJ路径规划
	int Plan_Joint_Path (
			IN InputAutoData* in,           // 再现数据
			OUT JointPathFeature* out);     // MOVJ路径
	// MOVL路径规划
	int Plan_Linear_Path(
			IN InputAutoData* in,           // 再现数据
			OUT CartesianPathFeature* out); // MOVL路径
	// MOVC路径规划
	int Plan_Circle_Path(
			IN InputAutoData* in,            // 再现数据
			OUT CartesianPathFeature* out);  // MOVC路径

private_function  // 轨迹规划
	// MOVJ轨迹规划
	int Plan_Joint_Trajectory (
			IN InterpPathStruct* now,    // 当前段MOVJ路径
			IN InterpPathStruct* next,   // 下一段MOVJ路径
			IN int premode,              // 与前一段过渡模式
			IN int nextmode,             // 与下一段过渡模式
			OUT Trajectory_Buffer* buf); // 轨迹缓冲区
	// MOVL轨迹规划
	int Plan_Linear_Trajectory(           
			IN InterpPathStruct* pre,    // 前一段MOVL路径
			IN InterpPathStruct* now,    // 当前段MOVL路径
			IN InterpPathStruct* next,   // 下一段MOVL路径
			IN int premode,              // 与前一段过渡模式
			IN int nextmode,             // 与下一段过渡模式
			OUT Trajectory_Buffer* buf); // 轨迹缓冲区
	// MOVC轨迹规划
	int Plan_Circle_Trajectory(
			IN InterpPathStruct* pre,    // 前一段MOVC路径
			IN InterpPathStruct* now,    // 当前段MOVC路径
			IN InterpPathStruct* next,   // 下一段MOVC路径
			IN int premode,              // 与前一段过渡模式
			IN int nextmode,             // 与下一段过渡模式
			OUT Trajectory_Buffer* buf); // 轨迹缓冲区

private_function  // 插补
	int Get_JointInterpPoint   (IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);
	int Get_LinearInterpPoint  (IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);
	int Get_ParabolaInterpPoint(IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);
	int Get_QuinticInterpPoint (IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);
	int Get_InterpPoint        (IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);

	int Insert_InterpPoint(Queue* q, ElemType e);

private_function // 过渡段参数
	void Get_ZoneLine_PosVel(IN CartesianPathFeature* line, // 直线路径
			IN int zone,                   // 过渡等级
			IN Boolean start,                 // 是否是开始端
			OUT CartesianPose* cpos,       // 过渡点坐标
			OUT double tpos[2],            // 过渡点转台坐标
			OUT VectorStruct* pvec,        // 过渡点速度
			OUT VectorStruct* gvec,        // 过渡点角速度
			OUT double tvec[2],            // 过渡点转台速度
			OUT double* zlen,              // 过渡段位移
			OUT double* zges,              // 过渡段角位移
			IN int mode);

	void Get_ZoneArc_PosVel(IN CartesianPathFeature* arc,  // 圆弧路径
			IN int zone,                   // 过渡等级
			IN Boolean start,                 // 是否是开始端
			OUT CartesianPose* cpos,       // 过渡点坐标
			OUT double tpos[2],            // 过渡点转台坐标
			OUT VectorStruct* pvec,        // 过渡点速度
			OUT VectorStruct* gvec,        // 过渡点角速度 
			OUT double tvec[2],            // 过渡点转台速度
			OUT double* zlen,              // 过渡段弧长
			OUT double* zges,              // 过渡段角位移
			IN int velmode);                // 返回过渡点速度模式

	double Get_ZoneTime_JointSpace(IN double p1[], 
			IN double p2[], 
			IN double v1[], 
			IN double v2[],
			IN int velpct);

	double Get_ZoneTime_CartesianSpace(IN double pos1[MOF], 
			IN double pos2[MOF], 
			IN double v1[MOF], 
			IN double v2[MOF],
			IN double maxpv,
			IN double maxgv,
			IN double maxtv);

private_function // 姿态
	// 获取两点之间的姿态夹角
	double Get_Attitude_Angle(
			IN CartesianPose* cpos1,        // 首点位姿
			IN CartesianPose* cpos2,        // 末点位姿
			OUT Boolean* inverse);             // 姿态反向旋转标志
	// 获取姿态插补中间点欧拉角
	Euler Get_Gesture_Euler(
			IN CartesianPose* cpos1,        // 首点位姿
			IN CartesianPose* cpos2,        // 末点位姿
			IN double angle,                // 姿态夹角
			Boolean reverse,                   // 姿态反向旋转标志
			double h);                      // [0,1]参数

	Euler Get_Gesture_Vel(
			IN CartesianPose* cpos1, // 首点位姿
			IN CartesianPose* cpos2, // 末点位姿
			IN double angle,         // 姿态夹角
			IN Boolean reverse,         // 反向旋转标志
			IN double h,             // [0,1]参数
			IN double hvel,
			IN int mode);         // h速度


public_function

// 轨迹插补状态
typedef struct _interpolationState
{
	Boolean Enable;    // 插补使能状态
	double Time;    // 当前插补时间
	InterpTrajectoryStruct Traj; // 当前插补轨迹段

	Boolean IfEndPoint;   // 末点标志
	ElemType EndPoint; // 末点
	
}InterpolationState;

#ifdef __cplusplus
}
#endif
#endif
