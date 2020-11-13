#ifndef __ROBOTGLOBALSTRUCT_H__
#define __ROBOTGLOBALSTRUCT_H__


#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        �궨��                                                             *
 *****************************************************************************/
#include "RobotError.h"
#include "Communicate.h"



#define RELEASE_MODE		0	//�������з�����
#define PC_TEST_MODE		1	//PC������԰�
#define OFFLINE_TEST_MODE	2	//�ڲ��ѻ����԰�
#define DSP_STATE_TEST			//����DSP�ڲ�״̬��
#define MaxServoNum			7	//����վ���������ڲ��ѻ����԰�
#define IOBoard_EN			1	// IO��վ�Ƿ���Ч

#define DebugIfLostLine          0

//#define PROGRAM_VERSION OFFLINE_TEST_MODE //RELEASE_MODE//OFFLINE_TEST_MODE//

#define ARM_WAIT_DELAY 1 //0xFFFFFFFF

//#ifndef TEST_ROBOT_CONTROL  // ����ר��
//#define TEST_ROBOT_CONTROL
//#endif

#define MaxCompensatePulse        (100*gs_State.Motor_Precision[i]/10000)

#define PeriodCompensatePulse        (2*gs_State.Motor_Precision[i]/10000)

#define MAX_INTRFZONE_NUM 6
#define MAX_USERFRAME_NUM 10

/* ѭ�������ǰһ��Ԫ���±� */
#define Array_PreID(CurrID, Array_Size) (((CurrID) > 0) ? ((CurrID) - 1) : ((Array_Size) - 1))

// [[ �岹����
#define INTERP_MOTION_JERK     10000     // �Ӽ��ٶ�
#define INTERP_JOINT_DEGREE        4     // �ؽڲ岹����Degree
#define INTERP_FIFO_LENTH          40//24//12// 6// �岹����г���
#define INTERP_JOINT_MAXVELPCT  0.95     // �ؽ� �岹����ٶȰٷֱ�, 95%
#define INTERP_TEACH_MAXVELPCT  0.10     // ʾ������ٶȰٷֱ�, 20%
#define INTERP_TEACH_MAXCVEL     250     // �ѿ���ʾ������ٶ�, mm/s
#define INTERP_TEACH_MAXGVEL      10     // �ѿ���ʾ�������̬�ٶ�, deg/s
#define INTERP_ZONE_GRADE          4     // ���ɶ����ȼ�
#define INTERP_ZONE_ACCPCT       1.0     // ���ɶμ��ٶȰٷֱ�, 100%
#define INTERP_SINGULARITY_ZONE  5.0     // ���������С, deg
#define JOINT_CART_TRANSF_EN	   1	 // �ؽ���ѿ������ɿ���
// ]] 

// [[ ϵͳ����
#define MOF           8          // �����������ɶ�+ת̨���ɶ�

extern int DOF;  //����������+ת̨���ɶ�

//#if PROGRAM_VERSION==RELEASE_MODE||PROGRAM_VERSION==OFFLINE_TEST_MODE
#define INTERP_T	   0.004     // �岹����,s
#define POS_T          0.001     // λ������,s
//#else
//#define INTERP_T       0.016     // (test)�岹����,s
//#define POS_T          0.004     // (test)λ������,s
//#endif
#define RT_LITTLE    0.000001    // ϵͳ��ʶ�����С����
#define SERR          0.00001    // �������Χ
#define POS_SERR      0.00036    // �ؽ�λ���������Χ, 1cts - 0.00036(���ٱ�100)
#define POS_PRECISION       1    // ��λ�þ���, �ŷ����
#ifndef PI
#define PI      3.1415926535898  // Բ����
#endif
#define PI2     6.2831853071796  // 2��Բ����  
#define PI_RAD  0.0174532925199  // �Ƕ�ת��Ϊ���Ȳ���
#define PI_DEG 57.2957795130823  // ����ת��Ϊ�ǶȲ���
// ]]
#ifndef ERR_STOP_T
#define ERR_STOP_T      0.5//  1.000 //��s
#endif

