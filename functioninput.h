#ifndef FUNCTIONINPUT_H
#define FUNCTIONINPUT_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class FunctionInput;
}

class FunctionInput : public QMainWindow
{
    Q_OBJECT

public:
    explicit FunctionInput(QWidget *parent = 0);
    ~FunctionInput();

private slots:
    void on_sinxbtn_clicked();

    void on_cosxbtn_clicked();

    void on_tanxbtn_clicked();

    void on_arcsinxbtn_clicked();

    void on_arccosxbtn_clicked();

    void on_arctanxbtn_clicked();

    void on_exbtn_clicked();

    void on_lnxbtn_clicked();

    void on_sqrtbtn_clicked();

private:
    Ui::FunctionInput *ui;
    MainWindow *parw;
};

#endif // FUNCTIONINPUT_H
