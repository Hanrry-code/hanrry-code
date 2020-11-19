#ifndef PARAMETERSETTING_WIDGET_H
#define PARAMETERSETTING_WIDGET_H
#define MAX_SET_BTN 6 //有6个按钮

#include "ui_parametersetting_widget.h"
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QWidget>
#include <QFileDialog>
#include "globle_definition.h"

namespace Ui {
class ParameterSetting_Widget;
}

class ParameterSetting_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterSetting_Widget(QWidget *parent = 0);

    void setParameter(TargetParameters *widget_para);//设置参数设置模块的的参数  传入globle_definition中的结构体
    ~ParameterSetting_Widget();
    void init_set_btn();


public:
    Ui::ParameterSetting_Widget *ui;
    int pass_num =MAX_SET_BTN;
    TargetParameters *widget_para;//创建结构体

    QPushButton *set_color_button[MAX_SET_BTN];
    QCheckBox *select_CheckBox[MAX_SET_BTN];
    QComboBox *combobox[MAX_SET_BTN];
    const QColor colorTable[20] = {
        QColor("#FB0873"), QColor("#3AFFF0"),QColor("#F8CF45"),QColor("#A553A8"),
        QColor("#87FF8D"), QColor("#F7595B"),QColor("#55C6DE"),QColor("#E8FF4C"),
        QColor("#E4008A"), QColor("#5AFFCA"),QColor("#F7A148"),QColor("#817FBC"),
        QColor("#AAFF6C"), QColor("#F62869"),QColor("#4EF1F5"),QColor("#FAE947"),
        QColor("#BE349B"), QColor("#71FFA1"),QColor("#F77550"),QColor("#62ACD2")};

    double displayWith;

private slots:

    //曲线颜色选择
    void set_color();

    //背景色选择
    void on_select_color_currentIndexChanged(int index);
    void checkBox_hide();
    void on_actionSaveImages_btn_clicked();
    void on_start_btn_clicked();
    void on_stop_btn_clicked();
    void on_selectZoom_btn_clicked(bool checked);
    void on_showVerticalLines_clicked(bool checked);
    void on_up_btn_clicked();
    void on_MarkingPork_clicked(bool checked);
    void on_down_btn_clicked();
    void on_left_btn_clicked();
    void on_right_btn_clicked();

    void on_horizontalGrid_clicked(bool checked);

    void on_verticalGrid_clicked(bool checked);

signals:
    void change_background(int index);//切换背景
    void change_graphColor(qint32 currentNum,QString graph_name,QColor graph_color);//切换曲线颜色

    void displayGraph(qint32 currentNum,QString graph_name,QColor graph_color);//显示曲线
    void removeGraph(int index);//隐藏曲线
    void save();//截图保存
//    void start(int millisecond);
    void start();//开始采集
    void stop();//暂停采集
    void zoomTrue(bool c);//框选放大
    void showVerticalLines(bool c);//垂直线
    void up();
    void down();
    void left();
    void right();
    void MarkingPork(bool c);//显示点
    void horizontalGrid(bool c);//水平网格
    void verticalGrid(bool c);//垂直网格

};

#endif // PARAMETERSETTING_WIDGET_H
