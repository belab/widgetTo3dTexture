#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QGraphicsScene>
MainWidget::MainWidget(QGraphicsScene *scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->widget->init(scene);
}

MainWidget::~MainWidget()
{
    delete ui;
}
