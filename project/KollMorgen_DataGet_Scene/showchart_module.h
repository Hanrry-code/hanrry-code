#ifndef SHOWCHART_MODULE_H
#define SHOWCHART_MODULE_H

#include <QWidget>
#include<showchart_module_widget.h>
#include"ui_showchart_module_widget.h"



class Showchart_module : public QObject
{
    Q_OBJECT
public:
    explicit Showchart_module(QObject *parent = 0);
    ShowChart_module_Widget *showchartWidget;



signals:

public slots:
};

#endif // SHOWCHART_MODULE_H
