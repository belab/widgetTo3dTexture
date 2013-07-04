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
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    setMouseTracking(true);
    //setAttribute( Qt::WA_TranslucentBackground );
    //setWindowOpacity(0.01f);
}

Form::~Form()
{
    delete ui;
}

void Form::resizeEvent(QResizeEvent * /* event */)
{
    QRegion maskedRegion(rect());
    setMask(maskedRegion);
}
void Form::on_pushButton_1_clicked(bool)
{
    ui->label_1->setText("clicked");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("");
    repaint(0,0,size().width(), size().height());
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

