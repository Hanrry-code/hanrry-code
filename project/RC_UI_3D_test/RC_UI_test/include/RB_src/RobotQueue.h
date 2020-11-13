#ifndef __ROBOTQUEUE_H__
#define __ROBOTQUEUE_H__
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        ѭ�����ж���                                                       *
 *****************************************************************************/
#include "Communicate.h"
#ifndef U16
#define U16 unsigned short int
#endif

#ifndef U32
#define U32 unsigned int
#endif

typedef struct _elemType
{	
	char name[20];	//������
	U32 decode_id;	//����ID
	U32	Mode;	//�˶���-1 | IO-2 | Delay-3 | �ǳ�����-4(�ȴ�)
	U32 Prog_SequNum;// ��������κ�
	U32 Prog_LineNum;// ���������к�
	U32 Prog_Mark;	 // �б�־λ
	U32 IfTransSeg;  // �Ƿ��ǹ��ɶ�
	U32	IfLastPoint; // �Ƿ����һ�㣬0 �����㣬1 �����㣬2 �����һ��
	int Error;         // �����״̬

	double Posval[MOF]; // ����λ��+ת̨2��λ��
	double Spdval[MOF]; // �����ٶ�+ת̨2��λ��

	U32 IO_Mode;          // 1-���� | 2-���
	U32 IO_Name;          // IO���
	U32 IO_Value;         // IOֵ, 1-true | 0-false
	
	U32 WaitTime;         // �ȴ�ʱ��, ms

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
	float Percent;
	int IfDout;       //�Ƿ������ѹ����
	int IfAout;
	//add for return to arm
	double time;
	double totaltime;
	double len;
	double totallen;
}ElemType;

typedef struct _queue
{
	ElemType *Queue;   // ָ��洢���е�����ռ�
	volatile U16 Front;// ����ָ�루�±꣩,����ָ�벻ָ��Ԫ��
	volatile U16 Rear; // ��βָ�루�±꣩
    U16 MaxSize;       // Queue����
}Queue;


//--------------------------------- ���� ------------------------------------/
int InitQueue(Queue *q, U16 size);   // ��ʼ������
int EnQueue(Queue *q, ElemType e);   // ����Ԫ��
int DeQueue(Queue *q, ElemType *e);  // ɾ��Ԫ�ز�����
int PeekQueue(Queue *q, ElemType *e);// ��ȡ����Ԫ��
int EmptyQueue(Queue *q);            // ����Ƿ�Ϊ��
int QueueLen(Queue *q);              // ����Ԫ�ظ���
int FullQueue(Queue *q);             // ����Ƿ�Ϊ��
void ClearQueue(Queue *q);           // ������� 
void ResetQueue(Queue *q);           // Reset����
#ifdef __cplusplus
}
#endif
#endif

