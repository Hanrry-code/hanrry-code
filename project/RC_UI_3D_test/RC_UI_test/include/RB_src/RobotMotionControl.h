#ifndef __ROBOTMOTIONCONTROL_H__
#define __ROBOTMOTIONCONTROL_H__
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        �������˶�����                                                     *
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
	int Init_Robot();                // ��ʼ��
	void Task_IOControl();           // IO����
	void Task_ReadMotionData();      // ����ͨѶ����ARM��ȡ����
	void Task_ReadSystemData();      // �������ã���ARM��ȡϵͳ����
	void Task_UpdateStatus();        // ״̬��أ�д״̬������ARM
	void Task_MotionProcess();       // ʵʱ�˶�
	void Task_PathPlanning();        // ·���滮
	void Task_TrajectoryPlanning();  // �켣�滮
	void Task_IdleProcess();         // ��̨�����岹

	void PathPlanning();
	int SetDelay(unsigned int t, unsigned int Timer);

	int IntefZoneJudge(double* JPosArray);
private_function
	void JointToMotor(double* posval, int* pulse);
	int MotorToJoint(int* pulse, double* posval);
	int Refresh_JointPos(double* motor, double* jpos); // ��ȡ�ؽ�ת��, deg

	void Init_GlobalState();   // ��ʼ��ȫ�ֲ���
	void Clear_MotionBuffer(); // Clear������
	int  ClearAlarm();        // �����˸�λ

    void Update_RealtimeStatus(); // ʵʱ״̬����
	
	int RequestServoParamInLoop(void);
	int RevAndSendServoParam(void);
	int ProcessGdt(void);
	int ReadIO( IoCardCtrl	*IOBuf,	// IO �����ַ
			unsigned char	Type,	// IO ���ͣ�1--���֣�2--ģ��
			unsigned char	Index, 	// IO �������(��0��ʼ)
			int				*Value,	// ģ��I/O--ʵ�ʿ��Ƶ�ѹ
			unsigned char	Ritio);	// ģ�������ʵ�ʿ��Ƶ�ѹ��ת������

	int SetIO( IoCardCtrl	*IOBuf,	// IO �����ַ
			unsigned char	Type,	// IO ���ͣ�1--���֣�2--ģ��
			unsigned char	Index, 	// IO �������(��0��ʼ)
			int				Value,	// ģ��I/O--ʵ�ʿ��Ƶ�ѹ
			unsigned char	Ritio);	// ģ�������ʵ�ʿ��Ƶ�ѹ��ת������

	void IOProcess(void);
	void ProgRunProcess(void);
	void GetDspState(void);

	/*void SetDSPStateLight(	unsigned char Index, 	//״̬�Ʊ��
						unsigned char Light);	//1 ������0 ����
	void DSPStateLightBlink(UD_DSPStateLightParam* DSPStateLightParam,	//IO�����ڲ�����
			 			unsigned char Index, 		//�ƺ�
			 			unsigned char Ritio, 		//����ʱ��ռ������˸���ڵı���
			 			unsigned int Interval, 		//��˸����
			 			unsigned char Timer);		//��ʱ������
*/
public_variable
//	extern TeachStruct gs_Teach;            // ʾ�̽ṹȫ�ֱ���
//	extern InputTeachData gs_TeachInput;    // ʾ����������ȫ�ֱ���
//	extern Path_Buffer gs_PathBuffer;       // ·������������
//	extern Trajectory_Buffer gs_TrajBuffer; // �켣����������
	extern Queue gs_queue;                  // ѭ������  - ȫ�ֱ���
	extern ElemType elemRecd;             // ѭ�����е�λ����
	extern Boolean gb_queueClear;
	extern unsigned char DlyReq;	//��ʱ���Ʊ�־
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
