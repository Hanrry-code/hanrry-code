#ifndef __ROBOTMatrix_H__
#define __ROBOTMatrix_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        ������                                                           *
 *****************************************************************************/

#ifndef PI
#define PI		  3.1415926535898	  // Բ����
#endif

#ifndef PI_RAD
#define PI_RAD    0.0174532925199     // �Ƕ�ת��Ϊ���Ȳ���
#endif

#ifndef PI_DEG
#define PI_DEG    57.2957795130823    // ����ת��Ϊ�ǶȲ���
#endif

#ifndef RT_LITTLE
#define RT_LITTLE 0.000001		  // ϵͳ��ʶ�����С����
#endif

#ifndef Boolean
#define Boolean unsigned short
#endif

#ifndef SYSTEM_TRUE
#define SYSTEM_TRUE  1
#endif
#ifndef SYSTEM_FALSE
#define SYSTEM_FALSE 0
#endif

// ����ṹ
typedef struct _matrix
{
	double* Mtx;    // ��̬���������������Ŀռ�
	int     Row;    // ���������
    int     Col;    // ���������
    int     N;      // ����Ԫ�ظ���
}Matrix;

// λ�˾���ṹ
typedef struct _poseMatrix
{
	double R11;
	double R12;
	double R13;
	double R21;
	double R22;
	double R23;
	double R31;
	double R32;
	double R33;
	
	double X;
	double Y;
	double Z;
}PoseMatrix;

// 6x6����ṹ
typedef struct _matrix_6x6
{
	double  Mtx[36];// ����Ŀռ�
	int     Row;    // ���������
    int     Col;    // ���������
    int     N;      // ����Ԫ�ظ���
}Matrix_6x6;
int InitMatrix_6x6(Matrix_6x6 *m); 
int InvMatrix_6x6(Matrix_6x6* m, Matrix_6x6* B);             // �������

//--------------------------------- ���� ------------------------------------/
int InitMatrix(Matrix *m,int row, int col);      // ��ʼ��Ϊrow��col�е������
int MultiMatrix(Matrix* A, Matrix* B, Matrix* AB);// �������
double DetMatrix(Matrix* m);                     // ���������ʽֵ
int InvMatrix(Matrix* m, Matrix* B);             // �������
void TrvMatrix(Matrix* A, Matrix* B);            // �����ת��
void ClearMatrix(Matrix* m);                     // �������

void Trans_PosToMtx(double* pos, PoseMatrix* output, int inv);  // λ��ת��Ϊλ�˾���
void Trans_MtxToPos(PoseMatrix* input, double* outpos);         // λ�˾���ת��Ϊλ��
void Mtx_Multiply(PoseMatrix* input, PoseMatrix* middle, PoseMatrix* output, int inv); // λ�˾������

#ifdef __cplusplus
}
#endif
#endif

