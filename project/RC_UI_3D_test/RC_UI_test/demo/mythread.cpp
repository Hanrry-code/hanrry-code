#include "mythread.h"
#include <qdebug.h>
#include <qstring.h>
Mythread::Mythread()
{
    isStop = true;
}

void Mythread::closeThread()
{
    isStop = false;
}

void Mythread::run()
{
    int i=0;
    while (isStop)
    {
        if(sd_size < SDSIZE-1)
        {
            //Task_MotionProcess();
            //Task_UpdateStatus();
            Run_InterpCore();
            for(i=0; i<6; i++)
            {
                sd_DataBuffer[sd_head][i]=gs_State.Joint_CmdPos[i];
            }
           // qDebug()<<gs_State.Joint_CmdPos[0]<<endl;
            sd_head=(sd_head+1)%SDSIZE;
            sd_size++;
        }
    }
}
