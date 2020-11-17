#include "showchart_module_widget.h"
#include "ui_showchart_module_widget.h"
#include "showchart_module.h"
#include "qcustomplot.h"

ShowChart_module_Widget::ShowChart_module_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowChart_module_Widget)
  //    timer(new QTimer)
{
    ui->setupUi(this);
    m_pWidget=new ParameterSetting_Widget(this);//参数设置模块窗口
    m_pWidget->move(0,480);

    Chart_init();//初始化表格
    connect(m_pWidget,SIGNAL(change_background(int)),this,SLOT(change_backgroundColor(int)));
    //    connect(m_pWidget,SIGNAL(addNewGraph(qint32,QString,QColor)),this,SLOT(addNewGraph(qint32,QString,QColor)));
    connect(m_pWidget,SIGNAL(addNewGraph(qint32,QString,QColor)),this,SLOT(display_graph(int)));

    connect(m_pWidget,SIGNAL(removeGraph(int)),this,SLOT(remove_graph(int)));
    connect(m_pWidget,SIGNAL(save()),this,SLOT(actionSaveImages()));//保存图片
    connect(m_pWidget,SIGNAL(zoomTrue(bool)),this,SLOT(actionselectZoom(bool)));//选择缩放
    connect(m_pWidget,SIGNAL(showVerticalLines(bool)),this,SLOT(actionCoorTips(bool)));//坐标显示
    //绑定开始信号与开启定时器槽函数
    //  connect(m_pWidget,SIGNAL(start(int millisecond)),this,SLOT(StartRecording(int millisecond)));
    //  connect(&timer, SIGNAL(timeout()), this, SLOT(draw()));
}

//初始化曲线
void ShowChart_module_Widget::Chart_init()
{
    // set some pens, brushes and backgrounds:
    ui->chart_plot->xAxis->setBasePen(QPen(Qt::white, 3));//轴线的画笔
    ui->chart_plot->yAxis->setBasePen(QPen(Qt::white, 3));
    ui->chart_plot->xAxis->setTickPen(QPen(Qt::white, 1));//轴线刻度的画笔
    ui->chart_plot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->chart_plot->xAxis->setSubTickPen(QPen(Qt::white, 1));//轴子刻度线的画笔
    ui->chart_plot->yAxis->setSubTickPen(QPen(Qt::white, 1));

    ui->chart_plot->xAxis->setTickLabelColor(Qt::white);//轴刻度文字的颜色
    ui->chart_plot->yAxis->setTickLabelColor(Qt::white);
    ui->chart_plot->xAxis->setLabel("time");
    ui->chart_plot->yAxis->setLabel("data");
    ui->chart_plot->xAxis->setLabelColor(Qt::white);
    ui->chart_plot->yAxis->setLabelColor(Qt::white);

    ui->chart_plot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->chart_plot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    //设置网格
//    ui->chart_plot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    ui->chart_plot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    ui->chart_plot->xAxis->grid()->setSubGridVisible(true);
//    ui->chart_plot->yAxis->grid()->setSubGridVisible(true);
    ui->chart_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->chart_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->chart_plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->chart_plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->chart_plot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->chart_plot->axisRect()->setBackground(axisRectGradient);


    ui->chart_plot->xAxis->setRange(0, 10, Qt::AlignCenter);
    ui->chart_plot->yAxis->setRange(0, 10, Qt::AlignCenter);

    //设定右上角图形标注和字体
    ui->chart_plot->legend->setBorderPen(QPen(QColor(140, 140, 140,0)));// legend 边框颜色透明
    ui->chart_plot->legend->setVisible(true);
    ui->chart_plot->legend->setTextColor(QColor(255,255,255,150)); // legend 字体颜色,白色
    ui->chart_plot->legend->setBrush(QColor(74,74,74,0));   //legend背景色设为灰色但背景透明，允许图像在legend区域可见
    ui->chart_plot->legend->setWrap(20); // 超过20行就换一列

    //设置曲线可拖拽 滚轮放大缩小 图像可选择
    //    ui->chart_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->chart_plot->setInteractions(QCP::iRangeDrag | QCP::iSelectPlottables|QCP::iSelectAxes);

    /*********************************/
    configMultiPlot(m_pWidget->combobox,m_pWidget->set_color_button);


}

