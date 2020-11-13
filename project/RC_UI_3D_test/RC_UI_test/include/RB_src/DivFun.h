#ifndef __DIVFUN_H__
#define __DIVFUN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "RobotGlobalStruct.h"


//机器人配置参数
short Set_Robot_Init();//机器人初始化

short Set_Robot_Simulation_Init();//机器人初始化

short Set_RobotLink(double *link); // 机器人连杆参数

short Set_RobotCurrentToolPose(CartesianPose Posetool);  // 机器人工具参数

short Set_RobotCurrentUserPose(CartesianPose Poseuser); // 机器人用户参数

short Set_RobotTableConfig(CartesianPose Pose1,CartesianPose Pose2); // 机器人转台参数


//机器人关节参数
short Set_JointMaxVel(double *vel);  // 关节速度限制, deg/s

short Set_JointStopDec(double *vel);  // 关节减速度

short Set_JointLimit(double *Npos,double *Ppos);  // 关节限位

short Set_JointMaxAcc(double *value);  // 关节最大加速度

//机器人笛卡尔参数
short Set_PoseMaxVel(double PosVel,double GesVel,double TabVel); //位姿最大速度

short Set_PoseMaxAcc(double PosAcc,double GesAcc,double TabAcc); //位姿加速度

short Set_PoseMaxDec(double PosDec,double GesDec,double TabDec);  //位姿减速度

//机器人电机相关参数
short Set_MotorRatio(double *value); // 电机减速比

short Set_MotorDirection(int *value);  // 电机方向

////////////////////////////////////////////////////
//JOG类
////////////////////////////////////////////////////
//short Cmd_JogInit();//启动手动模式

//short Cmd_JogCoord(int coord); //启动手动坐标系

//short Cmd_JogPara(); //启动手动参数

short Cmd_JogStop(int axis,int Stop); //手动示教停止

short Cmd_JogStart_Length(int axis,int coord,int Dir,double Acc,double length);

short Cmd_JogStart_Speed(int axis,int coord,int Dir,double Acc,double ratio);

short Cmd_DragStart_Speed(double acc,double ratio);

short Cmd_DragStop(int Stop); //6维力传感器示教停止
////////////////////////////////////////////////////
//插补类
////////////////////////////////////////////////////
short Cmd_AutoInit(); //自动初始化

short Cmd_Data_MOVJ(); //关节

short Cmd_Data_MOVL(); //直线

short Cmd_Data_MOVC(); //圆弧

short Cmd_Data_IO(); //IO

short Cmd_Data_Delay(); //延迟

short Cmd_BufferClear(); // 缓冲区初始化

short Cmd_BufferSpace(); // 缓冲区剩余

short Cmd_AutoStart(); //启动自动

short Get_AutoState(); //自动插补状态

////////////////////////////////////////////////////
//信息读取类
////////////////////////////////////////////////////
short Get_ActPos(double *actpos); //获取关节实际位置

short Get_JointPos(double *Jointpos); //获取关节指令位置

short Get_PosePos(double *Posepos); //获取笛卡尔指令位置

short Get_JointVel(double *Jointvel); //获取关节指令速度

short Get_PoseVel(double *Posevel); //获取笛卡尔指令速度

////////////////////////////////////////////////////
//插补内核运行类
////////////////////////////////////////////////////
short Run_InterpCore(); //机器人插补内核运行一次
#ifdef __cplusplus
}
#endif

#endif

