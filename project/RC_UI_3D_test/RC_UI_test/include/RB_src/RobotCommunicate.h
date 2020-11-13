#ifndef __ROBOTCOMMUNICATE_H__
#define __ROBOTCOMMUNICATE_H__


#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        ��ARMͨѶ                                                          *
 *****************************************************************************/
#include "RobotTeachPlan.h"
#include "RobotInterpolation.h"
#include "Communicate.h"

public_function
	void Init_Communicate();          // ��ʼ����ARMͨѶ
	Boolean Clear_MotionData_ARM();      // Clear�˶�����

	int  Read_EStop_FromARM();
//	int  Read_Abort_FromARM();        // ��ȡAbort
	int  Read_MachineStop_FromARM();  // ��ȡ��е����
	Boolean Read_OnlineData_FromARM();   // ��ȡ����ָ��
	Boolean Read_JointData_FromARM();    // ��ȡ�ؽ�����
	Boolean Read_CartesianData_FromARM();// ��ȡ�ѿ�������
	Boolean Read_MotorData_FromARM();    // ��ȡ������
	Boolean Read_RobotData_FromARM();    // ��ȡ����������
	Boolean Read_CPSTRITIOData_FromARM();// ��ȡ�����˲�����������
	Boolean Read_AbsZeroSet_FromARM();

	Boolean Read_TeachData_FormARM(InputTeachData* data); // ��ȡʾ������
	Boolean Read_AutoData_FromARM(OUT Path_Buffer *buf);  // ��ȡ��������

	void ReadIntfZoneData();
	void ReadUserFrameData();

	void Set_Data_ToARM();  // д���ݵ�ARM

	void Send_Stop_ToDSP();          // ����ָֹͣ��
	void Reset_AutoVelPct_ToArm();
	void Send_Enable_ToMotor(Boolean en);


#ifdef __cplusplus
}
#endif

#endif
