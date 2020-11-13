#ifndef __ROBOTMatrix_H__
#define __ROBOTMatrix_H__

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 *        矩阵定义                                                           *
 *****************************************************************************/

#ifndef PI
#define PI		  3.1415926535898	  // 圆周率
#endif

#ifndef PI_RAD
#define PI_RAD    0.0174532925199     // 角度转换为弧度参数
#endif

#ifndef PI_DEG
#define PI_DEG    57.2957795130823    // 弧度转换为角度参数
#endif

#ifndef RT_LITTLE
#define RT_LITTLE 0.000001		  // 系统可识别的最小正量
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

// 矩阵结构
typedef struct _matrix
{
	double* Mtx;    // 动态分配用来存放数组的空间
	int     Row;    // 矩阵的行数
    int     Col;    // 矩阵的列数
    int     N;      // 矩阵元素个数
}Matrix;

// 位姿矩阵结构
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

// 6x6矩阵结构
typedef struct _matrix_6x6
{
	double  Mtx[36];// 数组的空间
	int     Row;    // 矩阵的行数
    int     Col;    // 矩阵的列数
    int     N;      // 矩阵元素个数
}Matrix_6x6;
int InitMatrix_6x6(Matrix_6x6 *m); 
int InvMatrix_6x6(Matrix_6x6* m, Matrix_6x6* B);             // 矩阵的逆

//--------------------------------- 函数 ------------------------------------/
int InitMatrix(Matrix *m,int row, int col);      // 初始化为row行col列的零矩阵
int MultiMatrix(Matrix* A, Matrix* B, Matrix* AB);// 矩阵相乘
double DetMatrix(Matrix* m);                     // 矩阵的行列式值
int InvMatrix(Matrix* m, Matrix* B);             // 矩阵的逆
void TrvMatrix(Matrix* A, Matrix* B);            // 矩阵的转置
void ClearMatrix(Matrix* m);                     // 矩阵清除

void Trans_PosToMtx(double* pos, PoseMatrix* output, int inv);  // 位姿转换为位姿矩阵
void Trans_MtxToPos(PoseMatrix* input, double* outpos);         // 位姿矩阵转换为位姿
void Mtx_Multiply(PoseMatrix* input, PoseMatrix* middle, PoseMatrix* output, int inv); // 位姿矩阵相乘

#ifdef __cplusplus
}
#endif
#endif

