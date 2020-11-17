#ifndef RECEIVE_DATA_WIDGET_H
#define RECEIVE_DATA_WIDGET_H

#include <QWidget>
#include<QTcpSocket>
#include<QString>
#include<QTimer>
#include <QHostAddress>


namespace Ui {
class Receive_data_Widget;
}

class Receive_data_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Receive_data_Widget(QWidget *parent = 0);
    ~Receive_data_Widget();
    QTcpSocket *sock;
    QByteArray ReceiveDataBuf;

public:
    Ui::Receive_data_Widget *ui;

public slots:
    void Start();
    void Stop();

private slots:
    void on_btn_BindTcp_clicked();
    void readyReadSlot();
signals:
    void sendData(qint32,double);

};

#endif // RECEIVE_DATA_WIDGET_H
