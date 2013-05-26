//#include "glwidget.h"
#include "mainwidget.h"
#include <QApplication>
#include <QGraphicsScene>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QGraphicsScene scene;
    MainWidget w(&scene);
    w.show();
    return a.exec();
}
