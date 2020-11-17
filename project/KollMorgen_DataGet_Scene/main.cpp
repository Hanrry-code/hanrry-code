#include "main_scene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main_Scene w;
    w.show();

    return a.exec();
}
