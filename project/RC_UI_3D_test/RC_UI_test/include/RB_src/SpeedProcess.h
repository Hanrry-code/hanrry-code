#ifndef __SPEEDPROCESS_H__
#define __SPEEDPROCESS_H__
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        S�Ӽ��ٴ���ṹ����                                                *
 *****************************************************************************/
#include "RobotGlobalStruct.h"


// �켣�������
#ifndef _TRAJPOINTPARA_
#define _TRAJPOINTPARA_
typedef struct _trajPointPara
{
	double Acc; // ���ٶ�
	double Vel; // �ٶ�
	double Len; // ����
}TrajPointPara;
#endif

// �켣����������
typedef struct _spdPTrajInputData
{
	double Len;  // �켣�γ���
	double Vs;   // ��ʼ�ٶ�
	double V;    // �����ٶ�
	double Ve;   // �յ��ٶ�
	double Acc;  // �����ٶ�
	double Jerk; // ���Ӽ��ٶ�
	double T_Acc;// ����ʱ��
}SpdPTrajInputData;

// �켣���������
typedef struct _spdPTrajData
{
	double Len;  // �켣�γ���
	double Vs;   // ��ʼ�ٶ�
	double V;    // �����ٶ�
	double Ve;   // �յ��ٶ�

	double Jacc;
	double Jdec;

	double T1;   // ����ʱ��
	double T2;
	double T3;
	double T4;
	double T5;
	double T6;
	double T7;
	
	double T;    // �滮��ʱ��

	double V1;   // ���ζ˵��ٶ�
	double V2;
	double V3;
	double V4;
	double V5;
	double V6;

	double L1;  // ���ζ˵�λ��
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


//--------------------------------- ���� ------------------------------------//
public_function
	// T�Ӽ��ٹ滮
	int SpeedPlanningT(IN SpdPTrajInputData* pIn, OUT SpdTrajStruct* pOut);
	// S�Ӽ��ٹ滮
	int SpeedPlanningS(IN SpdPTrajInputData* pIn, OUT SpdTrajStruct* pOut);
	// ��ȡ�켣
	void Get_SpeedProcessData(IN SpdTrajStruct* pIn, IN double dTime, OUT TrajPointPara* pOut);
	// ����ʱ��滮	
	int SpeedPlanningSByTime(IN  SpdPTrajInputData *in,
							 IN  double Time, 
							 OUT SpdTrajStruct *out);
	int SpeedPlanningSByVmod(IN SpdPTrajInputData *in,
							 IN double Time,
							 OUT SpdTrajStruct *out);
	// �滮�켣ʱ��
	double TimePlanningT(SpdPTrajInputData* p);

private_function
	// ��һԪ���η���
	double Solve_Equation3(double a, double b, double c, double d, double val);
	// ��һԪ���η���
	int Solve_Equation2(double a, double b, double c, double* res1, double* res2);
	// ��ȡ���ٶκͼ��ٶξ���
	void Get_AccDecLen(SpdTrajStruct *out, double* sacc, double *sdec);
#ifdef __cplusplus
}
#endif


#endif
