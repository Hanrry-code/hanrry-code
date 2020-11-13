#ifndef __ROBOTQUEUE_H__
#define __ROBOTQUEUE_H__
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *        循环队列定义                                                       *
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
	char name[20];	//程序名
	U32 decode_id;	//译码ID
	U32	Mode;	//运动行-1 | IO-2 | Delay-3 | 非程序行-4(等待)
	U32 Prog_SequNum;// 所属程序段号
	U32 Prog_LineNum;// 所属程序行号
	U32 Prog_Mark;	 // 行标志位
	U32 IfTransSeg;  // 是否是过渡段
	U32	IfLastPoint; // 是否最后一点，0 非最后点，1 行最后点，2 段最后一点
	int Error;         // 点错误状态

	double Posval[MOF]; // 六轴位置+转台2轴位置
	double Spdval[MOF]; // 六轴速度+转台2轴位置

	U32 IO_Mode;          // 1-输入 | 2-输出
	U32 IO_Name;          // IO编号
	U32 IO_Value;         // IO值, 1-true | 0-false
	
	U32 WaitTime;         // 等待时间, ms

	// Mode == 10 焊接
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
	// 电流
	float AC ;
	// 电压
	float AVP ;
	// 时间
	float T ;
	// 速度
	float V ;
	float Percent;
	int IfDout;       //是否输出电压电流
	int IfAout;
	//add for return to arm
	double time;
	double totaltime;
	double len;
	double totallen;
}ElemType;

typedef struct _queue
{
	ElemType *Queue;   // 指向存储队列的数组空间
	volatile U16 Front;// 队首指针（下标）,队首指针不指向元素
	volatile U16 Rear; // 队尾指针（下标）
    U16 MaxSize;       // Queue长度
}Queue;


//--------------------------------- 函数 ------------------------------------/
int InitQueue(Queue *q, U16 size);   // 初始化队列
int EnQueue(Queue *q, ElemType e);   // 插入元素
int DeQueue(Queue *q, ElemType *e);  // 删除元素并返回
int PeekQueue(Queue *q, ElemType *e);// 读取队首元素
int EmptyQueue(Queue *q);            // 检查是否为空
int QueueLen(Queue *q);              // 返回元素个数
int FullQueue(Queue *q);             // 检查是否为满
void ClearQueue(Queue *q);           // 清除队列 
void ResetQueue(Queue *q);           // Reset队列
#ifdef __cplusplus
}
#endif
#endif