// [[ �˶�״̬
#define RUN_MODE_TEACH     1     // ʾ��ģʽ
#define RUN_MODE_AUTO      2     // ����ģʽ
#define RUN_MODE_6DFORCE      3     // 6ά���������϶� ģʽ
#define RUN_MODE_ERR       0     // ����ģʽ
#define RUN_DIR_POS        1     // ������
#define RUN_DIR_STOP       0     // �޷���
#define RUN_DIR_NEG       -1     // ������
#define RUN_STATE_RUNNING  1     // �����˶�
#define RUN_STATE_STOP     0     // ֹͣ
#define RUN_STOPMODE_HOLD  0     // ��ͣ
#define RUN_STOPMODE_STOP  1     // ֹͣ
#define RUN_LIM_POS        1     // ������
#define RUN_LIM_NOT        0     // �޼���
#define RUN_LIM_NEG       -1     // ������
#define RUN_SIN_YES        1     // ����״̬
#define RUN_SIN_NO         0     // ������

#define TEACH_STOP 1
#define TEACH_RUN  2
// ]]

// [[ ����ϵ
// [[ ʾ������ϵ - �ٶ�ģʽ/λ��ģʽ
#define COORDINATE_JOINT_VEL   1    // �ؽ�����ϵ
#define COORDINATE_WORLD_VEL   2    // ��������ϵ
#define COORDINATE_TOOL_VEL    3    // ��������ϵ
#define COORDINATE_USER_VEL    4    // �û�����ϵ

	#define COORDINATE_TABLE_VEL   5    // ת̨����ϵ
#define COORDINATE_JOINT_POS  11    // �ؽ�����ϵ
#define COORDINATE_WORLD_POS  12    // ��������ϵ
#define COORDINATE_TOOL_POS   13    // ��������ϵ
#define COORDINATE_USER_POS   14    // �û�����ϵ
	#define COORDINATE_TABLE_POS  15    // ת̨����ϵ
// ]]

// [[ ��״̬
#define MOTOR_ENABLE       1     // ʹ��
#define MOTOR_DISABLE      0     // ��ʹ��
// ]]


// [[ �������
#define PROG_MODE_MOVE         1     // Move
#define PROG_MODE_IO           2     // IO
#define PROG_MODE_DELAY        3     // Delay
#define PROG_MODE_NOTHING      4     // �ǳ�����
#define PROG_MODE_WAIT      5    // Wait
#define PROG_MODE_WELD      10    // ����
#define PROG_MODE_PULSE    12
#define PROG_IOMODE_Ds   8
#define PROG_IOMODE_De   9

#define PROG_order_ARCON    1  
#define PROG_order_ARCOFF    2 
#define PROG_order_ARCCT    3 
#define PROG_order_ARCSET    4 
#define PROG_order_AWELD    5 
#define PROG_order_VWELD    6 
#define PROG_order_ARCSETAVP    11 
#define PROG_order_ARCSETACC    12
#define PROG_order_ARCSETVEL    13


#define PROG_DsorDe_DisDs      1    // ����
#define PROG_DsorDe_DisDe      2    // ����
#define PROG_DsorDe_DisDsSlow      3    // ����
#define PROG_DsorDe_DisDeSlow      4   // ����
#define PROG_DsorDe_TimeDs      8   // ����
#define PROG_DsorDe_TimeDe      9    // ����
#define PROG_DsorDe_TimeDsSlow     10    // ����
#define PROG_DsorDe_TimeDeSlow      11   // ����

#define PROG_INTERP_JOINT      1     // �ؽڲ岹
#define PROG_INTERP_LINEAR     2     // ֱ�߲岹
#define PROG_INTERP_ARC        3     // Բ���岹
#define PROG_INTERP_CIRCLE     4     // ��Բ�岹
#define PROG_INTERP_PARABOLA   5     // �����߲岹 
#define PROG_INTERP_QUINTIC    6     // ��ζ���ʽ�岹

#define PROG_VELMODE_EULER     1  // ŷ�����ٶ�ģʽ
#define PROG_VELMODE_ANGLE     2  // ���ٶ�ģʽ