/**
 * @brief SerialCurve::addNewGraph 添加新的曲线
 */
void ShowChart_module_Widget::addNewGraph(qint32 currentNum,QString graph_name,QColor graph_color)
{
    // add new graphs and set their look:
    ui->chart_plot->addGraph();

    QPen pen;         // 画笔,绘制曲线颜色,形状等
    pen.setWidth(2);  //线宽
    pen.setStyle(Qt::PenStyle::SolidLine);// a plain line
    pen.setColor(graph_color);//设置曲线颜色

    qDebug()<<currentNum<<endl;

    ui->chart_plot->graph(currentNum)->setPen(pen); // line color blue for first graph
    ui->chart_plot->graph(currentNum)->setName(graph_name);//默认曲线名字
    ui->chart_plot->graph(currentNum)->setSelectable(QCP::stNone);// 禁止鼠标选择曲线
    ui->chart_plot->yAxis->rescale(true);
    ui->chart_plot->replot();
}

/**
 * @brief SerialCurve::configMultiPlot 添加多条曲线
 */
void ShowChart_module_Widget::configMultiPlot(QComboBox **combobox,QPushButton **set_color_button)
{
    numGraphs = 6;
    /* 添加多条曲线 */
    for(qint32 i=0; i<numGraphs; i++){
        // set line style
        this->addNewGraph(i,combobox[i]->currentText(),set_color_button[i]->palette().color(QPalette::Background));
    }
    ui->chart_plot->replot(QCustomPlot::rpQueuedReplot);

}

//显示曲线
void ShowChart_module_Widget::display_graph(int index)
{
    //index--;
    ui->chart_plot->graph(index)->setVisible(true);
    ui->chart_plot->replot();
}

//隐藏曲线
void ShowChart_module_Widget::remove_graph(int index)
{
    //index--;
    ui->chart_plot->graph(index)->setVisible(false);
//    ui->chart_plot->graph(index)

    ui->chart_plot->replot();
}

