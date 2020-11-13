#ifndef __ROBOTINTERPOLATION_H__
#define __ROBOTINTERPOLATION_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        �滮���岹���ƺ���                                                 *
 *****************************************************************************/
#include "RobotGlobalStruct.h"
#include "RobotKinematics.h"
#include "SpeedProcess.h"
#include "RobotQueue.h"
#include "RobotErrorPlan.h"
#include "RobotVelControl.h"

#define PATH_BUF_MAX_LEN        17//6//5  // ·������������
#define TRAJECTORY_BUF_LEN_MIN  18//6  // �켣��������С����
#define TRAJECTORY_BUF_LEN_MAX 36//14//12//10  // �켣��������󳤶�

#ifndef ABS
#define ABS(a)		((a)>=0?(a):(-(a)))
#endif
#define Count(n)    (((n) + PATH_BUF_MAX_LEN) % PATH_BUF_MAX_LEN) // ·��������������
#define Cnt(n)    (((n) + TRAJECTORY_BUF_LEN_MAX) % TRAJECTORY_BUF_LEN_MAX)
//------------------------------- �ṹ���� ----------------------------------//
// MOVJ·������
typedef struct _jointPathFeature
{
	double JPos_Start[MOF];  // ���
	double JPos_Mid1[MOF];
	double JPos_Mid2[MOF];
	double JPos_End[MOF];    // ĩ��
	double JVel_Cons[MOF];   // ���ٶ�

	double Time;
}JointPathFeature;

// �ռ�����
typedef struct _vectorStruct
{
	double X;   // ����x
	double Y;   // ����y
	double Z;   // ����z
	double Con; // ����
}VectorStruct;

// �ѿ���·������
typedef struct _cartesianPathFeature
{
	double JPos_Start[MOF];   // ���ؽڽ�
	double JPos_Mid[MOF];     // Բ���м��ؽڽ�
	double JPos_End[MOF];     // ĩ��ؽڽ�

	CartesianPose CPos_Start; // ���λ��
	CartesianPose CPos_Mid;   // Բ���м��λ��
	CartesianPose CPos_End;   // ĩ��λ��

	double Car_PAcc;          // �߼��ٶ�
	double Car_PVel;          // �������ٶ�
	double PosLen;            // ·������, ֱ�߳��Ȼ�Բ������
	double Car_GAcc;          // ��̬���ٶ�
	double Car_GVel;          // ������̬�ٶ�
	double GesAng;            // ��̬��
	Boolean Flag_Reverse;

	double Time;
	VectorStruct Line_Vector; // ֱ�ߵ�λ����, ����Con = 1
	double Angle_Vector[2];  //��ת��λ����
	double Car_Vec;      //�ѿ������ȷ���

	PoseMatrix   Arc_Matrix;  // Բ��UVW������ϵ����
	VectorStruct Arc_Centre;  // Բ�����꼰�뾶
	double       Arc_Radian;  // Բ���Ļ���
	double       Arc_MidLen;  // Բ���м���Ӧ�Ļ���

}CartesianPathFeature;

// ·��
typedef struct _interpPathStruct
{
	InputAutoData Input;

	JointPathFeature  JointPath;
	CartesianPathFeature CartePath;
}InterpPathStruct;


// �켣
typedef struct _InterpTrajectoryStruct
{
	// ������
    // ��ʾ�õ�
    char name[20];
	
    // ����Ĳ����
    // ʵʱͬ���õ�
    unsigned int decode_id ;

	//------------------- ����Ϣ --------------------//
	int Prog_SequNum;         // ��ǰ����α��	
	int Prog_LineNum;         // ��ǰ�����б��
	int Prog_Mark;            // �����־, 1-start/2-end/0-mid	
	int Mode;                 // ������ģʽ, �˶���-1 | IO-2 | Delay-3
	int Interp_Mode;          // �岹��ʽ - MOVJ 1 | MOVL 2 | MOVC 3 | MOVP 4
	int IfTransSeg;           // �Ƿ��ǹ��ɶ�, 1��/0��

	//------------------ �˶����� --------------------//
	double TotleTime;		  //��ǰ����ʱ��
	double Time;              // ��ʱ��

	double JPos_Start[MOF];   // ʼ��ؽڽ�
	double JPos_End[MOF];     // ĩ��ؽڽ�
	
// [[ �ؽڲ岹
	double JVel_Start[MOF];   // MOVJ �ؽڳ��ٶ�
	double JVel_End[MOF];     // MOVJ �ؽ�ĩ�ٶ�
// ]]

// [[ �ѿ����岹
	CartesianPose CPos_Start;   // ʼ��λ��
	CartesianPose CPos_End;     // ĩ��λ��
	PoseMatrix    Arc_Matrix;   // Բ��UVW������ϵ����
	VectorStruct  Arc_Centre;   // Բ�����꼰�뾶
	double        Arc_Len_Start;// Բ����ʼ�㻡��
	SpdTrajStruct Traj_CPos;    // λ�ù켣, �ǹ��ɶ�ʹ��
	SpdTrajStruct Traj_CGes;    // ��̬�켣
	Boolean          Ges_Reverse;  // ��̬����岹��־, 1���� | 0����
	double        CVel_Start[MOF];// λ�ó��ٶ�, ���ɶ�ʹ��
	double        CVel_End[MOF];  // λ��ĩ�ٶ�, ���ɶ�ʹ��

	double Car_Vec;      //�ѿ������ȷ���

	VectorStruct Line_Vector; // ֱ�ߵ�λ����, ����Con = 1
// ]]

	//------------------ �˶����� --------------------//
	// [[ IO����Ϣ
	int IO_Mode;          // 1-���� | 2-���
	int IO_Name;          // IO���
	int IO_Value;         // IOֵ, 1-true | 0-false
	// ]]
	int WaitTime;         // �ȴ�ʱ��, ms

	// Mode == 10 ����
	// 1 ARCON
	// 2 ARCOF
	// 3 ARCCT 
	// ----4 ARCSET----11,12,13
	// 5 AWELD
	// 6 VWELD

	// 11 ARCSET  av
	// 12 ARCSET  ac
	// 13 ARCSET  v
	int order ;      
	// ����
	float AC ;
	// ��ѹ
	float AVP ;
	// ʱ��
	float T ;
	// �ٶ�
	float V ;
	// 1 ds
	// 2 es
	int  dis_type;    
	float dis;
       /*int SonMode;         //������ģʽ
       int DsorDe;           //0-��Ч 1-Ds   2-De
       float Distance;     //����mm
       float Av;              //��ѹV
       float Acc;            //����A*/
}InterpTrajectoryStruct;