#define PROG_MARK_MIDLINE      0     // �м���
#define PROG_MARK_FIRSTLINE    0     // ����
#define PROG_MARK_LASTLINE     3     // ĩ��
#define PROG_MARK_SINGLELINE   1     // ����
#define PROG_MARK_CONTINUE	   2     // ����
#define PROG_COMM_CANREAD      2     // ����ɶ�
#define PROG_COMM_READOVER     3     // ���������
#define PROG_RUN_NOTSTART      0     // δ����
#define PROG_RUN_ON            1     // ��������
#define PROG_RUN_OVER          2     // �˶�����
#define PROG_RUN_STOP          3     // �˶�ֹͣ
#define PROG_RUN_ERROR        -1     // �˶�����

#define PROG_PLAN_NODATA       1     // ������
#define PROG_PLAN_WAITING      2     // �ȴ�
#define PROG_PLAN_PROCESSING   3     // �������ڹ滮
#define PROG_PLAN_COMPLETED    4     // ����滮���

#define PROG_TRANSMODE_YES     1     // ���ɶ�
#define PROG_TRANSMODE_NO      0     // �ǹ��ɶ�
// ]]

// [[״̬�����궨��
#define STATE_COMPLETED			 0		// ���봦�����
#define STATE_BLOCKCOMPLETED	 1		// ���������
#define STATE_FILECOMPLETED		 2		// �����ļ����
#define STATE_PROCESSING		 3		// �������ڴ���
#define STATE_WAITING			 4		// �ȴ����ش����ļ�
#define STATE_FEEDHOLD			 5		// ��ͣ
#define STATE_RESET			     8		// ��λ
#define STATE_WARNING            9      // ����
#define STATE_NOHOME            10      // �ǻ���
#define STATE_DECPROCESS		11      // 
// ]]


// IO���
#define AOUT_VOLT_MAX			10
#define AIN_VOLT_MAX			10
#define ANALOG_PREC				4096	// 10λ����


#define NMI  0
#define TIMER1  1
#define TIMER2  2
#define IDLE  3
#define ON   1
#define OFF  0

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

#define SYSTEM_OK    0   // ϵͳ����
#define SYSTEM_ERR  -1   // ϵͳ����

#ifndef SYSTEM_TRUE
#define SYSTEM_TRUE  1
#endif
#ifndef SYSTEM_FALSE
#define SYSTEM_FALSE 0
#endif
#define Square(n)   ((n) * (n))              // ƽ��
#define Cube(n)     ((n) * (n) * (n))        // ����

#ifndef Max
#define Max(a,b)    (((a) > (b)) ? (a) : (b))
#endif
#define Max3(a,b,c) Max(Max(a,b), (c))
#ifndef Min
#define Min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

// DSP��ʱ������λ-POS_T�岹����
typedef struct _dsp_Timer
{
	U16 Count[4];
	/*U16 NmiCount;
	U16 Timer1Count;
	U16 Timer2Count;
	U16 IdleCount;*/
	
}DSP_Timer;

#ifndef CARTESIANPOSE
#define CARTESIANPOSE
// ������λ�˱�ʾ���ѿ�������ϵ��ʾ
typedef struct _cartesianPose
{
	double X;     // λ��X,mm
	double Y;     // λ��Y,mm
	double Z;     // λ��Z,mm
	double W;     // ��̬W,deg
	double P;     // ��̬P,deg
	double R;     // ��̬R,deg
}CartesianPose;
#endif

#ifndef JOINTPOSE
#define JOINTPOSE
// �����˹ؽڽǶȱ�ʾ���ؽ�����ϵ��ʾ
typedef struct _jointPose
{
	double S;      // ��Sת��,deg
	double L;      // ��Lת��,deg
	double U;      // ��Uת��,deg
	double R;      // ��Rת��,deg
	double B;      // ��Bת��,deg
	double T;      // ��Tת��,deg
}JointPose;
#endif

#ifndef LINKDIMENSION
#define LINKDIMENSION
// ���������˲����ṹ
typedef struct _linkDimension
{
	double A1;           // a1,mm
	double A2;           // a2,mm
	double A3;           // a3,mm
	double D3;           // d3,mm
	double D4;           // d4,mm
	double Df;           // df,mm
	
}LinkDimension;
#endif

