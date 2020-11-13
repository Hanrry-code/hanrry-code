#ifndef __SPEEDPROCESS_H__
#define __SPEEDPROCESS_H__
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        S加减速处理结构定义                                                *
 *****************************************************************************/
#include "RobotGlobalStruct.h"


// 轨迹点参数类
#ifndef _TRAJPOINTPARA_
#define _TRAJPOINTPARA_
typedef struct _trajPointPara
{
	double Acc; // 加速度
	double Vel; // 速度
	double Len; // 距离
}TrajPointPara;
#endif

// 轨迹输入数据类
typedef struct _spdPTrajInputData
{
	double Len;  // 轨迹段长度
	double Vs;   // 初始速度
	double V;    // 期望速度
	double Ve;   // 终点速度
	double Acc;  // 最大加速度
	double Jerk; // 最大加加速度
	double T_Acc;// 加速时间
}SpdPTrajInputData;

// 轨迹输出数据类
typedef struct _spdPTrajData
{
	double Len;  // 轨迹段长度
	double Vs;   // 初始速度
	double V;    // 期望速度
	double Ve;   // 终点速度

	double Jacc;
	double Jdec;

	double T1;   // 各段时间
	double T2;
	double T3;
	double T4;
	double T5;
	double T6;
	double T7;
	
	double T;    // 规划总时间

	double V1;   // 各段端点速度
	double V2;
	double V3;
	double V4;
	double V5;
	double V6;

	double L1;  // 各段端点位移
	double L2;
	double L3;
	double L4;
	double L5;
	double L6;
	double L7;
}SpdTrajStruct;

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif


//--------------------------------- 函数 ------------------------------------//
public_function
	// T加减速规划
	int SpeedPlanningT(IN SpdPTrajInputData* pIn, OUT SpdTrajStruct* pOut);
	// S加减速规划
	int SpeedPlanningS(IN SpdPTrajInputData* pIn, OUT SpdTrajStruct* pOut);
	// 获取轨迹
	void Get_SpeedProcessData(IN SpdTrajStruct* pIn, IN double dTime, OUT TrajPointPara* pOut);
	// 给定时间规划	
	int SpeedPlanningSByTime(IN  SpdPTrajInputData *in,
							 IN  double Time, 
							 OUT SpdTrajStruct *out);
	int SpeedPlanningSByVmod(IN SpdPTrajInputData *in,
							 IN double Time,
							 OUT SpdTrajStruct *out);
	// 规划轨迹时间
	double TimePlanningT(SpdPTrajInputData* p);

private_function
	// 解一元三次方程
	double Solve_Equation3(double a, double b, double c, double d, double val);
	// 解一元二次方程
	int Solve_Equation2(double a, double b, double c, double* res1, double* res2);
	// 获取加速段和减速段距离
	void Get_AccDecLen(SpdTrajStruct *out, double* sacc, double *sdec);
#ifdef __cplusplus
}
#endif


#endif
