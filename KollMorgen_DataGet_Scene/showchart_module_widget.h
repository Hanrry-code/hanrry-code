#ifndef SHOWCHART_MODULE_WIDGET_H
#define SHOWCHART_MODULE_WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "parametersetting_widget.h"
#include "qcustomplot.h"
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include "receive_data_widget.h"

namespace Ui {
class ShowChart_module_Widget;
}

class ShowChart_module_Widget : public QWidget
{
    Q_OBJECT


public:

    double time_x[70];//设置横坐标数据


public:
    explicit ShowChart_module_Widget(QWidget *parent = 0);
    ~ShowChart_module_Widget();
    void Chart_init();
    void configMultiPlot(QComboBox **combobox,QPushButton **set_color_button);


public slots:
    //设置背景
    void change_backgroundColor(int index);

    //添加一条曲线
    void addNewGraph(qint32 currentNum,QString graph_name,QColor graph_color);
    void remove_graph(int index);
    void display_graph(int index);

    void actionSaveImages();
    void draw(qint32 GraphNumber,double data);
    void actionselectZoom(bool checked);
    void slots_mouseMove(QMouseEvent* event);
    void actionCoorTips(bool checked);
    void setGraphColor(qint32 index,QString graph_name,QColor graph_color);
    void markingPoint(bool checked);
    //上下左右移动显示区域
    void chartUp();
    void chartDown();
    void chartLeft();
    void chartRight();
    void horizontalGridVisible(bool checked);
    void verticalGridVisible(bool checked);

    //    void StartRecording(int millisecond);
    //    void StopRecording();


public:
    Ui::ShowChart_module_Widget *ui;
    ParameterSetting_Widget *m_pWidget;//参数设置窗口
    //    QTimer timer;


    QFileDialog *initSaveFileDialog();
private:
    QCPItemStraightLine *  lineV; // 垂直线
    QList<QCPItemTracer *> tracerPointArray;//跟踪的点
    QList<QCPItemText *>   lblGraph; // 显示曲线值
    int x = 0;
    qint32 numGraphs;


};

#endif // SHOWCHART_MODULE_WIDGET_H
