#ifndef __ROBOTVELCONTROL_H__
#define __ROBOTVELCONTROL_H__
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        �����ٶȿ���                                                       *
 *****************************************************************************/
// * ���ܣ������˶�ʱ��ʵʱ�ı��˶��ٶ�
// * ͨѶ����ARMͨ������(*m_pPctAutoVel)������������ʾ�����˶��ٶȰٷֱ�(0-100)
//         100%��ʾ����ԭ�������ٶ����У�0%��ʾ��ǰ�ٶ�Ϊ0(ʵ����ͣ?).
// * ԭ������ʱ��������incT(ʱ������) = T(�岹����) * pct(�ٷֱ�) / 100

#ifndef Boolean
#define Boolean unsigned short
#endif

#define TIME_AUTOVELCHANGE  500//1200   // �����ٶȴ�100%�仯��0%����Ҫ��ʱ��, ms
#define TIME_AUTOVELSTOP    100   // 250

#define ACC_AUTOVELCTRL    64
#define VEL_AUTOVELCTRL     3


#define MODE_AUTOVEL_INCRE  1
#define MODE_AUTOVEL_DECRE -1
#define MODE_AUTOVEL_STOP   0

typedef struct _velPctStruct
{
	Boolean Enable;
	
	double P1;    // �׵�
	double P2;    // ĩ��
	double A1; // ���ٶμ��ٶ�
	double V1; // ���ٶ�
	double T1; // ���ٶ�ʱ��
	double T2; // ��ʱ��

	double time;  // ��ǰʱ��
	double vel;  // ��ǰ�ٶ�
	double pos;  // ��ǰλ��

}VelPctStruct;

typedef struct _velCtrlStruct
{
	int Mode; // ģʽ, 1�� | 0ֹͣ | -1��

	double Pos; // ��ǰλ��, [0,1]
	double Vel; // ��ǰ�ٶ�, 
}VelCtrlStruct;

//public_function
	void Init_AutoVelControl(int pct);        // ��ʼ�� 
	int Set_AutoVelPct(int pct, int mode);// ����Ŀ���ٶȱ�
	void Set_AutoVelCtrl(int mode);
	int  Get_AutoVelCtrl();
	double Get_AutoVelPct(Boolean renew);        // ��ȡ��ǰ�ٶȱ�


#ifdef __cplusplus
}
#endif
#endif