//切换背景颜色
void ShowChart_module_Widget::change_backgroundColor(int index)
{

    if(index == 0)
    {
        // 深色背景
        // set some pens, brushes and backgrounds:
        ui->chart_plot->xAxis->setBasePen(QPen(Qt::white, 1));
        ui->chart_plot->yAxis->setBasePen(QPen(Qt::white, 1));
        ui->chart_plot->xAxis->setTickPen(QPen(Qt::white, 1));
        ui->chart_plot->yAxis->setTickPen(QPen(Qt::white, 1));
        ui->chart_plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
        ui->chart_plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
        ui->chart_plot->xAxis->setTickLabelColor(Qt::white);
        ui->chart_plot->yAxis->setTickLabelColor(Qt::white);
        ui->chart_plot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
        ui->chart_plot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//        ui->chart_plot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//        ui->chart_plot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//        ui->chart_plot->xAxis->grid()->setSubGridVisible(true);
//        ui->chart_plot->yAxis->grid()->setSubGridVisible(true);
        ui->chart_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
        ui->chart_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
        ui->chart_plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
        ui->chart_plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
        plotGradient.setColorAt(0, QColor(80, 80, 80));
        plotGradient.setColorAt(1, QColor(50, 50, 50));
        ui->chart_plot->setBackground(plotGradient);
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(80, 80, 80));
        axisRectGradient.setColorAt(1, QColor(30, 30, 30));
        ui->chart_plot->axisRect()->setBackground(axisRectGradient);
        ui->chart_plot->legend->setTextColor(QColor(255, 255, 255, 150)); // legend 字体颜色,白色
    }
    if(index == 1)
    {
        // 高亮背景
        // set some pens, brushes and backgrounds:
        ui->chart_plot->xAxis->setBasePen(QPen(Qt::black, 1));
        ui->chart_plot->yAxis->setBasePen(QPen(Qt::black, 1));
        ui->chart_plot->xAxis->setTickPen(QPen(Qt::black, 1));
        ui->chart_plot->yAxis->setTickPen(QPen(Qt::black, 1));
        ui->chart_plot->xAxis->setSubTickPen(QPen(Qt::black, 1));
        ui->chart_plot->yAxis->setSubTickPen(QPen(Qt::black, 1));
        ui->chart_plot->xAxis->setTickLabelColor(Qt::black);
        ui->chart_plot->yAxis->setTickLabelColor(Qt::black);
        ui->chart_plot->xAxis->grid()->setPen(QPen(QColor(115, 115, 115), 1, Qt::DotLine));
        ui->chart_plot->yAxis->grid()->setPen(QPen(QColor(115, 115, 115), 1, Qt::DotLine));
//        ui->chart_plot->xAxis->grid()->setSubGridPen(QPen(QColor(175, 175, 175), 1, Qt::DotLine));
//        ui->chart_plot->yAxis->grid()->setSubGridPen(QPen(QColor(175, 175, 175), 1, Qt::DotLine));
//        ui->chart_plot->xAxis->grid()->setSubGridVisible(true);
//        ui->chart_plot->yAxis->grid()->setSubGridVisible(true);
        ui->chart_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
        ui->chart_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
        ui->chart_plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
        ui->chart_plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
        plotGradient.setColorAt(0, QColor(255, 255, 255));
        plotGradient.setColorAt(1, QColor(255, 255, 255));
        ui->chart_plot->setBackground(plotGradient);
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(255, 255, 255));
        axisRectGradient.setColorAt(1, QColor(255, 255, 255));
        ui->chart_plot->axisRect()->setBackground(axisRectGradient);
        ui->chart_plot->legend->setTextColor(QColor(0, 0 , 0, 150)); // legend 字体颜色,白色 // 高亮背景

    }

    ui->chart_plot->replot(QCustomPlot::rpQueuedReplot);
}


/**
 * @brief SerialCurve::on_actionSaveImages_triggered 保存图像
 */
void ShowChart_module_Widget::actionSaveImages()
{
    QFileDialog *fileDialog = this->initSaveFileDialog();
    QString fileName = nullptr;
    QString fileType = nullptr;

    if(fileDialog->exec() == QDialog::Accepted) {
        fileName = fileDialog->selectedFiles()[0]; // 文件名不包含文件类型(.png)
        fileType = fileDialog->selectedNameFilter();

        QRegExp reg("(\\.).*(\\))", Qt::CaseInsensitive);// 匹配 .png)
        reg.indexIn(fileType);
        fileType = reg.cap(0);
        fileType.chop(1);
        fileName += fileType;// 拼接文件名和文件类型
    }
    QFileInfo file(fileName);

    if(file.path() != "/")
    {
        qint32 count = fileDialog->layout()->count();
        QWidget *pWidget = fileDialog->layout()->itemAt(count-1)->widget();// 获取layout最后一个Widget的指针
        count = pWidget->children().count();
        QDoubleSpinBox *pScale = (QDoubleSpinBox *)pWidget->children().at(count-1);// 获取pWidget的子widget
        QSpinBox *pHeight = (QSpinBox *)pWidget->children().at(count-3);
        QSpinBox *pWidth  = (QSpinBox *)pWidget->children().at(count-5);
        qint32 width      = pWidth->value();
        qint32 height     = pHeight->value();
        double scale      = pScale->value();

        bool success = false;

        if(fileName.endsWith(".png")){
            success = ui->chart_plot->savePng(fileName, width, height, scale, 100, 100);
        }else if(fileName.endsWith(".jpg")){
            success = ui->chart_plot->saveJpg(fileName,width, height, scale,100,100);
        }else if(fileName.endsWith(".bmp")){
            success = ui->chart_plot->saveBmp(fileName,width, height, scale,100);
        }else if(fileName.endsWith(".pdf")){
            success = ui->chart_plot->savePdf(fileName,width, height, QCP::epAllowCosmetic,"ing10 SerialData","Curve");
        }

        if(success){
            QDesktopServices::openUrl(QUrl::fromLocalFile(file.path()));
        }else{
            QMessageBox::information(NULL, tr("SaveFiles"), tr("保存失败"));
        }

    }
    else
    {
        QMessageBox::information(NULL, tr("saveFile"),tr("请选择正确路径"));
    }
    delete fileDialog;
}

