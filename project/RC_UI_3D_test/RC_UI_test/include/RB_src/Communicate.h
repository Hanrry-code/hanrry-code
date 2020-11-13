#ifndef __COMMUNICATE_H__
#define __COMMUNICATE_H__


#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        ����λ��ͨѶ                                                          *
 *****************************************************************************/
/////////////////////////////���ݽṹ����////////////////////////////////

#ifndef U16
#define U16 unsigned short
#endif

#ifndef U32
#define U32 unsigned int
#endif

// [[ ϵͳ����
#define MOF           8          // �����������ɶ�+ת̨���ɶ�

extern int DOF;  //����������+ת̨���ɶ�

#ifndef _CPSTRITIO_
#define _CPSTRITIO_
typedef struct _CPSTRITIO
{
    double CPSTRITIO_56;      // 56�Ჹ������
    double CPSTRITIO_45;      // 45�Ჹ������
    double CPSTRITIO_46;      // 46�Ჹ������
}CPSTRITIO;
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

#ifndef TABLEPOSE
#define TABLEPOSE
// ת̨�Ƕȱ�ʾ��ת̨����ϵ
typedef struct _tablePose
{
	double A1;     //��1��ת��,deg
	double A2;     //��2��ת��,deg
}TablePose;
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

//�������ṹ��
#ifndef INTFZONE
#define INTFZONE
typedef struct _IntfZone
{
	U16 ZoneID;			//�������ţ�0��5
	U16 Availablty;		//�Ƿ���Ч��־��1����Ч��0����Ч
	int RefCoord;		//�ο�����ϵ��-1 ��������ϵ������ �� �û�����ϵ��
	float PointMin[3];	//��һ��
	float PointMax[3];	//�ڶ���
}IntfZone;
#endif

//�û�����ϵ�ṹ��
#ifndef USERFRAME
#define USERFRAME
typedef struct _UserFrame
{
	U16 UserID;			//�û�����ϵ�ţ�0��9
	U16 Unused1;
	U32 Unused2;
	CartesianPose User;	//�û�����ϵ����
}UserFrame;
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

#ifndef INPUTAUTODATA
#define INPUTAUTODATA
// ϵͳ�����������ݽṹ
typedef struct _inputAutoData
{
    // ������
    // ��ʾ�õ�
    char name[20];//0

    // ����Ĳ����
    // ʵʱͬ���õ�
    unsigned int decode_id ;//20

    // [[ �λ�����Ϣ
    int Prog_SequNum;     // ��ǰ����α��	//24
    int Prog_LineNum;     // ��ǰ�����б��     //28
    int Prog_Mark;        // �����ʶ 0:�����һ��  1:���л����һ��//32
    // ]]

    int Mode;             // ������ģʽ, �˶���-1 | IO-2 | Delay-3 | �ǳ�����-4 |Wait-5|����-10  //36

    // [[ �˶�����Ϣ
    int Interp_Mode;      // �岹��ʽ - MOVJ 1 | MOVL 2 | Բ�� 3 | ��Բ 4   //40

    int Joint_VelPct;     // �ؽڲ岹�ٶȰٷֱ�   //44
	int PathSN;			  // Բ��ʱָ���ǵ�һ�λ��ǵڶ��Σ�0--���Σ�1--��һ�Σ�2--�ڶ���//48
	int PathSN2;			  //52
	double JPos_Start[MOF]; // ��ʼ��, Բ���岹ʱ�ã���ȷ��ֵ��  //�ռ�仯
    double JPos_Mid[MOF];   // �м��, Բ��/�����߲岹ʱ��  //�ռ�仯
    double JPos_End[MOF];   // Ŀ���  //�ռ�仯
    double Car_PVel;      // �ѿ����岹λ���ٶ�, 0-Ĭ��//200
    double Car_GVel; 	  //208
    int Zone;             // ���ɵȼ�, 0,1,2,3,4   //216

    int Move_IfHaveIn;    // �Ƿ�������ָ��//220
    int Move_InName;      // ������//224
    int Move_WaitInT;     // �ȴ������ʱ��//228

    int Move_IfHaveOut;   // �Ƿ������ָ��//232
    int Move_OutName;     // ������         //236
    int Move_OutTrigger;  // ���������ʽ//240
    // ]]

    // [[ IO����Ϣ
    int IO_Mode;          // 1-���� | 2-��� 3-ģ������ 4-ģ�����//244
    int IO_Name;          // IO���//248
    int IO_Value;         // IOֵ, 1-true | 0-false//252
    // ]]
    int WaitTime;         // �ȴ�ʱ��, ms//256
	// Mode == 10 ����
	// 1 ARCON
	// 2 ARCOF
	// 3 ARCCT 
	// 4 ARCSET
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
	int  acc_time;//ms
    /*// Mode == 10 ����
	// 1 ARCON
	// 2 ARCOF
	// 3 ARCCT 
	// 4 ARCSET
	// 5 AWELD
	// 6 VWELD
	int SonMode;//order ;//260
	// ����
	float Acc;//AC ;//264
	// ��ѹ
	float Av;//AVP ;//268
	// ʱ��
	float T ;//272   ms
	// �ٶ�
	float V ;//276
	// 1 ds
	// 2 es
	int  DsorDe;//if(
	float Distance;//dis;//284
	//288�ֽ�*/
    /*int SonMode;         //������ģʽ
    int DsorDe;           //0-��Ч 1-Ds   2-De
    float Distance;     //����mm
    float Av;              //��ѹV
    float Acc;            //����A*/

}InputAutoData;
#endif

