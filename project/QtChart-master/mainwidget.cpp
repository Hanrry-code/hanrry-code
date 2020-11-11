#include "mainwidget.h"
#include "ui_mainwidget.h"
//添加串口通信需要用到的两个串口头文件
#include <QDebug>
#include <QtMath>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    chart(new QChart),
    tip(0),
    timer(new QTimer),
    count(0),
    isStopping(false)
{
    ui->setupUi(this);

    initUI();
    radioButton[0]->setChecked(true);


    file.setFileName("finish.txt");
    file.open(QIODevice::ReadOnly);

//    timer->start(10);

    initSlot();
    //查找可用的串口

    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->portBox->addItem(serial.portName());
            serial.close();
        }
    }
    ui->baudBox->setCurrentText(0);
}

MainWidget::~MainWidget()
{
    delete ui;
}

//void MainWidget::wheelEvent(QWheelEvent *event)
//{
//    if (event->delta() > 0) {
//        chart->zoom(1.1);
//    } else {
//        chart->zoom(10.0/11);
//    }

//    QWidget::wheelEvent(event);
//}

void MainWidget::initUI()
{
    for (int i =0;i<6;i++)
    {
        radioButton[i] =  QWidget::findChild<QRadioButton *>("radioButton_"+QString::number(i+1));

    }
    initChart();
    initChart2();
    initChart3();
    initChart4();
    initChart5();
    initChart6();
}

void MainWidget::initChart()
{
    series = new QLineSeries;
    chart = new QChart();
    chart->addSeries(series);

    //    series->setUseOpenGL(true);

    chart->createDefaultAxes();
    chart->axisY()->setRange(-50000, 50000);
    chart->axisX()->setRange(0,300);

    chart->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart->axisX()->setTitleText("Time/sec");
    chart->axisY()->setTitleText("Data/m");

    chart->axisX()->setGridLineVisible(false);
    chart->axisY()->setGridLineVisible(false);

    /* hide legend */
    chart->legend()->hide();

    chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->HorLayout1->addWidget(chartView);

}
void MainWidget::initChart2()
{
    series2 = new QLineSeries;
    chart2 = new QChart();
    chart2->addSeries(series2);

    //    series->setUseOpenGL(true);

    chart2->createDefaultAxes();
    chart2->axisY()->setRange(-50000, 50000);
    chart2->axisX()->setRange(0,300);

    chart2->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart2->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart2->axisX()->setTitleText("Time/sec");
    chart2->axisY()->setTitleText("Data/m");

    chart2->axisX()->setGridLineVisible(false);
    chart2->axisY()->setGridLineVisible(false);

    /* hide legend */
    chart2->legend()->hide();

    chartView2 = new ChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    ui->HorLayout2->addWidget(chartView2);

}
void MainWidget::initChart3()
{
    series3 = new QLineSeries;
    chart3 = new QChart();
    chart3->addSeries(series3);

    //    series->setUseOpenGL(true);

    chart3->createDefaultAxes();
    chart3->axisY()->setRange(-50000, 50000);
    chart3->axisX()->setRange(0,300);

    chart3->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart3->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart3->axisX()->setTitleText("Time/sec");
    chart3->axisY()->setTitleText("Data/m");

    chart3->axisX()->setGridLineVisible(false);
    chart3->axisY()->setGridLineVisible(false);

    /* hide legend */
    chart3->legend()->hide();

    chartView3 = new ChartView(chart3);
    chartView3->setRenderHint(QPainter::Antialiasing);

    ui->HorLayout3->addWidget(chartView3);

}
void MainWidget::initChart4()
{
    series4 = new QLineSeries;
    chart4 = new QChart();
    chart4->addSeries(series4);

    //    series->setUseOpenGL(true);

    chart4->createDefaultAxes();
    chart4->axisY()->setRange(-300, 300);
    chart4->axisX()->setRange(0,300);

    chart4->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart4->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart4->axisX()->setTitleText("Time/sec");
    chart4->axisY()->setTitleText("Data/m");

    chart4->axisX()->setGridLineVisible(false);
    chart4->axisY()->setGridLineVisible(false);

    /* hide legend */
    chart4->legend()->hide();

    chartView4 = new ChartView(chart4);
    chartView4->setRenderHint(QPainter::Antialiasing);

    ui->HorLayout4->addWidget(chartView4);

}
void MainWidget::initChart5()
{
    series5 = new QLineSeries;
    chart5 = new QChart();
    chart5->addSeries(series5);

    //    series->setUseOpenGL(true);

    chart5->createDefaultAxes();
    chart5->axisY()->setRange(-300, 300);
    chart5->axisX()->setRange(0,300);

    chart5->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart5->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart5->axisX()->setTitleText("Time/sec");
    chart5->axisY()->setTitleText("Data/m");

    chart5->axisX()->setGridLineVisible(false);
    chart5->axisY()->setGridLineVisible(false);

    /* hide legend */
    chart5->legend()->hide();

    chartView5 = new ChartView(chart5);
    chartView5->setRenderHint(QPainter::Antialiasing);

    ui->HorLayout5->addWidget(chartView5);

}
void MainWidget::initChart6()
{
    series6 = new QLineSeries;
    chart6 = new QChart();
    chart6->addSeries(series6);

    //    series->setUseOpenGL(true);

    chart6->createDefaultAxes();
    chart6->axisY()->setRange(-300, 300);
    chart6->axisX()->setRange(0,300);

    chart6->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart6->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    chart6->axisX()->setTitleText("Time/sec");
    chart6->axisY()->setTitleText("Data/m");

    chart6->axisX()->setGridLineVisible(false);
    chart6->axisY()->setGridLineVisible(false);

    /* hide legend */
    chart6->legend()->hide();

    chartView6 = new ChartView(chart6);
    chartView6->setRenderHint(QPainter::Antialiasing);

    ui->HorLayout6->addWidget(chartView6);

}

