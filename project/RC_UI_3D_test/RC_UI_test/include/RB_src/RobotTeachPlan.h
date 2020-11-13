#ifndef __ROBOTTEACHPLAN_H__
#define __ROBOTTEACHPLAN_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        Robotʾ�̽ṹ����                                                  *
 *****************************************************************************/
#include "RobotGlobalStruct.h"
#include "RobotError.h"

#ifndef INPUTTEACHDATA
#define INPUTTEACHDATA
// ����ʾ�����ݽṹ����
typedef struct _inputTeachData
{
	int Stop; // ʾ��״̬ stop-1 run - 2
	int Coor; // �ؽڡ�ֱ�ǡ����ߡ�����
	int Aix;  // ��1-6
	int Vel;  // �ٶȰٷֱ�
	int Dir;  // ���� -1/1 
	int Acc;  // ���ٶ�
	double Pos;
}InputTeachData;
#endif

// ʾ�̽ṹ����
typedef struct _teachStruct
{
	//------ ���� ------//
	double Interp_T;          // �岹����
	int Tacc;                 // ����������   - �ؽ� | �ѿ���
	int Flag[MOF];       // �����˶�״̬ - JC
	int Dir[MOF];        // ����ʾ�̷��� - JC
    int Time[MOF];       // �������ڼ��� - JC,//�Ӵ���С��
	double Vel[MOF];     // ���������ٶ� - JC

	//---- ����ʾ�� ----//
	double T_Acc;
	double Total_T[MOF]; // �˶���ʱ��
    double Start_Pos[MOF];  /*  ��ʼλ��	*/
	double Tar_Pos[MOF]; // Ŀ��λ��

	double Act_T[MOF];   // ��ǰʱ��

	//------ ���� ------//
	double Jerk[MOF];    // �Ӽ��ٶ� - JC
	double Act_Acc[MOF]; // ���ٶ�   - JC
	double Act_Vel[MOF]; // �����ٶ� - JC
	double Act_Pos[MOF]; // ����λ�� - JC

	//------ ��� ------//
	double O_Acc[MOF];   // ������ٶ� - JC
	double O_Vel[MOF];   // ����ٶ�   - JC
	double O_Pos[MOF];   // ���λ��   - JC

	// �ѿ�������ϵʾ��ר��
	double Curr_Vel[MOF];// ��ǰ�ٶ� - C
	double Curr_Pos[MOF];// ��ǰλ�� - C
}TeachStruct;

//--------------------------------- ���� ------------------------------------//
//public_function
	void Init_Teach(TeachStruct *p, int coor);                 // ��ʼ��ʾ��
	void Get_TeachData(InputTeachData* in, TeachStruct* out);  // ��ȡʾ����Ϣ
	int Teach(TeachStruct* p, double* posval, double* spdval, int (*Teach_Coor)());// �ص�
	int Robot_Teach(TeachStruct* p, double* posval, double* spdval, int coor);

//private_function
	// �ٶ�ģʽ
	int Teach_Joint_Vel(TeachStruct* p, double* posval, double* spdval);   // �ؽ�����ϵʾ��
	int Teach_World_Vel(TeachStruct* p, double* posval, double* spdval);   // ��������ϵʾ��
	int Teach_Tool_Vel(TeachStruct* p, double* posval, double* spdval);    // ��������ϵʾ��
	int Teach_User_Vel(TeachStruct* p, double* posval, double* spdval);    // �û�����ϵʾ��
	int Teach_Table_Vel(TeachStruct* p, double* posval, double* spdval);   // ת̨����ϵʾ��

	// λ��ģʽ
	int Teach_Joint_Pos(TeachStruct* p, double* posval, double* spdval);
	int Teach_World_Pos(TeachStruct* p, double* posval, double* spdval);
	int Teach_Tool_Pos(TeachStruct* p, double* posval, double* spdval);
	int Teach_User_Pos(TeachStruct* p, double* posval, double* spdval);
	int Teach_Table_Pos(TeachStruct* p, double* posval, double* spdval);
       //���������϶�
	int Robot_6dForceTeach(From_Sensor_t* fs, double* posval, double* spdval);

#ifdef __cplusplus
}
#endif
#endif
