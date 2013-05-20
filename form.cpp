#include "form.h"
#include "glwidget.h"
#include "ui_form.h"

#include <QMouseEvent>
#include <QPainter>

Form::Form(QWidget *parent, GlWidget *widget) :
    QWidget(parent),
    glWidget( widget ),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_1_clicked(bool)
{
    ui->label_1->setText("clicked");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("");
}

void Form::on_pushButton_2_clicked(bool)
{
    ui->label_1->setText("");
    ui->label_2->setText("clicked");
    ui->label_3->setText("");
    ui->label_4->setText("");
}

void Form::on_pushButton_3_clicked(bool)
{
    ui->label_1->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("clicked");
    ui->label_4->setText("");
}

void Form::on_pushButton_4_clicked(bool)
{
    ui->label_1->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("clicked");
}

