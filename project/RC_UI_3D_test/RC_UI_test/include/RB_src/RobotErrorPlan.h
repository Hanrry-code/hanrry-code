#ifndef __ROBOTERRORPLAN_H__
#define __ROBOTERRORPLAN_H__


#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        ����滮                                                           *
 *****************************************************************************/
#include "RobotGlobalStruct.h"

// �켣��ʼ����
typedef struct _trajInitPara
{
	double Jerk; // �Ӽ��ٶ�
	double Acc;  // ���ٶ�
	double Vel;  // �ٶ�
	double Len;  // ����
}TrajInitPara;

// ����ֹͣ�岹��
#ifndef _TRAJPOINTPARA_
#define _TRAJPOINTPARA_
typedef struct _trajPointPara
{
	double Acc; // ���ٶ�
	double Vel; // �ٶ�
	double Len; // ����
}TrajPointPara;
#endif

// ����ֹͣ�ṹ��
typedef struct _errStopTrajStruct
{
	int Stop;      // ֹͣ��־
	
	double Interp_T; // �岹����
	
	double Time;   // ֹͣʱ��
	double T[MOF];   // 
	double Pos[MOF]; // ��ʼλ��
	double Vel[MOF]; // ��ʼ�ٶ�
	double Acc[MOF]; // ���ٶ�
	double Curr_T; // ��ǰʱ��
	
}ErrStopTrajStruct; 

public_function
	int Get_JointLimState(double* ld_pos, double* ld_vel); // ��ȡ�ؽڼ���״̬
	int Get_BoundarySinState(double* ld_pos, double* ld_vel);
	int Get_InternalSinState(double* ld_pos, double* ld_vel);

	int If_In_JointLim(double * pos);               // �жϹؽڵ��Ƿ���
	Boolean If_In_BoundarySin(double* pos1, double* pos2);
	Boolean If_In_InternalSin(double* pos1, double* pos2);

	void Init_ErrorStop(double* pos, double* vel, double* acc);// ����ֹͣ��ʼ��
	int Get_ErrorStop(double* posval, double* spdval); 
	Boolean IfTableZoneLimit(double jpos_start[MOF],double jpos_end[MOF]);

public_variable
	extern ErrStopTrajStruct gs_ErrStop;

#ifdef __cplusplus
}
#endif
#endif
