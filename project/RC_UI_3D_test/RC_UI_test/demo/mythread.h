#ifndef MYTHREAD_H
#define MYTHREAD_H

#define SDSIZE   40

#include <QThread>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "RB_src/RobotMotionControl.h"
#include "RB_src/RobotError.h"
#include "RB_src/RobotGlobalStruct.h"
#include "RB_src/Communicate.h"
#include "RB_src/DivFun.h"


class Mythread : public QThread
{
public:
    Mythread();
    void closeThread();
    bool add =false;
    double J[6] = {1,2,3,4,5,6};
    double axis[6] = {1.1f,2.3f,2.4f,2.5f,2.6f,6};
    double V[6] = {10.1f,2,5,76,3,89};

    int sd_head=0;
    int sd_tail=0;
    int sd_size=0;
    double sd_DataBuffer[SDSIZE][6]={};

protected:
    virtual void run();

private:
    volatile bool isStop;       //isStop是易失性变量，需要用volatile进行申明

};

#endif // MYTHREAD_H
