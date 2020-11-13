#ifndef __ROBOTKINEMATICS_H__
#define __ROBOTKINEMATICS_H__
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        机器人运动学定义                                                   *
 *****************************************************************************/
#include "RobotGlobalStruct.h"
#include "RobotMatrix.h"

#define KINE_RATIO_V   800
#define KINE_DAMP_EI   500
#define KINE_DAMP_EB   500
#define KINE_RATIO_W  0.08
#define KINE_DAMP_EW  0.087


// 欧拉角
typedef struct _euler
{
	double W;
	double P;
	double R;
}Euler;

// 四元数
typedef struct _quaternion
{
	double P0;
	double P1;
	double P2;
	double P3;
}Quaternion;

//--------------------------------- 函数 ------------------------------------/
public_function
	// 正解
	int Robot_ForwardKine(IN  JointPose* i_JPos,      // 关节角
						  OUT CartesianPose* o_CPos,  // 位姿
						  IN  LinkDimension* i_Link,  // 机器人机构参数
						  IN  CartesianPose* i_Tool); // 工具参数

	// 逆解
	int Robot_InverseKine(IN  CartesianPose* i_CPos,  // 位姿
						  IN  JointPose* i_JCurr,     // 当前关节角
						  OUT JointPose* o_JPos,      // 关节角
						  IN  LinkDimension* i_Link,  // 机器人机构参数
						  IN  CartesianPose* i_Tool); // 工具参数

	// 工具坐标系下的增量位姿的转换
	void Robot_IncreTransTool(IN  double* currpos,     // 当前位姿
							  IN  double* increpos,    // 工具坐标系下的增量位姿
							  OUT double* outpos);     // 输出位姿
	// 用户坐标系下的增量位姿的转换
	void Robot_IncreTransUser(IN  double* currpos,     // 当前位姿
							  IN  double* increpos,    // 用户坐标系下的增量位姿
							  OUT double* outpos,      // 输出位姿
						      IN  CartesianPose* user);// 用户坐标系参数
public_function
	// 速度正解
	int Robot_ForwardVelocity(IN  double* jvel,         // 关节速度
							  IN  JointPose* jpos,      // 关节转角
							  OUT double* cvel,         // 速度(在坐标系coor下的笛卡儿速度) 
							  IN  LinkDimension* robot, // 机器人结构参数 
							  IN  CartesianPose* tool,  // 机器人工具参数
							  IN  int coor);            // 坐标系
	// 速度逆解
	int Robot_InverseVelocity(IN  double* cvel,         // 速度(在坐标系coor下的笛卡儿速度)
							  IN  JointPose* jpos,      // 关节转角
							  OUT double* jvel,         // 关节速度
							  IN  LinkDimension* robot, // 机器人结构参数 
							  IN  CartesianPose* tool,  // 机器人工具参数
							  IN  int coor);            // 坐标系

	// 速度逆解(奇异过渡)
	int Robot_InverseVel_SinAvoid(IN  double* cvel,         // 速度(在坐标系coor下的笛卡儿速度) 
								  IN  JointPose* jpos,      // 关节转角 
								  OUT double* jvel,         // 关节速度
								  IN  LinkDimension* link, // 机器人结构参数  
								  IN  CartesianPose* tool,  // 机器人工具参数
								  IN  int coor);            // 坐标系

	void BaseToUserFrame(IN CartesianPose* UserRef, IN CartesianPose* PosBase, OUT CartesianPose* PosUserRef);

public_function
	// 四元数
	void EulerToQuaternion(IN Euler* e, OUT Quaternion* q);
	void QuaternionToEuler(IN Quaternion* q, OUT Euler* e);
	Quaternion Multi_Quat_Quat(IN Quaternion* q1, IN Quaternion* q2);
	Quaternion Multi_Quat_Cons(IN Quaternion* q,  IN double val);
	Quaternion Plus_Quat_Quat (IN Quaternion* q1, IN Quaternion* q2);
	Euler ChangeVel_QToEuler(IN Quaternion q, IN Quaternion v);
	Euler ChangeVel_QToAngle(IN Quaternion q, IN Quaternion v);



private_function
	// 正解 - 位姿矩阵表示
	int Robot_ForwardKine_Mtx(IN  JointPose* i_JPos, 
							  OUT PoseMatrix* o_Tcp,
							  IN  LinkDimension* i_Link, 
							  IN  CartesianPose* i_Tool);
	// 雅可比矩阵 - 工具坐标系表示
	void Robot_Jacobian_Tool(IN  JointPose* jpos, 
							 OUT Matrix* m, 
							 IN  LinkDimension* link);

#ifdef __cplusplus
}
#endif
#endif