#ifndef PROGRAMINFORMSTRUCT
#define PROGRAMINFORMSTRUCT
// ����״̬
typedef struct _programInformStruct
{
	int Prog_State; // 1. �˶�����ǰ�����˶�״̬, 0������, 1��������, 2�˶���, ����-�˶�����
	                // 2. �滮��0����, ����-�滮�����кźͶκ�ֻ�ڹ滮����ʱ��Ч
	int CurrLine_State;	//��ǰ��״̬, 0 ������, 1 ��������, 2 �˶�����, ����-�˶�����
    // ������
    // ��ʾ�õ�
    char name[20];
	
    // ����Ĳ����
    // ʵʱͬ���õ�
    unsigned int decode_id ;
	int Prog_SequNum;// ������κ�
	int Prog_LineNum;// ���������к�
	int IfTransSeg;  // �Ƿ��ǹ��ɶ�
}ProgramInformStruct;
#endif


#ifndef TABLECONFIGT
#define TABLECONFIGT
//ת̨����
typedef struct _TableConfigT
{
	CartesianPose Pos1;  //��1������ϵ
	CartesianPose Pos2;  //��2������ϵ
}TableConfigT;
#endif

typedef struct _globalState
{
/////////////////////////////////////////////////////////////////////// ��������
	int Acc_Time;              // ����ʱ��, ms

// [[ �ѿ���
	double Car_MaxPVel;          // �ѿ���λ������ٶ�, mm/s
	double Car_MaxGVel;          // �ѿ�����̬����ٶ�, deg/s
	double Car_MaxPAcc;          // �ѿ���λ�ü��ٶ�
	double Car_MaxGAcc;          // �ѿ�����̬���ٶ�
	double Car_StopPDec;         // �ѿ���λ��ֹͣ���ٶ�
	double Car_StopGDec;         // �ѿ�����ֹ̬ͣ���ٶ�
	LinkDimension Robot_Link;    // ���������˲���
	CartesianPose Robot_Tool;    // ��������ϵ����
	CartesianPose Robot_User;    // �û�����ϵ����
// ]] �ѿ���

// [[ �ؽڿռ�
	double Joint_MaxVel[MOF];    // �ؽ�����ٶ�����, deg/s*s
	double Joint_StopDec[MOF];   // �ؽ�ֹͣ���ٶ�, deg/s*s
	double Joint_PLim[MOF];      // �ؽ�������, deg
	double Joint_NLim[MOF];      // �ؽڸ�����, deg
	double Joint_MaxAcc[MOF];    // �ؽ������ٶ�, deg/s*s
// ]] �ؽڿռ�

// [[ ��ռ�
	double Motor_Ratio[MOF];     // ����ٱ�
	double Motor_AbsZero[MOF];   // ��������, ���ת��
	int Motor_Precision[MOF];    // �ᾫ��, cts/round
	int Motor_Dir[MOF];          // �᷽��, "1"-���������ؽڷ���һ��, "-1"-��һ��
// ]] ��ռ�

/////////////////////////////////////////////////////////////////////// ��������
	CartesianPose Car_ActPos; // ������ʵ��λ��
	double Joint_ActPos[MOF]; // �ؽ�ʵ��λ��
	double Joint_ActVel[MOF]; // �ؽ�ʵ���ٶ�
	double Motor_ActCurr[MOF];// ��ʵ�ʵ���
	double Motor_ActPos[MOF]; // ��ʵ��ת��
	double Joint_CurrentPos[MOF]; // ·���滮�ĵ�ǰλ��
	double Joint_CalculPos[MOF];
	double Car_ActVel[MOF];   // �ѿ���ʵ���ٶ�
	
	double Car_CmdPos[MOF];// ������ʵ��λ��
	double Car_CmdVel[MOF]; // �ѿ���ʵ���ٶ�
	double Joint_CmdPos[MOF];//��ǰ�ؽ�ָ��λ��
       double Joint_CmdVel[MOF];//��ǰ�ؽ�ָ���ٶ�

    short Joint_Dir[MOF];     // �ؽ��˶�����  :��ʾ�����
	short Flag_PLim[MOF];     // �ؽ�λ�ü��ޱ�־, ������(1)/�Ǽ���(0)/������(-1)
    short Joint_State[MOF];   // �ؽ��˶�״̬  :��ʾ�����
    short Flag_Enable[MOF];   // ʹ�ܱ�־  :��ʾ�����
    short Flag_VLim[MOF];     // �ؽ��ٶȼ��ޱ�־  :��ʾ�����

	double Table_MaxVel;  //ת̨�����ϳ���ת�ٶ�,  deg/s
	double Table_MaxAcc;  //ת̨�����ϳ������ٶ�,  deg/s.s
    double Table_StopDec;
	TableConfigT Table_ConfigT;   //ת̨����
	int Table_Gt;

/////////////////////////////////////////////////////////////////////// ȫ��״̬
// [[ ����
	U16 Mode;           // ʾ��(1)/����(2) - // ARM����ֵ��1 �� 2
	U16 Stop;           // ֹͣ(1)         - // ARM����ֵ��1
	U16 Hold;           // ��ͣ(1)/����(0) - // ARM����ֵ��1 �� 0
	U16 AlarmClear;          // ��λ(1)         - // ARM����ֵ��1
	U16 EStop;          // ��ͣ(1)         - // ARM����ֵ��1
	U16 Abort;          // ȡ���˶�(1)     - // ARM����ֵ��1
	U16 MachineStop;    // ����(1)/���(0) - // ARM����ֵ��1 �� 0
	U16 Pct_AutoVel;    // �����˶��ٶȰٷֱ�, �����˶�����������
// ]] ����

// [[ ��ǰ״̬
	U16 MotionMode;     // ��ǰ�˶�ģʽ - ʾ��(1)/����(2)/����(0)
	U16 JogCoordinate;  // �ֶ�����ϵѡ�� - �ؽ�(1)/��(2)/����(3)/�û�(4)
	U16 In_Motion;      // �����˶���־(1)
	U16 Singularity;    // ����λ��(1)
	U16 MotorEnable;    // ��ʹ��(1)
// ]] ��ǰ״̬
	/* DSPState[0]-ֹͣ״̬��DSPState[1]-��ͣ״̬, DSPState[2]-����״̬*/
	char DSPState[4];
// [[ ����״̬
	ProgramInformStruct Prog_Run;  // ����ǰ�˶�״̬, �ڲ岹ʱ����
	ProgramInformStruct Prog_Plan; // ����ǰ״̬, �ڹ滮����ʱ����
// ]] ����״̬

// [[ ������Ϣ
	AlarmInformStruct Err;    // ������Ϣ, �ڳ���ִ�й����и���
}GlobalState;