#ifndef INPUTTEACHDATA
#define INPUTTEACHDATA
// ����ʾ�����ݽṹ����
typedef struct _inputTeachData
{
    int Stop; 	// ʾ��״̬ stop-1 run - 2
    int Coor; 	// �ٶȷ�ʽ���ؽ�--1��ֱ��--2������--3������--4��������ʽ���ؽ�--11��ֱ��--12������--13������--14
    int Aix;  	// ��1-6
    int Vel;  	// �ٶȰٷֱ�
    int Dir;  	// ���� -1/1 
    int Acc;  	// ���ٶ�
	double Pos;	// ����ʾ����λ�Ƴ��ȣ��Ƕ�����λ��deg��ƽ������λ��mm
}InputTeachData;
#endif

#ifndef JOINTINTPARA
#define JOINTINTPARA
typedef struct _jointIntPara
{
    short int S;
    short int L;
    short int U;
    short int R;
    short int B;
    short int T;
}JointIntPara;
#endif

#ifndef ALARMINFORMSTRUCT
#define ALARMINFORMSTRUCT
typedef struct _alarmInformStruct
{
    int Err_Comm; // ͨѶ������
    int Err_Plan; // �滮����
    int Err_Run;  // ���д���
    int Err_Lim;  // ����
    int Alm_Ser;  // �ŷ�����
    int OTC_CIA;  // ������
}AlarmInformStruct;
#endif

typedef struct _alarmQueue
{
    int Err_Num;                         //  ?�̨�3����?����y
    int Err_Number[10];  // ?�̨�3����?��o?
}AlarmQueue;

#ifndef PROGRAMINFORMSTRUCT
#define PROGRAMINFORMSTRUCT
// ����״̬
typedef struct _programInformStruct
{
	int Prog_State; // 1. �˶�����ǰ�����˶�״̬, 0������, 1��������, 2�˶�����, ����-�˶�����
	                // 2. �滮��0����, ����-�滮�����кźͶκ�ֻ�ڹ滮����ʱ��Ч
	int CurrLine_State;	//��ǰ��״̬, 0 ������, 1 ��������, 2 �˶�����, ����-�˶�����
    // ������
    // ��ʾ�õ�
    char name[20];
	
    // ����Ĳ����
    // ʵʱͬ���õ�
    unsigned int decode_id ;
	int Prog_SequNum;// ��������κ�
	int Prog_LineNum;// ���������к�
	int IfTransSeg;  // �Ƿ��ǹ��ɶ�
}ProgramInformStruct;

#endif

#ifndef PROGRAMRUNSTRUCT
#define PROGRAMRUNSTRUCT
// ����״̬
typedef struct _programRunInformStruct
{
   	 // ʵʱͬ���õ�
	double time;      //�ù켣������ʱ��
	double totaltime;//�ù켣������ʱ��
	double len; //�ù켣�����г���
	double totallen;//�ù켣�����ܳ���
	
}ProgramRunInformStruct;

#endif

typedef struct  _SYSTEMSTATUS
{
	U16 pEStop;        
	U16 pMode;       
    U16 intCanUse; 
    U16 intMode; 
	U16 pStop;       
    U16 pReset; 
	U16 pEnable;   
    U16 pAbort;
	U16 pPctAutoVel;
    U16 pHold;
	U32 DSPStateLight;
}SYSTEMSTATUS;

#ifndef IOCARDCTRL
#define IOCARDCTRL
typedef struct _IoCardCtrl
{
	U32 DigitalSignal[2];			 
	U32 AnalogSignal[2];         
	U16 CardADC[4];
}IoCardCtrl;
#endif

#ifndef IOARMCTRL
#define IOARMCTRL
typedef struct _IoArmCtrl
{
	U32 DigitalSignal[2];	//64λIO		       
	U16 Control;//����λ��1-ARM IOָ����Ч 2-DSP��ȡ����Ϊ2
}IoArmCtrl;
#endif

