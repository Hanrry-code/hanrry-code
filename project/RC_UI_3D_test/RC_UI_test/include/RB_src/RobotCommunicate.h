#ifndef __ROBOTCOMMUNICATE_H__
#define __ROBOTCOMMUNICATE_H__


#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        与ARM通讯                                                          *
 *****************************************************************************/
#include "RobotTeachPlan.h"
#include "RobotInterpolation.h"
#include "Communicate.h"

public_function
	void Init_Communicate();          // 初始化与ARM通讯
	Boolean Clear_MotionData_ARM();      // Clear运动数据

	int  Read_EStop_FromARM();
//	int  Read_Abort_FromARM();        // 获取Abort
	int  Read_MachineStop_FromARM();  // 获取机械锁定
	Boolean Read_OnlineData_FromARM();   // 获取在线指令
	Boolean Read_JointData_FromARM();    // 获取关节数据
	Boolean Read_CartesianData_FromARM();// 获取笛卡尔数据
	Boolean Read_MotorData_FromARM();    // 获取轴数据
	Boolean Read_RobotData_FromARM();    // 获取机器人数据
	Boolean Read_CPSTRITIOData_FromARM();// 获取机器人补偿比率数据
	Boolean Read_AbsZeroSet_FromARM();

	Boolean Read_TeachData_FormARM(InputTeachData* data); // 获取示教数据
	Boolean Read_AutoData_FromARM(OUT Path_Buffer *buf);  // 获取再现数据

	void ReadIntfZoneData();
	void ReadUserFrameData();

	void Set_Data_ToARM();  // 写数据到ARM

	void Send_Stop_ToDSP();          // 发送停止指令
	void Reset_AutoVelPct_ToArm();
	void Send_Enable_ToMotor(Boolean en);


#ifdef __cplusplus
}
#endif

#endif
