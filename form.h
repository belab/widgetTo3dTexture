#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPoint>
class GlWidget;

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent, GlWidget* widget);
    ~Form();
    void resizeEvent(QResizeEvent *);
private slots:
    void on_pushButton_1_clicked(bool);
    void on_pushButton_2_clicked(bool);
    void on_pushButton_3_clicked(bool);
    void on_pushButton_4_clicked(bool);

private:
    Ui::Form *ui;
    GlWidget* glWidget;
    QPoint currentMouse;
};

#endif // FORM_H
