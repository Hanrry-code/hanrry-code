#ifndef __DIVFUN_H__
#define __DIVFUN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "RobotGlobalStruct.h"


//���������ò���
short Set_Robot_Init();//�����˳�ʼ��

short Set_Robot_Simulation_Init();//�����˳�ʼ��

short Set_RobotLink(double *link); // ���������˲���

short Set_RobotCurrentToolPose(CartesianPose Posetool);  // �����˹��߲���

short Set_RobotCurrentUserPose(CartesianPose Poseuser); // �������û�����

short Set_RobotTableConfig(CartesianPose Pose1,CartesianPose Pose2); // ������ת̨����


//�����˹ؽڲ���
short Set_JointMaxVel(double *vel);  // �ؽ��ٶ�����, deg/s

short Set_JointStopDec(double *vel);  // �ؽڼ��ٶ�

short Set_JointLimit(double *Npos,double *Ppos);  // �ؽ���λ

short Set_JointMaxAcc(double *value);  // �ؽ������ٶ�

//�����˵ѿ�������
short Set_PoseMaxVel(double PosVel,double GesVel,double TabVel); //λ������ٶ�

short Set_PoseMaxAcc(double PosAcc,double GesAcc,double TabAcc); //λ�˼��ٶ�

short Set_PoseMaxDec(double PosDec,double GesDec,double TabDec);  //λ�˼��ٶ�

//�����˵����ز���
short Set_MotorRatio(double *value); // ������ٱ�

short Set_MotorDirection(int *value);  // �������

////////////////////////////////////////////////////
//JOG��
////////////////////////////////////////////////////
//short Cmd_JogInit();//�����ֶ�ģʽ

//short Cmd_JogCoord(int coord); //�����ֶ�����ϵ

//short Cmd_JogPara(); //�����ֶ�����

short Cmd_JogStop(int axis,int Stop); //�ֶ�ʾ��ֹͣ

short Cmd_JogStart_Length(int axis,int coord,int Dir,double Acc,double length);

short Cmd_JogStart_Speed(int axis,int coord,int Dir,double Acc,double ratio);

short Cmd_DragStart_Speed(double acc,double ratio);

short Cmd_DragStop(int Stop); //6ά��������ʾ��ֹͣ
////////////////////////////////////////////////////
//�岹��
////////////////////////////////////////////////////
short Cmd_AutoInit(); //�Զ���ʼ��

short Cmd_Data_MOVJ(); //�ؽ�

short Cmd_Data_MOVL(); //ֱ��

short Cmd_Data_MOVC(); //Բ��

short Cmd_Data_IO(); //IO

short Cmd_Data_Delay(); //�ӳ�

short Cmd_BufferClear(); // ��������ʼ��

short Cmd_BufferSpace(); // ������ʣ��

short Cmd_AutoStart(); //�����Զ�

short Get_AutoState(); //�Զ��岹״̬

////////////////////////////////////////////////////
//��Ϣ��ȡ��
////////////////////////////////////////////////////
short Get_ActPos(double *actpos); //��ȡ�ؽ�ʵ��λ��

short Get_JointPos(double *Jointpos); //��ȡ�ؽ�ָ��λ��

short Get_PosePos(double *Posepos); //��ȡ�ѿ���ָ��λ��

short Get_JointVel(double *Jointvel); //��ȡ�ؽ�ָ���ٶ�

short Get_PoseVel(double *Posevel); //��ȡ�ѿ���ָ���ٶ�

////////////////////////////////////////////////////
//�岹�ں�������
////////////////////////////////////////////////////
short Run_InterpCore(); //�����˲岹�ں�����һ��
#ifdef __cplusplus
}
#endif

#endif