/**
 * @brief ParameterSetting_Widget::initSaveFileDialog 初始化配置保存文件对话框
 * @return
 */
QFileDialog *  ShowChart_module_Widget::initSaveFileDialog()
{
    QFileDialog *fileDialog = new QFileDialog();
    fileDialog->setOption(QFileDialog::DontUseNativeDialog,true); // 不使用本地的文件对话框

    QLabel *lblWidth = new QLabel("Width",fileDialog);  // 宽度
    QSpinBox *spbWidth = new QSpinBox(fileDialog);
    spbWidth->setMinimum(10);
    spbWidth->setMaximum(16777215);
    spbWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spbWidth->setValue(ui->chart_plot->width());

    QLabel *lblHeight = new QLabel("Height",fileDialog);// 高度
    QSpinBox *spbHeight  = new QSpinBox(fileDialog);
    spbHeight->setMinimum(10);
    spbHeight->setMaximum(16777215);
    spbHeight->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spbHeight->setValue(ui->chart_plot->height());

    QLabel *lblScale = new QLabel("Scale",fileDialog);  // 缩放比例
    QDoubleSpinBox *spbScale  = new QDoubleSpinBox(fileDialog);
    spbScale->setMinimum(0);
    spbScale->setMaximum(16777215);
    spbScale->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spbScale->setValue(1);

    QHBoxLayout *hlayout = new QHBoxLayout(); // 新建布局图层
    hlayout->addWidget(lblWidth);             // 添加Widget
    hlayout->addWidget(spbWidth);
    hlayout->addWidget(lblHeight);
    hlayout->addWidget(spbHeight);
    hlayout->addWidget(lblScale);
    hlayout->addWidget(spbScale);
    hlayout->setSpacing(3);// 间隔为0

    QWidget *pWidget = new QWidget(fileDialog);
    QLabel *lblImagesSize = new QLabel("ImagesSize:",fileDialog); // 图像大小
    fileDialog->layout()->addWidget(lblImagesSize);// 添加Widget,整体添加两个Widget, pWidget另外包含4个Widget
    fileDialog->layout()->addWidget(pWidget);      //
    pWidget->setLayout(hlayout);

    fileDialog->setWindowTitle(tr("保存图像"));           // 对话框标题
    fileDialog->setAcceptMode(QFileDialog::AcceptSave); // 保存模式
    fileDialog->setViewMode(QFileDialog::List);         // 列表显示
    fileDialog->setLabelText(QFileDialog::Accept,"保存");// 按钮文本
    fileDialog->setLabelText(QFileDialog::Reject,"取消");

    fileDialog->setDirectory(".");
    QString filters="png(*.png);;jpg(*.jpg);;bmp(*.bmp);;pdf(*.pdf)";// 过滤类型
    fileDialog->setNameFilter(filters);
    fileDialog->setDirectory(qApp->applicationDirPath());// 默认路径
    return fileDialog;
}


void ShowChart_module_Widget::draw(qint32 GraphNumber, double data)
{
    qDebug()<<data<<endl;

    ui->chart_plot->graph(GraphNumber)->addData(x,data);
    if(x<m_pWidget->displayWith)
        ui->chart_plot->rescaleAxes(true);
    else
    {
        ui->chart_plot->xAxis->setRange(x, m_pWidget->displayWith, Qt::AlignRight);
        ui->chart_plot->yAxis->rescale(true);
    }

    ui->chart_plot->replot(QCustomPlot::rpQueuedReplot);
    x++;
}

