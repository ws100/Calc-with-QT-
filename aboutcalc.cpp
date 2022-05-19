#include "aboutcalc.h"
#include "ui_aboutcalc.h"

AboutCalc::AboutCalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutCalc)
{
    ui->setupUi(this);
}

AboutCalc::~AboutCalc()
{
    delete ui;
}