/*
//#define COMM_BASIC  0xB0004000
extern int COMM_BASIC;

extern U16* m_pDSPVersion;		//�汾�ţ���12��Ԫ��

extern U16* m_pUserFrameControl;	//����λ��0 �� ������1 �� ��������û�����ϵ
extern UserFrame* m_pUserFrame;//��������ϵ

extern U16* m_pIntfZoneControl;	//����λ��0 �� ��������ʼ������DSP���������ݺ���0����1 �� ������¸�����
extern IntfZone* m_pIntfZone;//������

extern U16* m_pIntfZoneEnter;//�Ƿ�����������־��0 bit��5 bit��0��δ���룬1���ѽ���
//extern U32* m_pDSPStateLight;
extern U16* m_pCPSTRITIOControl;    //�������ʶ�д����  1-DSP�ɶ� 0-DSP����� 
extern CPSTRITIO *m_pCPSTRITIO;//����double

extern U32 DSPStateLight;
extern volatile U16* m_pMode;       // �˶�ģʽ - ʾ��(1)/����(2)
extern volatile U16* m_pStop;       // ֹͣ(1)
extern volatile U16* m_pAlarmClear;      // ��λ(1)
extern volatile U16* m_pEnable;     // ʹ��(1) / ��ʹ��(0)
extern volatile U16* m_pReset;      // ȡ��(1)
extern volatile U16* m_pMachineLock;// ��е����(1)
extern volatile U16* m_pPctAutoVel; // �����ٶȰٷֱ�(20-100)
extern volatile U16* m_pHold;       // ��ͣ(1) / ����(0)
extern volatile U16* m_pDSPState;
extern volatile U16* m_pInitOk;
extern volatile U16* m_pEStop;	//��ͣ�ź�
extern volatile U16* m_pEnableKey; 
/////////////////////////////////////////////// ���ò��� (ARM-DSP) 0x0200-0x0520
extern U16* m_pAbsZeroControl;     // ���þ���������λ, 1-�ؽ�, 2-��
extern JointPose* m_pJointAbsZero; // �ؽھ������

// [[ �ؽڿռ�
extern U16* m_pJointControl;      // �ؽڲ�������λ
extern JointPose* m_pJointMaxAcc;// �ؽ������ٶ�
extern JointPose* m_pJointMaxVel; // �ؽ�����ٶ�
extern JointPose* m_pJointStopDec;// �ؽ�ֹͣ���ٶ�, deg/s*s
extern JointPose* m_pJointPLim;   // �ؽ�������, deg
extern JointPose* m_pJointNLim;   // �ؽڸ�����, deg
// ]]

// [[ ��ռ� ,�������
extern U16* m_pMotorControl;      // ���������λ
extern JointPose* m_pMotorRatio;  // ����ٱ�
extern JointPose* m_pMotorAbsZero;// ��������, ���ת��
extern int* m_pMotorPrec;         // �ᾫ��, cts/round
extern U16* m_pMotorDir;          // �᷽��, ��λ����, ��ؽڷ���һ��ʱΪ1, ��һ��Ϊ0
// ]]

extern int* m_pAccTime;  // ����ʱ��, ms

// [[ �ѿ����ռ�
extern U16* m_pCarControl;     // �ѿ�����������λ
extern double* m_pCarMaxPVel;  // �ѿ���λ������ٶ�, mm/s
extern double* m_pCarMaxGVel;  // �ѿ����̬����ٶ? deg/s
extern double* m_pCarMaxPAcc;  // �ѿ���λ�ü��ٶ�
extern double* m_pCarMaxGAcc;  // �ѿ�����̬���ٶ�
extern double* m_pCarStopPDec; // �ѿ���λ��ֹͣ���ٶ�
extern double* m_pCarStopGDec; // �ѿ�����ֹ̬ͣ���ٶ�
//]]

// [[ ������
extern U16* m_pRobotControl;        // �ѿ�����������λ
extern LinkDimension* m_pRobotLink; // ���������˲���
extern CartesianPose* m_pRobotTool; // ��������ϵ����
extern CartesianPose* m_pRobotUser; // �û�����ϵ����
// ]]


/////////////////////////////////////////////// ʾ������ (ARM-DSP) 0x0520-0x0560
extern U16* m_pTeachControl;         // ʾ�̿���
extern InputTeachData* m_pTeachData; // ʾ������


/////////////////////////////////////////////// �������� (ARM-DSP) 0x0560-0x0d00
//����100K�Ŀռ�����뻺���� 100k=0x19000  412k=421888=0x67000
extern U32* m_pAutoControl;         // ���ֿ���
extern InputAutoData* m_pAutoData;  // ��������


/////////////////////////////////////////////// �������� (DSP-ARM) 0x0d00-0x0e00
extern CartesianPose* m_pCarActPos; // ������ʵ��λ��
extern JointPose* m_pJointActPos;   // �ؽ�ʵ��λ��
extern JointPose* m_pJointActVel;   // �ؽ�ʵ���ٶ�
extern JointPose* m_pJointActCurr;  // ��ʵ�ʵ���
extern JointPose* m_pMotorActPos;   // ��ʵ��ת��


extern JointIntPara* m_pJointDir;   // �ؽ��˶�����
extern JointIntPara* m_pJointState; // �ؽ��˶�״̬
extern JointIntPara* m_pFlagEnable; // ʹ�ܱ�־
extern JointIntPara* m_pFlagVLim;   // �ؽ��ٶȼ��ޱ�־
extern JointIntPara* m_pFlagPLim;   // �ؽ�λ�ü��ޱ�־, ������(1)/�Ǽ���(0)/������(-1)

extern AlarmQueue* m_pAlarmQueue; // ����״̬

extern ProgramInformStruct* m_pProgRunInform;  // �����˶�״̬
extern ProgramInformStruct* m_pProgPlanInform; // ����滮����״̬
extern ProgramRunInformStruct* m_pRunInform;
//extern U32*m_pIoIn;  // I/O���룬32λ
//extern U32*m_pIoOut; // I/O�����32λ

extern IoCardCtrl* m_IoInputCtrl;
extern IoArmCtrl* ARMClrIO;
extern IoArmCtrl* ARMSetIO;
extern IoCardCtrl* m_IoOutputCtrl;

extern float *Avp;
extern float *Acc;

extern int* PulseSendSum;
extern int* PulseSendNum;

extern SYSTEMSTATUS* SystemRunState;

extern short int* OverFlowCount;

extern short int*  TestRam;

/////////////////////////////////////////////// ���ò���

// [[ ת̨�ռ�
extern TablePose* m_pTableJointMaxAcc; // �ؽ����������ٶ�, deg/s*s
extern TablePose* m_pTableJointMaxVel; // ת̨����ٶ�
extern TablePose* m_pTableJointStopDec; // תֹ̨ͣ���ٶ�, deg/s*s
extern TablePose* m_pTableJointPLim; // ת̨������, deg
extern TablePose* m_pTableJointNLim; // ת̨������, deg
// ]]

// [[ ��ռ� ,�������
extern TablePose* m_pTableMotorRatio; // ����ٱ�
extern TablePose* m_pTableMotorAbsZero; // ��������, ���ת��
extern int* m_pTableMotorPrec1; // �ᾫ��, cts/round
extern int* m_pTableMotorPrec2; // �ᾫ��, cts/round
extern U32* m_pTableMotorDir; 

// [[ ת̨�ռ�
extern double* m_pTableMaxVel;  //ת̨�����ϳ���ת�ٶ�,  deg/s
extern double* m_pTableMaxAcc;  //ת̨�����ϳ������ٶ�,  deg/s.s
// ]]

//[[ ת̨����
extern TableConfigT* m_pTableConfigT;
extern int * m_pTableAxisNum;
//]]

/////////////////////////////////////////////// �������� 

extern TablePose* m_pTableJointActPos;   // �ؽ�ʵ��λ��  16�ֽ�
extern TablePose* m_pTableJointActVel;   // �ؽ�ʵ���ٶ�  16�ֽ�
extern TablePose* m_pTableJointActCurr;  // ��ʵ�ʵ���  16�ֽ�
extern TablePose* m_pTableMotorActPos;   // ��ʵ��ת��  16�ֽ�

extern short int* m_pTableJointDir1;   // �ؽ�1�˶�����  2�ֽ�
extern short int* m_pTableJointDir2;   // �ؽ�2�˶�����  2�ֽ�

extern short int* m_pTableJointState1;   // �ؽ�1�˶�״̬  2�ֽ�
extern short int* m_pTableJointState2;   // �ؽ�2�˶�״̬  2�ֽ�

extern short int* m_pTableFlagEnable1; // ʹ��1��־  2�ֽ�
extern short int* m_pTableFlagEnable2; // ʹ��2��־  2�ֽ�

extern short int* m_pTableFlagVLim1; // �ؽ�1�ٶȼ��ޱ�־  2�ֽ�
extern short int* m_pTableFlagVLim2; // �ؽ�2�ٶȼ��ޱ�־  2�ֽ�

extern short int*  m_pTableFlagPLim1;   // �ؽ�λ�ü��ޱ�־, ������(1)/�Ǽ���(0)/������(-1)  2�ֽ�
extern short int*  m_pTableFlagPLim2;   // �ؽ�λ�ü��ޱ�־, ������(1)/�Ǽ���(0)/������(-1)  2�ֽ�
*/

#ifdef __cplusplus
}
#endif

#endif