//设置框选放大
void ShowChart_module_Widget::actionselectZoom(bool c)
{
    if(c){
        ui->chart_plot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
    }else{
        ui->chart_plot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
    }
}

/**
 * @brief ShowChart_module_Widget::actionCoorTips 坐标显示
 * @param checked
 */
void ShowChart_module_Widget::actionCoorTips(bool checked)
{
    if(numGraphs == 0) return;
    if(checked){
        QPen linesPen(Qt::yellow, 1, Qt::SolidLine);
        lineV = new QCPItemStraightLine(ui->chart_plot);//垂直线
        lineV->setLayer("overlay");
        lineV->setPen(linesPen);
        lineV->setClipToAxisRect(true);
        lineV->setVisible(true);

        for(qint32 i=0; i<numGraphs;i++){
            QCPItemTracer *tracer = new QCPItemTracer(ui->chart_plot);
            tracer->setStyle(QCPItemTracer::tsCircle);
            tracer->setPen(QColor(Qt::red));
            tracer->setBrush(Qt::NoBrush);
            tracer->position->setTypeX(QCPItemPosition::ptPlotCoords);
            tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
            tracer->setSize(6);
            tracer->setVisible(true);
            tracerPointArray<<tracer;

            QCPItemText *label = new QCPItemText(ui->chart_plot);
//            label->setLayer("overlay");
            label->setClipToAxisRect(false);
            label->setPadding(QMargins(6, 6, 6, 6));
            label->setBrush(QColor(20,20,20,200));         //  颜色填充,半透明
//            label->setPen();       // 边框颜色
            label->position->setParentAnchor(tracer->position);
            label->setColor(ui->chart_plot->graph(i)->pen().color());  // 字体颜色与曲线颜色一致
            label->setText("test");
            label->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
            label->setVisible(true);
            lblGraph<<label;
        }
        connect(ui->chart_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(slots_mouseMove(QMouseEvent*)));
    }else{
        ui->chart_plot->disconnect(SIGNAL(mouseMove(QMouseEvent*)));

        lineV->setVisible(false);
        ui->chart_plot->removeItem(lineV);

        foreach( QCPItemText *label, lblGraph ){
            label->setVisible(false);
            ui->chart_plot->removeItem(label);
        }
        foreach( QCPItemTracer *tracer, tracerPointArray ){
            tracer->setVisible(false);
            ui->chart_plot->removeItem(tracer);
        }

        lblGraph.clear();
        tracerPointArray.clear();
        ui->chart_plot->replot(QCustomPlot::rpQueuedReplot);
    }
}

/**
 * @brief ShowChart_module_Widget::slots_mouseMove 鼠标移动事件
 * @param event
 */
void ShowChart_module_Widget::slots_mouseMove(QMouseEvent* event)
{
 //获取鼠标坐标点
    qint32 x_pos = event->pos().x();

// 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
// coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
    qint32 x_val = qRound(ui->chart_plot->xAxis->pixelToCoord(x_pos));

// 然后打印在界面上
    lineV->point1->setCoords(x_val, 0);
    lineV->point2->setCoords(x_val, 2);

    double posAtGraph=0;
    qint32 i=0;
    foreach( auto tracer, tracerPointArray ){
        /* 跟随点 */
        auto iter = ui->chart_plot->graph(i)->data()->findBegin(x_val+1);
        posAtGraph = iter->mainValue();
        tracer->position->setCoords( x_val, posAtGraph);

        /* 坐标说明 */
        auto label = lblGraph.at(i);
        label->position->setCoords( 5, 0);
        label->setText(tr("X:%1 , Y:%2").arg(x_val).arg(posAtGraph));
        i++;
    }
    ui->chart_plot->replot(QCustomPlot::rpQueuedReplot);
}

ShowChart_module_Widget::~ShowChart_module_Widget()
{
    delete ui;
}
