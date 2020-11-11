#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include <QRadioButton>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QQueue>
//引入qt中串口通信需要的头文件
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "chartview.h"
#include "callout.h"




QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();


private:
//    void wheelEvent(QWheelEvent *event);

    void initUI();
    void initChart();
    void initChart2();
    void initChart3();
    void initChart4();
    void initChart5();
    void initChart6();

    void initSlot();

    void updateData(QString trans_data);
    void updateData2(QString trans_data);
    void updateData3(QString trans_data);
    void updateData4(QString trans_data);
    void updateData5(QString trans_data);
    void updateData6(QString trans_data);
    int  bytesToInt(QByteArray bytes);

    QSerialPort *serial;//全局的串口对象


    Ui::MainWidget *ui;

    ChartView *chartView;
    ChartView *chartView2;
    ChartView *chartView3;
    ChartView *chartView4;
    ChartView *chartView5;
    ChartView *chartView6;

    QChart *chart;
    QChart *chart2;
    QChart *chart3;
    QChart *chart4;
    QChart *chart5;
    QChart *chart6;



    Callout *tip;
    QLineSeries *series;
    QLineSeries *series2;
    QLineSeries *series3;
    QLineSeries *series4;
    QLineSeries *series5;
    QLineSeries *series6;

    QRadioButton *radioButton[6];

    QTimer *timer;

    quint16 count;
    QStringList list;
    bool isStopping;
    QFile file;
    int data_number = 1;
    typedef struct
    {
        qint32 Fx;
        qint32 Fy;
        qint32 Fz;
        qint32 Mx;
        qint32 My;
        qint32 Mz;

        uint32_t Status_Code;
        uint32_t Sample_Count;
    }From_Sensor_t;

    QQueue<From_Sensor_t> fifo;

private slots:
    void timerSlot();
    //void buttonSlot();
    void tipSlot(QPointF position, bool isHovering);
    void readData();
    void on_OpenSerialButton_clicked();
};

#endif // MAINWIDGET_H
