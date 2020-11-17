#include "main_scene.h"
#include "ui_main_scene.h"
#include<QPainter>
#include<QtNetwork/QTcpServer>
#include<QtNetwork/QNetworkInterface>
#include<QTcpSocket>
#include<QString>
#include<QTimer>
#include  <QDebug>
#include <QFile>
#include <QVBoxLayout>

Main_Scene::Main_Scene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Main_Scene)
{
    ui->setupUi(this);
    setWindowTitle("数据跟踪");


    m_cWidget=new ShowChart_module_Widget(this);//折线图显示模块窗口
    m_cWidget->move(10,75);

    m_recWidget=new Receive_data_Widget(this);//tcp接收数据模块窗口
    m_recWidget->move(750,5);

    /////////////////////
    connect(m_cWidget->m_pWidget,SIGNAL(start()),m_recWidget,SLOT(Start()));
    connect(m_recWidget,SIGNAL(sendData(int,double)),m_cWidget,SLOT(draw(int,double)));
    connect(m_cWidget->m_pWidget,SIGNAL(stop()),m_recWidget,SLOT(Stop()));

    QVBoxLayout layout;
    layout.addWidget(m_cWidget);
    layout.addWidget(m_cWidget->m_pWidget);
    this->setLayout(&layout);
    /* ui初始化 */
    QApplication::setStyle(QStyleFactory::create("fusion"));// fusion 风格
    QFile file(":/pss/1.css");
    if (!file.open(QFile::ReadOnly)){  // 打开文件
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8 ");
    QString qss = in.readAll();        // 读取数据
    qApp->setStyleSheet(qss);    // 应用
    file.close();
    this->setWindowTitle("基于tcp的数据图像化工具 v1.0");
}



void Main_Scene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res_photo/fliter.png");//示波器 图片
    pix = pix.scaled( pix.width() * 0.4 , pix.height() * 0.4);
    painter.drawPixmap(10,10,pix);
}

Main_Scene::~Main_Scene()
{
    delete ui;
}



void Main_Scene::on_setHidden_btn_clicked()
{
    static bool checked = true;
    if(checked)
    {
        m_cWidget->m_pWidget->setHidden(true);
        ui->setHidden_btn->setText("完整示图");
        m_cWidget->setFixedHeight(this->height()-70);
        checked = false;
        return;
    }

    ui->setHidden_btn->setText("缩小示图");
    m_cWidget->setFixedHeight(406);
    m_cWidget->m_pWidget->setHidden(false);
    checked = true;
}