// ·��������
typedef struct _path_Buffer
{
	InterpPathStruct Data[PATH_BUF_MAX_LEN];   
	U16 Start;
	U16 End;
	U16 Now;
	
	U16 Num;
}Path_Buffer;


// �켣������
typedef struct _trajectory_Buffer
{
	InterpTrajectoryStruct Data[TRAJECTORY_BUF_LEN_MAX];
	U16 Start;
	U16 End;
}Trajectory_Buffer;


// �ؽڿռ�岹�ṹ��
typedef struct _jointInterpStruct
{
	int Degree;     // �岹������ߵ���ߴ���
	double Pos0[MOF]; // ��һ������
	double Pos1[MOF]; // �ڶ���
	double Pos2[MOF]; // ������
	double Pos3[MOF]; // ���ĵ�
	double Pos4[MOF]; // ����� 
	int Num;        // ÿ���ڲ岹����
	int Count;      // �岹�����
}JointInterpStruct;


//------------------------------- ����˵�� ----------------------------------//
public_function // �����
	int Minimize_RadRot(double start, double* end);
	int Get_ForwardPos(IN double* jpos, OUT CartesianPose* cpos);
	int Get_InversePos(IN CartesianPose* cpos, IN double* jcurrpos, OUT double* jpos);
	int Get_ForwardVel(IN double* jpos, IN double* jvel, OUT double* cvel);
	int Get_InverseVel(IN double* jpos, IN double* cvel, OUT double* jvel);
	int Get_InverseVel_SinAvoid(IN double* jpos, IN double* cvel, OUT double* jvel);


public_function
	void Init_Interpolation(double* pos);          // ���ֳ�ʼ��
	int Plan_Path(InterpPathStruct *path);         // ·���滮
	int Plan_Trajectory(IN Path_Buffer* p, OUT Trajectory_Buffer* buf); // �켣�滮
	int Interpolation(Trajectory_Buffer* p, Queue* q); // �岹
	
	// �ؽڿռ�켣�滮
	void Init_JointInterp(double* pos, int degree);          // ��ʼ���ؽڲ岹
int Get_JointInterpData(Queue* que, ElemType* elem, double* posval, double* spdval); // ��ȡ�ؽڲ岹����


private_function  // �켣������
	int  Get_TrajectoryBufNum(IN Trajectory_Buffer *buf);
	Boolean Put_TrajectoryBuffer(IN Trajectory_Buffer *buf, IN  InterpTrajectoryStruct *msg);
	Boolean Get_TrajectoryBuffer(IN Trajectory_Buffer *buf, OUT InterpTrajectoryStruct *msg);

	void Clear_PathBuffer      (IN Path_Buffer* buf);
	void Clear_TrajectoryBuffer(IN Trajectory_Buffer* buf);

private_function  // ·���滮
	Boolean Read_TrajectoryBuffer(IN Trajectory_Buffer *buf, 
						  OUT InterpTrajectoryStruct *msg);
	// MOVJ·���滮
	int Plan_Joint_Path (
			IN InputAutoData* in,           // ��������
			OUT JointPathFeature* out);     // MOVJ·��
	// MOVL·���滮
	int Plan_Linear_Path(
			IN InputAutoData* in,           // ��������
			OUT CartesianPathFeature* out); // MOVL·��
	// MOVC·���滮
	int Plan_Circle_Path(
			IN InputAutoData* in,            // ��������
			OUT CartesianPathFeature* out);  // MOVC·��

