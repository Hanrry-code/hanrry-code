#ifndef __ROBOTERRORPLAN_H__
#define __ROBOTERRORPLAN_H__


#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        错误规划                                                           *
 *****************************************************************************/
#include "RobotGlobalStruct.h"

// 轨迹初始参数
typedef struct _trajInitPara
{
	double Jerk; // 加加速度
	double Acc;  // 加速度
	double Vel;  // 速度
	double Len;  // 距离
}TrajInitPara;

// 错误停止插补点
#ifndef _TRAJPOINTPARA_
#define _TRAJPOINTPARA_
typedef struct _trajPointPara
{
	double Acc; // 加速度
	double Vel; // 速度
	double Len; // 距离
}TrajPointPara;
#endif

// 错误停止结构体
typedef struct _errStopTrajStruct
{
	int Stop;      // 停止标志
	
	double Interp_T; // 插补周期
	
	double Time;   // 停止时间
	double T[MOF];   // 
	double Pos[MOF]; // 初始位置
	double Vel[MOF]; // 初始速度
	double Acc[MOF]; // 加速度
	double Curr_T; // 当前时间
	
}ErrStopTrajStruct; 

public_function
	int Get_JointLimState(double* ld_pos, double* ld_vel); // 获取关节极限状态
	int Get_BoundarySinState(double* ld_pos, double* ld_vel);
	int Get_InternalSinState(double* ld_pos, double* ld_vel);

	int If_In_JointLim(double * pos);               // 判断关节点是否超限
	Boolean If_In_BoundarySin(double* pos1, double* pos2);
	Boolean If_In_InternalSin(double* pos1, double* pos2);

	void Init_ErrorStop(double* pos, double* vel, double* acc);// 错误停止初始化
	int Get_ErrorStop(double* posval, double* spdval); 
	Boolean IfTableZoneLimit(double jpos_start[MOF],double jpos_end[MOF]);

public_variable
	extern ErrStopTrajStruct gs_ErrStop;

#ifdef __cplusplus
}
#endif
#endif
