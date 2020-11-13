#include "axes.h"
#include "widget.h"
#include "ui_widget.h"

#include <QTextStream>
// Example function
class Rosenbrock : public Function
{
public:

    Rosenbrock(GridPlot& pw)
        :Function(pw)
    {
    }

    //设置z与x，y的关系
    double operator()(double x, double y)
    {
        //        return log10((1-x)*(1-x) + 1 * (y - x*x)*(y - x*x));
        return x;
    }
};
void Widget::init_qwt3D()
{
    QGridLayout *grid = new QGridLayout(ui->frame);
    plot = new GridPlot(ui->frame);
    grid->addWidget(plot,0,0);
    plot->setZoom(0.95);//占屏比
    plot->setRotation(30,0,30);
    plot->coordinates()->setGridLines(true,true);

    plot->setCoordinateStyle(FRAME);

    rosenbrock = new Rosenbrock(*plot);
    rosenbrock->setMesh(31,33);//设置x,y的精度
    rosenbrock->setDomain(-200,200,-200,200);//设置x最小,最大,y最小,最大
    //    rosenbrock->setMinZ(-200);
    rosenbrock->create();

    //设置刻度
    for (unsigned i=0; i!=plot->coordinates()->axes.size(); ++i)
    {
        plot->coordinates()->axes[i].setMajors(5);
        plot->coordinates()->axes[i].setMinors(0);
        plot->coordinates()->axes[i].setLabelColor(RGBA(0,0,0));
    }

    //    plot->setTitle("Rosenbrock");
    plot->setMeshLineWidth(1);
    plot->coordinates()->setGridLinesColor(RGBA(0.5,0.5,0.5));
    plot->coordinates()->setLineWidth(1);
    plot->coordinates()->setNumberColor(RGBA(0,0,0));
    plot->coordinates()->setNumberFont("Courier",10);
    //    plot->coordinates()->setColor(1,1,0);
    //    plot->setTitleFont("Courier",11);
    //    plot->coordinates()->setLabelFont("Courier",12, QFont::Bold);

    plot->coordinates()->axes[X1].setLabelString("X");
    plot->coordinates()->axes[Y1].setLabelString("Y");
    plot->coordinates()->axes[Z1].setLabelString("Z");
    plot->coordinates()->axes[X2].setLabelString("X");
    plot->coordinates()->axes[Y2].setLabelString("Y");
    plot->coordinates()->axes[Z2].setLabelString("Z");
    plot->coordinates()->axes[X3].setLabelString("X");
    plot->coordinates()->axes[Y3].setLabelString("Y");
    plot->coordinates()->axes[Z3].setLabelString("Z");
    plot->coordinates()->axes[X4].setLabelString("X");
    plot->coordinates()->axes[Y4].setLabelString("Y");
    plot->coordinates()->axes[Z4].setLabelString("Z");


    plot->coordinates()->setLineSmooth(true);//设置线平滑

    tics = plot->coordinates()->axes[X1].majors();

    //    resetTics();
    //    customScale();
    //    plot->setPolygonOffset(10);

    setGrid(Qwt3D::BACK);
    setGrid(Qwt3D::FLOOR);
    setGrid(Qwt3D::RIGHT);

}


void Widget::init_qss()
{
    QApplication::setStyle(QStyleFactory::create("fusion"));// fusion 风格
    QFile file(":/qss/Ubuntu.css");
    if (!file.open(QFile::ReadOnly)){  // 打开文件
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString qss = in.readAll();        // 读取数据
    qApp->setStyleSheet(qss);    // 应用
    file.close();
}


void Widget::init_Joint_CmdPos()
{
    line_Joint_CmdPos[0] = ui->line_J1;
    line_Joint_CmdPos[1] = ui->line_J2;
    line_Joint_CmdPos[2] = ui->line_J3;
    line_Joint_CmdPos[3] = ui->line_J4;
    line_Joint_CmdPos[4] = ui->line_J5;
    line_Joint_CmdPos[5] = ui->line_J6;
}
void Widget::init_Joint_CmdVel()
{
    line_Car_CmdVel[0] = ui->line_Joint_V1;
    line_Car_CmdVel[1] = ui->line_Joint_V2;
    line_Car_CmdVel[2] = ui->line_Joint_V3;
    line_Car_CmdVel[3] = ui->line_Joint_V4;
    line_Car_CmdVel[4] = ui->line_Joint_V5;
    line_Car_CmdVel[5] = ui->line_Joint_V6;
}

void Widget::init_Car_CmdPos()
{
    line_Car_CmdPos[0] = ui->line_X;
    line_Car_CmdPos[1] = ui->line_Y;
    line_Car_CmdPos[2] = ui->line_Z;
    line_Car_CmdPos[3] = ui->line_W;
    line_Car_CmdPos[4] = ui->line_P;
    line_Car_CmdPos[5] = ui->line_R;
}

void Widget::init_Car_CmdVel()
{
    line_Joint_CmdVel[0] = ui->line_V1;
    line_Joint_CmdVel[1] = ui->line_V2;
    line_Joint_CmdVel[2] = ui->line_V3;
    line_Joint_CmdVel[3] = ui->line_V4;
    line_Joint_CmdVel[4] = ui->line_V5;
    line_Joint_CmdVel[5] = ui->line_V6;

}
void Widget::resetTics()
{
    plot->setTitle("");
    plot->coordinates()->axes[X1].setMajors(5);
    plot->coordinates()->setAutoScale(true);
    plot->coordinates()->setStandardScale();
    plot->coordinates()->axes[Z2].setLabelString("Z4");
    plot->coordinates()->setGridLines(false,false,Qwt3D::FLOOR);
}

//设置比例尺
void Widget::customScale()
{
    resetTics();
    //  plot->coordinates()->axes[Z1].setScale(LOG10SCALE);
    //  plot->coordinates()->axes[Z2].setLabelString("log10(z)");
    //  plot->coordinates()->axes[Z3].setScale(LOG10SCALE);
    //  plot->coordinates()->axes[Z4].setScale(LOG10SCALE);
    //  plot->coordinates()->axes[Z4].setScale(new LogScale);
    plot->coordinates()->axes[Z1].setAutoScale(true);
    plot->coordinates()->axes[Z2].setAutoScale(true);
    plot->coordinates()->axes[Z3].setAutoScale(true);
    plot->coordinates()->axes[Z4].setAutoScale(true);
    plot->coordinates()->setGridLines(true,true,Qwt3D::BACK);//设置网格线
    plot->coordinates()->setGridLines(true,true,Qwt3D::FLOOR);//设置网格线

    plot->update();
}
void Widget::setGrid(Qwt3D::SIDE s)
{
    if (!plot)
        return;

    int sum = plot->coordinates()->grids();
    sum |= s;
    // sum &= ~s;

    plot->coordinates()->setGridLines(sum!=Qwt3D::NOSIDEGRID, sum!=Qwt3D::NOSIDEGRID, sum);
    plot->update();
}
void Widget::setStandardView()
{
    plot->setRotation(30,0,30);
    plot->setViewportShift(0.05,0);
    plot->setScale(1,1,1);
    plot->setZoom(0.95);
}

