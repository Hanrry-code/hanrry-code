#ifndef _SERVOINFO_H
#define _SERVOINFO_H

#ifdef __cplusplus
extern "C"{
#endif

int LinkFillMotorData(int *OpenOutput,unsigned short *RealPos,int *ErrPos,short *DataAll);
int Get_GLink_MotorPos(unsigned short *RealPos);
int GetAlmStateFromServo(void);
int GetLinkStateFromServo(void);
int GskLinkInit(void);
void DSP_ClearMotorALM(int axis);




#ifdef __cplusplus
}
#endif

#endif