typedef struct STRC_DelayCtrl
{
	int Req;	//������ʱ��־
	int DlyTime;//��ʱʱ��

}UD_DelayCtrl;

//IO�����ڲ�����
typedef struct STRC_DSPStateLightParam
{
	unsigned int TotleTimes;
	unsigned int BlinkTimes;
	unsigned int CurrTimes;
	unsigned int IsBlinkSrart;
}UD_DSPStateLightParam;

//���ӿ��ƽṹ
typedef struct STRC_WeldControl
{

       int WaitTime;         // �ȴ�ʱ��, ms//256
	// Mode == 10 ����
	// 1 ARCON
	// 2 ARCOF
	// 3 ARCCT 
	// 4 ARCSET
	// 5 AWELD
	// 6 VWELD
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
   /* int WaitTime;         // �ȴ�ʱ��, ms
    int SonMode;         //������ģʽ
    int DsorDe;           //0-��Ч 1-Ds(Distance)   2-De(Distance)  3-����4-Ds(Time) 5-De(Time) 6
    float Distance;     //����mm
    float Av;              //��ѹV
    float Acc;            //����A
    unsigned int IfOutPut; //�Ƿ����  0-�����   1-���*/
    float  CurrentAvp;
    float  CurrentAcc;
   // float  Vel;
    U32 IO_Mode;          // 1-���� | 2-���
    U32 IO_Name;          // IO���
    U32 IO_Value;         // IOֵ, 1-true | 0-false
}WeldControl;

typedef struct
{
    int Fx;
    int Fy;
    int Fz;
    int Mx;
    int My;
    int Mz;
    int Status_Code;
    int Sample_Count;
    int Stop;
    double Acc;
    double Ratio;
} From_Sensor_t;


extern GlobalState gs_State;  // ȫ��״̬
extern DSP_Timer gs_timer;    // DSP��ʱ��

#ifdef __cplusplus
}
#endif
#endif

