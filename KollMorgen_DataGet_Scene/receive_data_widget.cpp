#include "receive_data_widget.h"
#include "ui_receive_data_widget.h"
#include <QDebug>
#include <QMessageBox>


Receive_data_Widget::Receive_data_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Receive_data_Widget)
{
    ui->setupUi(this);
    // TCP对象
    sock = new QTcpSocket(this);

    ui->btn_BindTcp->setEnabled(true);
    ui->IPLineEdit->setText("172.20.10.2");
    ui->portLineEdit->setText("20021");
    connect(sock, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
}
void Receive_data_Widget::on_btn_BindTcp_clicked()
{
    sock->connectToHost(QHostAddress(ui->IPLineEdit->text()),
                        ui->portLineEdit->text().toUShort());

    if(!sock->waitForConnected(2*1000))
    {
        QMessageBox::information(this, "错误", sock->errorString(), QMessageBox::Ok);
        return;
    }
    else
        qDebug() << "connection ok";
}


void Receive_data_Widget::readyReadSlot()
{
    ReceiveDataBuf = sock->readLine();
    //对数据进行处理

    if(ReceiveDataBuf.isEmpty()) return;// 数据缓存为空
    /* 删除所有空格 */
    QString tmp = ReceiveDataBuf;
    tmp.remove(QRegExp("\\s"));
    ReceiveDataBuf = tmp.toLatin1();
    /* 验证最后的数据为';',表示至少接收到一帧完整的数据 */
    if(ReceiveDataBuf.endsWith(';')){ // 接收到完整的数据
        QRegExp reg("(\\d+=-?\\d+\\.?\\d*;)", Qt::CaseInsensitive);
        qint32 pos = 0;
        // 遍历所有匹配的字符串
        while ((pos = reg.indexIn(ReceiveDataBuf, pos)) != -1) {

            pos += reg.matchedLength();

            /* 解析字符串,以'='划分两部分 */
            QStringList valueData = reg.capturedTexts().at(0).split('='); // 划分为两部分有效数据
            qDebug()<<valueData<<endl;
            qint32 graphNum = valueData.at(0).toInt();  // 第一部分是曲线编号
            QString strData = valueData.at(1);          // 第二部分是曲线数据
            strData.remove(';');  // 移除';'号
            double curveData = strData.toDouble();

            emit sendData(graphNum,curveData);

        }
        ReceiveDataBuf.clear();
    }
}

void Receive_data_Widget::Start()
{
    sock->write("ok");
}

void Receive_data_Widget::Stop()
{
    sock->write("stop");
}

Receive_data_Widget::~Receive_data_Widget()
{
    delete ui;
}

