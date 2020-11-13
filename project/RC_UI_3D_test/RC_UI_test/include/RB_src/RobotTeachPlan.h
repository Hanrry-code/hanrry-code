#ifndef __ROBOTTEACHPLAN_H__
#define __ROBOTTEACHPLAN_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        Robot示教结构定义                                                  *
 *****************************************************************************/
#include "RobotGlobalStruct.h"
#include "RobotError.h"

#ifndef INPUTTEACHDATA
#define INPUTTEACHDATA
// 输入示教数据结构定义
typedef struct _inputTeachData
{
	int Stop; // 示教状态 stop-1 run - 2
	int Coor; // 关节、直角、工具、工件
	int Aix;  // 轴1-6
	int Vel;  // 速度百分比
	int Dir;  // 方向 -1/1 
	int Acc;  // 加速度
	double Pos;
}InputTeachData;
#endif

// 示教结构定义
typedef struct _teachStruct
{
	//------ 输入 ------//
	double Interp_T;          // 插补周期
	int Tacc;                 // 加速周期数   - 关节 | 笛卡尔
	int Flag[MOF];       // 各轴运动状态 - JC
	int Dir[MOF];        // 各轴示教方向 - JC
    int Time[MOF];       // 加速周期计数 - JC,//从大往小减
	double Vel[MOF];     // 各轴期望速度 - JC

	//---- 定长示教 ----//
	double T_Acc;
	double Total_T[MOF]; // 运动总时间
    double Start_Pos[MOF];  /*  开始位置	*/
	double Tar_Pos[MOF]; // 目标位置

	double Act_T[MOF];   // 当前时间

	//------ 计算 ------//
	double Jerk[MOF];    // 加加速度 - JC
	double Act_Acc[MOF]; // 加速度   - JC
	double Act_Vel[MOF]; // 各轴速度 - JC
	double Act_Pos[MOF]; // 各轴位置 - JC

	//------ 输出 ------//
	double O_Acc[MOF];   // 输出加速度 - JC
	double O_Vel[MOF];   // 输出速度   - JC
	double O_Pos[MOF];   // 输出位姿   - JC

	// 笛卡尔坐标系示教专用
	double Curr_Vel[MOF];// 当前速度 - C
	double Curr_Pos[MOF];// 当前位姿 - C
}TeachStruct;

//--------------------------------- 函数 ------------------------------------//
//public_function
	void Init_Teach(TeachStruct *p, int coor);                 // 初始化示教
	void Get_TeachData(InputTeachData* in, TeachStruct* out);  // 获取示教信息
	int Teach(TeachStruct* p, double* posval, double* spdval, int (*Teach_Coor)());// 回调
	int Robot_Teach(TeachStruct* p, double* posval, double* spdval, int coor);

//private_function
	// 速度模式
	int Teach_Joint_Vel(TeachStruct* p, double* posval, double* spdval);   // 关节坐标系示教
	int Teach_World_Vel(TeachStruct* p, double* posval, double* spdval);   // 世界坐标系示教
	int Teach_Tool_Vel(TeachStruct* p, double* posval, double* spdval);    // 工具坐标系示教
	int Teach_User_Vel(TeachStruct* p, double* posval, double* spdval);    // 用户坐标系示教
	int Teach_Table_Vel(TeachStruct* p, double* posval, double* spdval);   // 转台坐标系示教

	// 位置模式
	int Teach_Joint_Pos(TeachStruct* p, double* posval, double* spdval);
	int Teach_World_Pos(TeachStruct* p, double* posval, double* spdval);
	int Teach_Tool_Pos(TeachStruct* p, double* posval, double* spdval);
	int Teach_User_Pos(TeachStruct* p, double* posval, double* spdval);
	int Teach_Table_Pos(TeachStruct* p, double* posval, double* spdval);
       //力传感器拖动
	int Robot_6dForceTeach(From_Sensor_t* fs, double* posval, double* spdval);

#ifdef __cplusplus
}
#endif
#endif