void MainWidget::initSlot()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
   // connect(ui->stopBtn, SIGNAL(clicked(bool)), this, SLOT(buttonSlot()));
    connect(series, SIGNAL(hovered(QPointF, bool)), this, SLOT(tipSlot(QPointF,bool)));
}

void MainWidget::updateData(QString trans_data)
{
    int i;
    QVector<QPointF> oldData = series->pointsVector();
    QVector<QPointF> data;

    if (oldData.size() < 300)
    {
        data = series->pointsVector();
    }
    else
    {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData.size(); ++i)
        {
            data.append(QPointF(i - 1 , oldData.at(i).y()));
        }
    }


    qint64 size = data.size();
    /*
     * 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
    for(i = 0; i < 1; ++i)
    {
        data.append(QPointF(i + size, trans_data.toInt()));
    }

    series->replace(data);

    count++;
}
void MainWidget::updateData2(QString trans_data)
{
    int i;
    QVector<QPointF> oldData = series2->pointsVector();
    QVector<QPointF> data;

    if (oldData.size() < 300)
    {
        data = series2->pointsVector();
    }
    else
    {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData.size(); ++i)
        {
            data.append(QPointF(i - 1 , oldData.at(i).y()));
        }
    }


    qint64 size = data.size();
    /*
     * 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
    for(i = 0; i < 1; ++i)
    {
        data.append(QPointF(i + size, trans_data.toInt()));
    }

    series2->replace(data);

    count++;
}void MainWidget::updateData3(QString trans_data)
{
    int i;
    QVector<QPointF> oldData = series3->pointsVector();
    QVector<QPointF> data;

    if (oldData.size() < 300)
    {
        data = series3->pointsVector();
    }
    else
    {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData.size(); ++i)
        {
            data.append(QPointF(i - 1 , oldData.at(i).y()));
        }
    }


    qint64 size = data.size();
    /*
     * 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
    for(i = 0; i < 1; ++i)
    {
        data.append(QPointF(i + size, trans_data.toInt()));
    }

    series3->replace(data);

    count++;
}
void MainWidget::updateData4(QString trans_data)
{
    int i;
    QVector<QPointF> oldData = series4->pointsVector();
    QVector<QPointF> data;

    if (oldData.size() < 300)
    {
        data = series4->pointsVector();
    }
    else
    {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData.size(); ++i)
        {
            data.append(QPointF(i - 1 , oldData.at(i).y()));
        }
    }


    qint64 size = data.size();
    /*
     * 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
    for(i = 0; i < 1; ++i)
    {
        data.append(QPointF(i + size, trans_data.toInt()));
    }

    series4->replace(data);

    count++;
}void MainWidget::updateData5(QString trans_data)
{
    int i;
    QVector<QPointF> oldData = series5->pointsVector();
    QVector<QPointF> data;

    if (oldData.size() < 300)
    {
        data = series5->pointsVector();
    }
    else
    {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData.size(); ++i)
        {
            data.append(QPointF(i - 1 , oldData.at(i).y()));
        }
    }


    qint64 size = data.size();
    /*
     * 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
    for(i = 0; i < 1; ++i)
    {
        data.append(QPointF(i + size, trans_data.toInt()));
    }

    series5->replace(data);

    count++;
}
void MainWidget::updateData6(QString trans_data)
{
    int i;
    QVector<QPointF> oldData = series6->pointsVector();
    QVector<QPointF> data;

    if (oldData.size() < 300)
    {
        data = series6->pointsVector();
    }
    else
    {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData.size(); ++i)
        {
            data.append(QPointF(i - 1 , oldData.at(i).y()));
        }
    }


    qint64 size = data.size();
    /*
     * 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
    for(i = 0; i < 1; ++i)
    {
        data.append(QPointF(i + size, trans_data.toInt()));
    }

    series6->replace(data);

    count++;
}

void MainWidget::timerSlot()
{
    if (QObject::sender() == timer)
    {
//                if(!file.atEnd())
//                {
//                    QString s =  file.readLine();
//                    for (int i =0;i<6;i++) {
//                        if(radioButton[i]->isChecked())
//                        {


//                        }
//                    }


//                }
//                else
//                {
//                    //            file.close();
//                }


    }
}

//void MainWidget::buttonSlot()
//{
//    if (QObject::sender() == ui->stopBtn) {
//        if (!isStopping) {
//            timer->stop();
//        } else {
//            timer->start();
//        }
//        isStopping = !isStopping;
//    }
//}

void MainWidget::tipSlot(QPointF position, bool isHovering)
{
    if (tip == 0)
        tip = new Callout(chart);

    if (isHovering) {
        tip->setText(QString("X: %1 \nY: %2 ").arg(position.x()).arg(position.y()));

        tip->setAnchor(position);
        tip->setZValue(11);
        tip->updateGeometry();
        tip->show();
    } else {
        tip->hide();
    }
}




void MainWidget::on_OpenSerialButton_clicked()
{
    if(ui->OpenSerialButton->text()==tr("open"))
    { serial = new QSerialPort;

        //设置串口名
        serial->setPortName(ui->portBox->currentText());


        //设置波特率
        serial->setBaudRate(QSerialPort::Baud115200);

        //设置数据位
        switch (ui->dataBox->currentIndex())
        {
        case 0:
            serial->setDataBits(QSerialPort::Data8);
            break;
        default:
            break;
        }

        //设置校验位
        switch (ui->checkBox->currentIndex())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;

        default:
            break;

        }

        //设置停止位
        switch (ui->stopBox->currentIndex()) {
        case 0:
            serial->setStopBits(QSerialPort::OneStop);
            break;

        case 1:
            serial->setStopBits(QSerialPort::TwoStop);
            break;

        default:
            break;
        }


        //设置控制流
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //打开串口
        serial->open(QIODevice::ReadWrite);

        ui->portBox->setEnabled(false);
        ui->dataBox->setEnabled(false);
        ui->checkBox->setEnabled(false);
        ui->stopBox->setEnabled(false);
        ui->baudBox->setEnabled(false);
        ui->OpenSerialButton->setText("close");

        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWidget::readData);
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        ui->portBox->setEnabled(true);
        ui->dataBox->setEnabled(true);
        ui->checkBox->setEnabled(true);
        ui->stopBox->setEnabled(true);
        ui->baudBox->setEnabled(true);
        ui->OpenSerialButton->setText("open");


    }
}
int MainWidget:: bytesToInt(QByteArray bytes)
{
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}
void MainWidget::readData()
{
    QByteArray buf;

    buf = serial->read(32);
    if(buf.length()>=32)
    {
        From_Sensor_t feed;

        memcpy(&feed,buf,sizeof(From_Sensor_t));
        qDebug()<<"feed.Fx"+QString::number(feed.Fx)+" "
                  +"feed.Fy"+QString::number(feed.Fy)+" "

                  +"feed.Fz"+QString::number(feed.Fz)+" "
                  +"feed.Mx"+QString::number(feed.Mx)+" "
                  +"feed.My"+QString::number(feed.My)+" "
                  +"feed.Mz"+QString::number(feed.Mz)+" "
                  +"feed.Status_Code"+QString::number(feed.Status_Code)+" "
                  +"feed.Sample_Count"+QString::number(feed.Sample_Count)<<endl;

            updateData(QString::number(feed.Fx));

            updateData2(QString::number(feed.Fy));

            updateData3(QString::number(feed.Fz));

            updateData4(QString::number(feed.Mx));

            updateData5(QString::number(feed.My));

            updateData6(QString::number(feed.Mz));


        buf.clear();
    }
}
