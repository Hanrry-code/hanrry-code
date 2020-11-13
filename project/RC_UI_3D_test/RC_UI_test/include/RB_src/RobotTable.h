#ifndef _ROBOTTABLE_H
#define _ROBOTTABLE_H


#ifdef __cplusplus
extern "C"{
#endif
#include <math.h>
#include <string.h>
#include "Communicate.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef Boolean
	typedef unsigned short Boolean;
#endif

#define ANG2RAD  0.017453292519943295769236907684886  //=PIE/180
#define RAD2ANG  57.295779513082320876798154814105  //=180/PIE

typedef double TMatrix[4][4];

#define ANGL_NUM 2
#define LINE_NUM 3

Boolean UpdateTableConfig(TableConfigT *table_config);
Boolean Tabl2MachT(int gt ,CartesianPose *pos, double angl[ANGL_NUM] ,CartesianPose *vmach);
Boolean Tabl4MachT(int gt ,CartesianPose *pos, double angl[ANGL_NUM] ,CartesianPose *vmach);
#ifdef __cplusplus
}
#endif

#endif
