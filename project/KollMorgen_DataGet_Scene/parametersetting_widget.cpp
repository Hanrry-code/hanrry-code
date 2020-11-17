#include "parametersetting_widget.h"
#include"parametersetting_module_obj.h"
#include <QColorDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTimer>

ParameterSetting_Widget::ParameterSetting_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterSetting_Widget)
{
    ui->setupUi(this);

    init_set_btn();
    combobox[0]->setCurrentIndex(1);
    combobox[1]->setCurrentIndex(2);
    combobox[2]->setCurrentIndex(3);
    combobox[3]->setCurrentIndex(4);
    combobox[4]->setCurrentIndex(5);
    combobox[5]->setCurrentIndex(6);

    dataNumbers = 2;
    ui->lineEdit_displayWith->setText("2000");
}

ParameterSetting_Widget::~ParameterSetting_Widget()
{
    delete ui;
}

//通道界面初始化
void ParameterSetting_Widget::init_set_btn()
{
    //曲线源
    combobox[0] = ui->NO1_comboBox;
    combobox[1] = ui->NO2_comboBox;
    combobox[2] = ui->NO3_comboBox;
    combobox[3] = ui->NO4_comboBox;
    combobox[4] = ui->NO5_comboBox;
    combobox[5] = ui->NO6_comboBox;

    //颜色选项按钮
    set_color_button[0] = ui->set_1color_btn;
    set_color_button[1] = ui->set_2color_btn;
    set_color_button[2] = ui->set_3color_btn;
    set_color_button[3] = ui->set_4color_btn;
    set_color_button[4] = ui->set_5color_btn;
    set_color_button[5] = ui->set_6color_btn;

    //显示曲线按钮
    select_CheckBox[0] = ui->checkBox_hide1;
    select_CheckBox[1] = ui->checkBox_hide2;
    select_CheckBox[2] = ui->checkBox_hide3;
    select_CheckBox[3] = ui->checkBox_hide4;
    select_CheckBox[4] = ui->checkBox_hide5;
    select_CheckBox[5] = ui->checkBox_hide6;

    qint32 colorIndex;
    //按钮绑定对应的槽函数
    for(int i=0;i<MAX_SET_BTN ;i++)
    {
        /* 使用随机颜色 */
        colorIndex = qrand()%20;// 伪随机
        set_color_button[i]->setPalette(QPalette(colorTable[colorIndex]));
        set_color_button[i]->setStyleSheet(tr("background-color: %1").arg(colorTable[colorIndex].name()));


        //绑定相关槽函数
        connect(set_color_button[i],SIGNAL(clicked()),this,SLOT(on_set_color_btn_clicked()));
        connect(select_CheckBox[i],SIGNAL(clicked()),this,SLOT(on_checkBox_hide_clicked()));

    }

}

//选择颜色
void ParameterSetting_Widget::on_set_color_btn_clicked()
{
    QObject *clickObject = sender();
    QColorDialog *colorDialog = new QColorDialog();
    colorDialog->setWindowTitle("选择颜色");
    for (int i = 0;i<MAX_SET_BTN;i++)
    {
        if(clickObject == set_color_button[i])
        {
            QColor color = set_color_button[i]->palette().background().color();
            color = colorDialog->getColor(color);

            if(color.isValid() )
            {
                set_color_button[i]->setPalette(QPalette( color ));
                set_color_button[i]->setStyleSheet(tr("background-color: %1").arg(color.name()));
            }
        }
    }
}


void ParameterSetting_Widget::on_select_color_currentIndexChanged(int index)
{
    emit change_background(index);

}
/*********************************/
void ParameterSetting_Widget::on_checkBox_hide_clicked()
{
    QObject *clickObject = sender();
    for (int i = 0;i<MAX_SET_BTN;i++)
    {
        //判断是哪个控件触发
        if(clickObject == select_CheckBox[i])
        {
            //判断是否勾选
            if(select_CheckBox[i]->isChecked())
                //勾选删除曲线
                emit removeGraph(i);
            else
                //取消勾选添加曲线
                emit addNewGraph(i,combobox[i]->currentText(),set_color_button[i]->palette().color(QPalette::Background));
        }
    }
}

/**
 * @brief SerialCurve::on_actionSaveImages_triggered 保存图像
 */
void ParameterSetting_Widget::on_actionSaveImages_btn_clicked()
{
    emit save();
}

void ParameterSetting_Widget::on_start_btn_clicked()
{
    // emit start(20);

    emit start();
    displayWith = ui->lineEdit_displayWith->text().toDouble();
}

void ParameterSetting_Widget::on_stop_btn_clicked()
{
    emit stop();
}

void ParameterSetting_Widget::on_selectZoom_btn_clicked(bool checked)
{
    emit zoomTrue(checked);
}

void ParameterSetting_Widget::on_showVerticalLines_clicked(bool checked)
{
    emit showVerticalLines(checked);
}
