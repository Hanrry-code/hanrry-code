#ifndef __ROBOTMOTIONCONTROL_H__
#define __ROBOTMOTIONCONTROL_H__
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        机器人运动控制                                                     *
 *****************************************************************************/
#include "RobotCommunicate.h"
#include <string.h>

#define SetDSPStateLight(Index)   DSPStateLight|=(1<<(Index-1))
#define ClrDSPStateLight(Index)   DSPStateLight&=~(1<<(Index-1))
#define GetDSPStateLight(Index)  (DSPStateLight&(1<<(Index-1)))

#define LightProcess(index,period,light)   if(gs_timer.Count[index]++>period){gs_timer.Count[index]=0;\
                 if(GetDSPStateLight(light)) ClrDSPStateLight(light);\
		   else SetDSPStateLight(light);}
     
		 
public_function
	int Init_Robot();                // 初始化
	void Task_IOControl();           // IO控制
	void Task_ReadMotionData();      // 数据通讯：从ARM获取数据
	void Task_ReadSystemData();      // 参数设置：从ARM获取系统参数
	void Task_UpdateStatus();        // 状态监控：写状态参数到ARM
	void Task_MotionProcess();       // 实时运动
	void Task_PathPlanning();        // 路经规划
	void Task_TrajectoryPlanning();  // 轨迹规划
	void Task_IdleProcess();         // 后台处理：插补

	void PathPlanning();
	int SetDelay(unsigned int t, unsigned int Timer);

	int IntefZoneJudge(double* JPosArray);
private_function
	void JointToMotor(double* posval, int* pulse);
	int MotorToJoint(int* pulse, double* posval);
	int Refresh_JointPos(double* motor, double* jpos); // 获取关节转角, deg

	void Init_GlobalState();   // 初始化全局参数
	void Clear_MotionBuffer(); // Clear缓冲区
	int  ClearAlarm();        // 机器人复位

    void Update_RealtimeStatus(); // 实时状态更新
	
	int RequestServoParamInLoop(void);
	int RevAndSendServoParam(void);
	int ProcessGdt(void);
	int ReadIO( IoCardCtrl	*IOBuf,	// IO 缓冲地址
			unsigned char	Type,	// IO 类型，1--数字；2--模拟
			unsigned char	Index, 	// IO 输出点编号(从0开始)
			int				*Value,	// 模拟I/O--实际控制电压
			unsigned char	Ritio);	// 模拟输出到实际控制电压的转换比例

	int SetIO( IoCardCtrl	*IOBuf,	// IO 缓冲地址
			unsigned char	Type,	// IO 类型，1--数字；2--模拟
			unsigned char	Index, 	// IO 输出点编号(从0开始)
			int				Value,	// 模拟I/O--实际控制电压
			unsigned char	Ritio);	// 模拟输出到实际控制电压的转换比例

	void IOProcess(void);
	void ProgRunProcess(void);
	void GetDspState(void);

	/*void SetDSPStateLight(	unsigned char Index, 	//状态灯编号
						unsigned char Light);	//1 灯亮，0 灯灭
	void DSPStateLightBlink(UD_DSPStateLightParam* DSPStateLightParam,	//IO闪灯内部参数
			 			unsigned char Index, 		//灯号
			 			unsigned char Ritio, 		//点亮时间占整个闪烁周期的比例
			 			unsigned int Interval, 		//闪烁周期
			 			unsigned char Timer);		//定时器周期
*/
public_variable
//	extern TeachStruct gs_Teach;            // 示教结构全局变量
//	extern InputTeachData gs_TeachInput;    // 示教输入数据全局变量
//	extern Path_Buffer gs_PathBuffer;       // 路径缓冲区变量
//	extern Trajectory_Buffer gs_TrajBuffer; // 轨迹缓冲区变量
	extern Queue gs_queue;                  // 循环队列  - 全局变量
	extern ElemType elemRecd;             // 循环队列点位数据
	extern Boolean gb_queueClear;
	extern unsigned char DlyReq;	//延时控制标志
	extern unsigned char DlyStart;
	extern unsigned char StopStat;
	extern unsigned char HoldStat;
	extern unsigned char ResetStat;
	extern GlobalState gs_State;  
	extern CartesianPose RobotUserFrame[MAX_USERFRAME_NUM];
	extern IntfZone RobotIntfZone[MAX_INTRFZONE_NUM];
	

#ifdef __cplusplus
}
#endif
#endif
