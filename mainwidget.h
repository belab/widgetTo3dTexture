#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QGraphicsScene;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QGraphicsScene* scene, QWidget *parent = 0);
    ~MainWidget();
    
private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