private_function  // �켣�滮
	// MOVJ�켣�滮
	int Plan_Joint_Trajectory (
			IN InterpPathStruct* now,    // ��ǰ��MOVJ·��
			IN InterpPathStruct* next,   // ��һ��MOVJ·��
			IN int premode,              // ��ǰһ�ι���ģʽ
			IN int nextmode,             // ����һ�ι���ģʽ
			OUT Trajectory_Buffer* buf); // �켣������
	// MOVL�켣�滮
	int Plan_Linear_Trajectory(           
			IN InterpPathStruct* pre,    // ǰһ��MOVL·��
			IN InterpPathStruct* now,    // ��ǰ��MOVL·��
			IN InterpPathStruct* next,   // ��һ��MOVL·��
			IN int premode,              // ��ǰһ�ι���ģʽ
			IN int nextmode,             // ����һ�ι���ģʽ
			OUT Trajectory_Buffer* buf); // �켣������
	// MOVC�켣�滮
	int Plan_Circle_Trajectory(
			IN InterpPathStruct* pre,    // ǰһ��MOVC·��
			IN InterpPathStruct* now,    // ��ǰ��MOVC·��
			IN InterpPathStruct* next,   // ��һ��MOVC·��
			IN int premode,              // ��ǰһ�ι���ģʽ
			IN int nextmode,             // ����һ�ι���ģʽ
			OUT Trajectory_Buffer* buf); // �켣������

private_function  // �岹
	int Get_JointInterpPoint   (IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);
	int Get_LinearInterpPoint  (IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);
	int Get_ParabolaInterpPoint(IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);
	int Get_QuinticInterpPoint (IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);
	int Get_InterpPoint        (IN InterpTrajectoryStruct* p, IN double t, OUT ElemType* e);

	int Insert_InterpPoint(Queue* q, ElemType e);

private_function // ���ɶβ���
	void Get_ZoneLine_PosVel(IN CartesianPathFeature* line, // ֱ��·��
			IN int zone,                   // ���ɵȼ�
			IN Boolean start,                 // �Ƿ��ǿ�ʼ��
			OUT CartesianPose* cpos,       // ���ɵ�����
			OUT double tpos[2],            // ���ɵ�ת̨����
			OUT VectorStruct* pvec,        // ���ɵ��ٶ�
			OUT VectorStruct* gvec,        // ���ɵ���ٶ�
			OUT double tvec[2],            // ���ɵ�ת̨�ٶ�
			OUT double* zlen,              // ���ɶ�λ��
			OUT double* zges,              // ���ɶν�λ��
			IN int mode);

	void Get_ZoneArc_PosVel(IN CartesianPathFeature* arc,  // Բ��·��
			IN int zone,                   // ���ɵȼ�
			IN Boolean start,                 // �Ƿ��ǿ�ʼ��
			OUT CartesianPose* cpos,       // ���ɵ�����
			OUT double tpos[2],            // ���ɵ�ת̨����
			OUT VectorStruct* pvec,        // ���ɵ��ٶ�
			OUT VectorStruct* gvec,        // ���ɵ���ٶ� 
			OUT double tvec[2],            // ���ɵ�ת̨�ٶ�
			OUT double* zlen,              // ���ɶλ���
			OUT double* zges,              // ���ɶν�λ��
			IN int velmode);                // ���ع��ɵ��ٶ�ģʽ

	double Get_ZoneTime_JointSpace(IN double p1[], 
			IN double p2[], 
			IN double v1[], 
			IN double v2[],
			IN int velpct);

	double Get_ZoneTime_CartesianSpace(IN double pos1[MOF], 
			IN double pos2[MOF], 
			IN double v1[MOF], 
			IN double v2[MOF],
			IN double maxpv,
			IN double maxgv,
			IN double maxtv);

private_function // ��̬
	// ��ȡ����֮�����̬�н�
	double Get_Attitude_Angle(
			IN CartesianPose* cpos1,        // �׵�λ��
			IN CartesianPose* cpos2,        // ĩ��λ��
			OUT Boolean* inverse);             // ��̬������ת��־
	// ��ȡ��̬�岹�м��ŷ����
	Euler Get_Gesture_Euler(
			IN CartesianPose* cpos1,        // �׵�λ��
			IN CartesianPose* cpos2,        // ĩ��λ��
			IN double angle,                // ��̬�н�
			Boolean reverse,                   // ��̬������ת��־
			double h);                      // [0,1]����

	Euler Get_Gesture_Vel(
			IN CartesianPose* cpos1, // �׵�λ��
			IN CartesianPose* cpos2, // ĩ��λ��
			IN double angle,         // ��̬�н�
			IN Boolean reverse,         // ������ת��־
			IN double h,             // [0,1]����
			IN double hvel,
			IN int mode);         // h�ٶ�


public_function

// �켣�岹״̬
typedef struct _interpolationState
{
	Boolean Enable;    // �岹ʹ��״̬
	double Time;    // ��ǰ�岹ʱ��
	InterpTrajectoryStruct Traj; // ��ǰ�岹�켣��

	Boolean IfEndPoint;   // ĩ���־
	ElemType EndPoint; // ĩ��
	
}InterpolationState;

#ifdef __cplusplus
}
#endif
#endif
