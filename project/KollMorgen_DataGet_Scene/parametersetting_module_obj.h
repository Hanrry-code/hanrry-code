#ifndef PARAMETERSETTING_MODULE_OBJ_H
#define PARAMETERSETTING_MODULE_OBJ_H

#include <QObject>
#include"globle_definition.h"
#include"parametersetting_widget.h"
#include <QThread>
//参数设置模块逻辑文件  主要负责实现参数设置模块的逻辑函数
class ParameterSetting_module_obj : public QObject
{
    Q_OBJECT
public:
    explicit ParameterSetting_module_obj(QObject *parent = 0);

signals:

public slots:

private:
    TargetParameters m_para;
    ParameterSetting_Widget pWidget;

};

#endif // PARAMETERSETTING_MODULE_OBJ_H
