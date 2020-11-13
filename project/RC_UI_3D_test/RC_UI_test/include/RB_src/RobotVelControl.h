#ifndef __ROBOTVELCONTROL_H__
#define __ROBOTVELCONTROL_H__
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        再现速度控制                                                       *
 *****************************************************************************/
// * 功能：再现运动时，实时改变运动速度
// * 通讯：与ARM通过参数(*m_pPctAutoVel)交互，参数表示再现运动速度百分比(0-100)
//         100%表示按照原程序编程速度运行，0%表示当前速度为0(实现暂停?).
// * 原理：控制时间增量，incT(时间增量) = T(插补周期) * pct(百分比) / 100

#ifndef Boolean
#define Boolean unsigned short
#endif

#define TIME_AUTOVELCHANGE  500//1200   // 再现速度从100%变化到0%所需要的时间, ms
#define TIME_AUTOVELSTOP    100   // 250

#define ACC_AUTOVELCTRL    64
#define VEL_AUTOVELCTRL     3


#define MODE_AUTOVEL_INCRE  1
#define MODE_AUTOVEL_DECRE -1
#define MODE_AUTOVEL_STOP   0

typedef struct _velPctStruct
{
	Boolean Enable;
	
	double P1;    // 首点
	double P2;    // 末点
	double A1; // 加速段加速度
	double V1; // 初速度
	double T1; // 加速段时间
	double T2; // 总时间

	double time;  // 当前时间
	double vel;  // 当前速度
	double pos;  // 当前位置

}VelPctStruct;

typedef struct _velCtrlStruct
{
	int Mode; // 模式, 1加 | 0停止 | -1减

	double Pos; // 当前位置, [0,1]
	double Vel; // 当前速度, 
}VelCtrlStruct;

//public_function
	void Init_AutoVelControl(int pct);        // 初始化 
	int Set_AutoVelPct(int pct, int mode);// 设置目标速度比
	void Set_AutoVelCtrl(int mode);
	int  Get_AutoVelCtrl();
	double Get_AutoVelPct(Boolean renew);        // 获取当前速度比


#ifdef __cplusplus
}
#endif
#endif
