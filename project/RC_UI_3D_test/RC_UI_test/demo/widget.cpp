#include "widget.h"
#include "ui_widget.h"
#include <QActionGroup>
#include <QFileDialog>
#include <QTime>
#include "QDebug"

using namespace std;
using namespace Qwt3D;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init_Joint_CmdPos();
    init_Car_CmdPos();
    init_Joint_CmdVel();
    init_Car_CmdVel();

    connect(&timer,SIGNAL(timeout()),this,SLOT(Display()));

    isV = true;
    Init_Robot();
    init_qwt3D();
    init_qss();
    //    gs_State.MotionMode=2;//初始给定自动模式
    //    gs_State.Mode=2;
    //    gs_State.Pct_AutoVel = 100;
    //    *m_pEnable=1;
    //    *m_pAutoControl=2;

    //    gs_State.MotorEnable=1;
    //    gs_State.In_Motion=0;//
    /*
    gs_Struct.Robot_ToolIndexValue[0].X=-190;
    gs_Struct.Robot_ToolIndexValue[0].Y=1.19;
    gs_Struct.Robot_ToolIndexValue[0].Z=131.03;
    gs_Struct.Robot_ToolIndexValue[0].W=-31.13;
    gs_Struct.Robot_ToolIndexValue[0].P=-89.99;
    gs_Struct.Robot_ToolIndexValue[0].R=-149.01;
    gs_Struct.Robot_Tool=gs_Struct.Robot_ToolIndexValue[0];
    */

    new_thread = new Mythread();
    ui->radioButtonV->setChecked(true);
}

//void Widget::init_JBtn()
//{
//    JAddBtn[0] = ui->btn_J1add;
//    JAddBtn[1] = ui->btn_J2add;
//    JAddBtn[2] = ui->btn_J3add;
//    JAddBtn[3] = ui->btn_J4add;
//    JAddBtn[4] = ui->btn_J5add;
//    JAddBtn[5] = ui->btn_J6add;

//}



void Widget::Display()
{
    ++timer_number;
    //读取数据
    double jointData[6]={0,0,0,0,0,0};
    if(new_thread->sd_size > 0)
    {
        for(int i=0; i<6; i++)
        {
            jointData[i]=new_thread->sd_DataBuffer[new_thread->sd_tail][i];
        }
        new_thread-> sd_tail=(new_thread->sd_tail+1)%SDSIZE;
        new_thread-> sd_size--;
    }
    for (int j = 0;j<6;j++)
    {
        line_Joint_CmdPos[j]->setText(QString("%1").arg(gs_State.Joint_CmdPos[j]));  //gs_State.Joint_CmdPos[j]
        line_Joint_CmdVel[j]->setText(QString("%1").arg(gs_State.Joint_CmdVel[j]));//joint vel
        line_Car_CmdPos[j]->setText(QString("%1").arg(gs_State.Car_CmdPos[j])); //car pos
        line_Car_CmdVel[j]->setText(QString("%1").arg(gs_State.Car_CmdVel[j])); //car vel

        if(flagFile == true)
        {
            if(j == 0)
            {
                file.write( QString::number(timer_number).toUtf8()+" "+QString("%1").arg(gs_State.Joint_CmdPos[j]).toUtf8()+" ");
            }
            else if(j == 5)
            {
                file.write(QString("%1").arg(gs_State.Joint_CmdPos[j]).toUtf8()+"\n");

            }
            else
                file.write(QString("%1").arg(gs_State.Joint_CmdPos[j]).toUtf8()+" ");
        }
    }

}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_openThreadBtn_clicked()
{
    new_thread->start();
    timer.start(1);

}

void Widget::on_closeThreadBtn_clicked()
{
    new_thread->closeThread();
    new_thread->wait();
}


void Widget::on_send_instructions_btn_clicked()
{
    //将输入框里面的数据进行拆
    //数据存储到数据区，速度存储到速度显示
    QStringList list =  ui->line_instructions->text().split("=");
    QString cmd = list[0];
    QString data = list[1];
    qDebug()<<list[0]<<" "<<list[1]<<endl;//MOVC P1

    list = cmd.split(" ");
    //在cmdList里面检索是否有相关命令，若有则进入操作
    for (int i = 0;i<cmdList.length();i++) {
        if(list[0] == cmdList[i])
        {
            list = data.split(",");
            for (int i =0;i<MAX_SET_LINE_DATA;i++) {
                line_Joint_CmdPos[i]->setText(list[i]);//data1,2,3,4,5,6,V50,Z0
            }
            cmdRight = true;
            break;
        }
    }
    if(cmdRight == false)
        QMessageBox::information(NULL, "error", "输入指令错误");
    else
        cmdRight = false;

    ui->line_instructions->clear();
}

void Widget::on_btn_writeFile_clicked()
{
    QString filename ="data.txt";
    if(!dir.exists("data")){
        dir.mkdir("data");
    }
    dir="data";
    QString path = dir.filePath(filename);
    file.setFileName(path);

    //    if(file.open(QIODevice::WriteOnly |QIODevice::Text |QIODevice::Append)){
    //        //追加写入数据
    //        file.write("write somthing");
    //    }

    if(file.open(QIODevice::WriteOnly |QIODevice::Text)){
        //覆盖写入数据
        qDebug()<<"open success"<<endl;
        flagFile = true;
    }
}

//J1
void Widget::on_btn_J1add_clicked()
{
    if(isV == false)
    {
        // Cmd_JogInit();
        // Cmd_JogCoord(11); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
        Cmd_JogStart_Length(0,(Coord+10),1,5000,0.1);
    }
    else
        return;
}

