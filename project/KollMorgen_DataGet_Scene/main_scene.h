#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include"showchart_module_widget.h"
#include"receive_data_widget.h"
#include<QPainter>
#include<QTimer>

namespace Ui {
class Main_Scene;
}

class Main_Scene : public QWidget
{
    Q_OBJECT

public:
    explicit Main_Scene(QWidget *parent = 0);

    //重新paintEvent事件 画示波器图片
    void paintEvent(QPaintEvent *);
    ~Main_Scene();
public:
    Ui::Main_Scene *ui;
    Receive_data_Widget      *m_recWidget;//数据接收模块窗口
    ShowChart_module_Widget  *m_cWidget;//数据显示模块窗口


private slots:

    void on_setHidden_btn_clicked();
signals:
    void change_background(int index);
};

#endif // MAIN_SCENE_H
