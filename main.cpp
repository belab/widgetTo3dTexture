#include <QApplication>
#include "glwidget.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    GlWidget w;
    w.show();
    return a.exec();
}
