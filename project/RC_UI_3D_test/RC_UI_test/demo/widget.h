#ifndef WIDGET_H
#define WIDGET_H

#define MAX_SET_LINE_DATA 6 //显示个数

#include <QDir>
#include <QFile>
#include <QPushButton>
#include <QTextBrowser>
#include <QTimer>
#include <QWidget>
#include "mythread.h"
#include "qwt_3D/qwt3d_gridplot.h"
#include "qwt_3D/qwt3d_function.h"
#include "qwt_3D/qwt3d_plot3d.h"
#include "axes.h"
#include "qwt_3D/qwt3d_function.h"
#include <QStyleFactory>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void init_Joint_CmdPos();
    void init_Car_CmdPos();
    void init_Joint_CmdVel();
    void init_Car_CmdVel();
    void init_qwt3D();
    void init_qss();
    void resetTics();
    void customScale();
    void setGrid(Qwt3D::SIDE s);
    void setStandardView();

    int Coord = 1;
    int timer_number = 0 ;
    ~Widget();
    QTextBrowser *line_Joint_CmdPos[MAX_SET_LINE_DATA];
    QTextBrowser *line_Car_CmdPos[MAX_SET_LINE_DATA];
    QTextBrowser *line_Joint_CmdVel[MAX_SET_LINE_DATA];
    QTextBrowser *line_Car_CmdVel[MAX_SET_LINE_DATA];

    QTimer timer;
    Mythread *new_thread;
    QFile file;
    QDir dir;
    QStringList cmdList = {"MOVC","movc","MOVJ","movj","MOVL","movl","IO","io","DELAY","delay",
                          "MOVC ","movc ","MOVJ ","movj ","MOVL ","movl ","IO ","io ","DELAY ","delay "};
    bool isV = true;
    bool flagFile = false;
    bool cmdRight = false;

    //QPushbutton *JAddBtn[MAX_SET_LINE_DATA];

    Qwt3D::GridPlot* plot;
    Qwt3D::Function *rosenbrock;

private:
    Ui::Widget *ui;
    int tics;

private slots:
    void Display();
    void on_openThreadBtn_clicked();
    void on_closeThreadBtn_clicked();
    void on_send_instructions_btn_clicked();
    void on_btn_writeFile_clicked();
    void on_btn_J1add_clicked();
    void on_btn_J1add_pressed();
    void on_btn_J1add_released();
    void on_btn_J1sub_clicked();
    void on_btn_J1sub_pressed();
    void on_btn_J1sub_released();
    void on_btn_J2add_pressed();
    void on_btn_J2add_released();
    void on_btn_J2sub_pressed();
    void on_btn_J2sub_released();
    void on_btn_J2add_clicked();
    void on_btn_J2sub_clicked();
    void on_btn_J3add_clicked();
    void on_btn_J3add_pressed();
    void on_btn_J3add_released();
    void on_btn_J3sub_clicked();
    void on_btn_J3sub_pressed();
    void on_btn_J3sub_released();
    void on_btn_J4add_clicked();
    void on_btn_J4add_pressed();
    void on_btn_J4add_released();
    void on_btn_J4sub_clicked();
    void on_btn_J4sub_pressed();
    void on_btn_J4sub_released();
    void on_btn_J5add_clicked();
    void on_btn_J5add_pressed();
    void on_btn_J5add_released();
    void on_btn_J5sub_clicked();
    void on_btn_J5sub_pressed();
    void on_btn_J5sub_released();
    void on_btn_J6add_clicked();
    void on_btn_J6add_pressed();
    void on_btn_J6add_released();
    void on_btn_J6sub_clicked();
    void on_btn_J6sub_pressed();
    void on_btn_J6sub_released();
    void on_radioButtonV_clicked();
    void on_radioButtonP_clicked();
    void on_comboBox_axis_currentIndexChanged(int index);
    void on_closeFile_clicked();
    void on_btn_clear_clicked();
    void on_btn_drag_begin_clicked();
    void on_btn_drag_stop_clicked();
    void on_reset_btn_clicked();
};
#endif // WIDGET_H
