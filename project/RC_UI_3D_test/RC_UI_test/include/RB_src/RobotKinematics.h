#ifndef __ROBOTKINEMATICS_H__
#define __ROBOTKINEMATICS_H__
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        �������˶�ѧ����                                                   *
 *****************************************************************************/
#include "RobotGlobalStruct.h"
#include "RobotMatrix.h"

#define KINE_RATIO_V   800
#define KINE_DAMP_EI   500
#define KINE_DAMP_EB   500
#define KINE_RATIO_W  0.08
#define KINE_DAMP_EW  0.087


// ŷ����
typedef struct _euler
{
	double W;
	double P;
	double R;
}Euler;

// ��Ԫ��
typedef struct _quaternion
{
	double P0;
	double P1;
	double P2;
	double P3;
}Quaternion;

//--------------------------------- ���� ------------------------------------/
public_function
	// ����
	int Robot_ForwardKine(IN  JointPose* i_JPos,      // �ؽڽ�
						  OUT CartesianPose* o_CPos,  // λ��
						  IN  LinkDimension* i_Link,  // �����˻�������
						  IN  CartesianPose* i_Tool); // ���߲���

	// ���
	int Robot_InverseKine(IN  CartesianPose* i_CPos,  // λ��
						  IN  JointPose* i_JCurr,     // ��ǰ�ؽڽ�
						  OUT JointPose* o_JPos,      // �ؽڽ�
						  IN  LinkDimension* i_Link,  // �����˻�������
						  IN  CartesianPose* i_Tool); // ���߲���

	// ��������ϵ�µ�����λ�˵�ת��
	void Robot_IncreTransTool(IN  double* currpos,     // ��ǰλ��
							  IN  double* increpos,    // ��������ϵ�µ�����λ��
							  OUT double* outpos);     // ���λ��
	// �û�����ϵ�µ�����λ�˵�ת��
	void Robot_IncreTransUser(IN  double* currpos,     // ��ǰλ��
							  IN  double* increpos,    // �û�����ϵ�µ�����λ��
							  OUT double* outpos,      // ���λ��
						      IN  CartesianPose* user);// �û�����ϵ����
public_function
	// �ٶ�����
	int Robot_ForwardVelocity(IN  double* jvel,         // �ؽ��ٶ�
							  IN  JointPose* jpos,      // �ؽ�ת��
							  OUT double* cvel,         // �ٶ�(������ϵcoor�µĵѿ����ٶ�) 
							  IN  LinkDimension* robot, // �����˽ṹ���� 
							  IN  CartesianPose* tool,  // �����˹��߲���
							  IN  int coor);            // ����ϵ
	// �ٶ����
	int Robot_InverseVelocity(IN  double* cvel,         // �ٶ�(������ϵcoor�µĵѿ����ٶ�)
							  IN  JointPose* jpos,      // �ؽ�ת��
							  OUT double* jvel,         // �ؽ��ٶ�
							  IN  LinkDimension* robot, // �����˽ṹ���� 
							  IN  CartesianPose* tool,  // �����˹��߲���
							  IN  int coor);            // ����ϵ

	// �ٶ����(�������)
	int Robot_InverseVel_SinAvoid(IN  double* cvel,         // �ٶ�(������ϵcoor�µĵѿ����ٶ�) 
								  IN  JointPose* jpos,      // �ؽ�ת�� 
								  OUT double* jvel,         // �ؽ��ٶ�
								  IN  LinkDimension* link, // �����˽ṹ����  
								  IN  CartesianPose* tool,  // �����˹��߲���
								  IN  int coor);            // ����ϵ

	void BaseToUserFrame(IN CartesianPose* UserRef, IN CartesianPose* PosBase, OUT CartesianPose* PosUserRef);

public_function
	// ��Ԫ��
	void EulerToQuaternion(IN Euler* e, OUT Quaternion* q);
	void QuaternionToEuler(IN Quaternion* q, OUT Euler* e);
	Quaternion Multi_Quat_Quat(IN Quaternion* q1, IN Quaternion* q2);
	Quaternion Multi_Quat_Cons(IN Quaternion* q,  IN double val);
	Quaternion Plus_Quat_Quat (IN Quaternion* q1, IN Quaternion* q2);
	Euler ChangeVel_QToEuler(IN Quaternion q, IN Quaternion v);
	Euler ChangeVel_QToAngle(IN Quaternion q, IN Quaternion v);



private_function
	// ���� - λ�˾����ʾ
	int Robot_ForwardKine_Mtx(IN  JointPose* i_JPos, 
							  OUT PoseMatrix* o_Tcp,
							  IN  LinkDimension* i_Link, 
							  IN  CartesianPose* i_Tool);
	// �ſɱȾ��� - ��������ϵ��ʾ
	void Robot_Jacobian_Tool(IN  JointPose* jpos, 
							 OUT Matrix* m, 
							 IN  LinkDimension* link);

#ifdef __cplusplus
}
#endif
#endif