void Widget::on_btn_J1add_pressed()
{
    if(isV == true)
    {

        //  Cmd_JogInit();
        //  Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
        Cmd_JogStart_Speed(0,Coord,1,500,100); //Cmd_JogStart_Speed(int axis,int Coor,int Dir,double Acc,double ratio);
    }
    else
        return;

}

void Widget::on_btn_J1add_released()
{

    //    if(isV == true)
    {
        Cmd_JogStop(0,1);
    }
    //    else
    return;
}


void Widget::on_btn_J1sub_clicked()
{
    if(isV == false)
    {
        // Cmd_JogInit();
        // Cmd_JogCoord(1); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
        Cmd_JogStart_Length(0,(Coord+10),-1,500,100);
    }
    else
        return;
}

void Widget::on_btn_J1sub_pressed()
{
    if(isV == true)
    {
        //Cmd_JogInit();
        //Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
        Cmd_JogStart_Speed(0,Coord,-1,500,100); //Cmd_JogStart_Speed(int axis,int Coor,int Dir,double Acc,double ratio);
        //Cmd_JogStart_Length(0,1,1,500,21); //(int axis,int coord,int Dir,double Acc,double
    }
    else
        return;

}

void Widget::on_btn_J1sub_released()
{
    Cmd_JogStop(0,1);
}

//J2
void Widget::on_btn_J2add_clicked()
{

}
void Widget::on_btn_J2add_pressed()
{
    // Cmd_JogInit();
    // Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(1,Coord,1,500,100);
}

void Widget::on_btn_J2add_released()
{
    Cmd_JogStop(1,1);
}

void Widget::on_btn_J2sub_clicked()
{

}
void Widget::on_btn_J2sub_pressed()
{
    // Cmd_JogInit();
    // Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(1,Coord,-1,500,100);
}

void Widget::on_btn_J2sub_released()
{
    Cmd_JogStop(1,1);
}

//J3
void Widget::on_btn_J3add_clicked()
{

}

void Widget::on_btn_J3add_pressed()
{
    //    Cmd_JogInit();
    //    Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(2,Coord,1,500,100);
}

void Widget::on_btn_J3add_released()
{
    Cmd_JogStop(2,1);
}

void Widget::on_btn_J3sub_clicked()
{

}

void Widget::on_btn_J3sub_pressed()
{
    //    Cmd_JogInit();
    //    Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(2,Coord,-1,500,100);
}

void Widget::on_btn_J3sub_released()
{
    Cmd_JogStop(2,1);
}


//J4
void Widget::on_btn_J4add_clicked()
{

}

void Widget::on_btn_J4add_pressed()
{
    //    Cmd_JogInit();
    //    Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(3,Coord,1,500,100);
}

void Widget::on_btn_J4add_released()
{
    Cmd_JogStop(3,1);
}

void Widget::on_btn_J4sub_clicked()
{

}

void Widget::on_btn_J4sub_pressed()
{
    //    Cmd_JogInit();
    //    Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(3,Coord,-1,500,100);
}

void Widget::on_btn_J4sub_released()
{
    Cmd_JogStop(3,1);
}


//J5
void Widget::on_btn_J5add_clicked()
{

}

void Widget::on_btn_J5add_pressed()
{
    //    Cmd_JogInit();
    //    Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(4,Coord,1,500,100);
}

void Widget::on_btn_J5add_released()
{
    Cmd_JogStop(4,1);
}

void Widget::on_btn_J5sub_clicked()
{

}

void Widget::on_btn_J5sub_pressed()
{
    //    Cmd_JogInit();
    //    Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(4,Coord,-1,500,100);
}

void Widget::on_btn_J5sub_released()
{
    Cmd_JogStop(4,1);
}

//J6
void Widget::on_btn_J6add_clicked()
{

}

void Widget::on_btn_J6add_pressed()
{
    //    Cmd_JogInit();
    //    Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(5,Coord,1,500,100);
}

void Widget::on_btn_J6add_released()
{
    Cmd_JogStop(5,1);
}

void Widget::on_btn_J6sub_clicked()
{

}

void Widget::on_btn_J6sub_pressed()
{
    //    Cmd_JogInit();
    //    Cmd_JogCoord(Coord); //关节(1)/笛卡尔2)/工具(3)/用户(4)/转台(5)
    Cmd_JogStart_Speed(5,Coord,-1,500,100);
}

void Widget::on_btn_J6sub_released()
{
    Cmd_JogStop(5,1);
}

void Widget::on_radioButtonV_clicked()
{
    isV = true;
}

void Widget::on_radioButtonP_clicked()
{
    isV = false;
}

void Widget::on_comboBox_axis_currentIndexChanged(int index)
{
    if(index == 0)
    {
        Coord = 1;
    }
    else if(index == 1)
        Coord = 2;
    else if(index == 2)
        Coord = 3;
    else if(index == 3)
        Coord = 4;
    else if(index == 4)
        Coord = 5;
    else if(index == 5)
        Coord = 6;

}

void Widget::on_closeFile_clicked()
{
    flagFile = false;
    file.close();
}

void Widget::on_btn_clear_clicked()
{
    Set_Robot_Simulation_Init();
}

void Widget::on_btn_drag_begin_clicked()
{
    Cmd_DragStart_Speed(0,0);
}

void Widget::on_btn_drag_stop_clicked()
{
    Cmd_DragStop(0);
}

void Widget::on_reset_btn_clicked()
{
    setStandardView();
}
