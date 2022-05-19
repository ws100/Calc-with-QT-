#include "functioninput.h"
#include "ui_functioninput.h"

FunctionInput::FunctionInput(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FunctionInput)
{
    ui->setupUi(this);
    parw = (MainWindow*)parentWidget();
}

FunctionInput::~FunctionInput()
{
    delete ui;
}

void FunctionInput::on_sinxbtn_clicked()
{
    parw->addSinx();
}

void FunctionInput::on_cosxbtn_clicked()
{
    parw->addCosx();
}

void FunctionInput::on_tanxbtn_clicked()
{
    parw->addTanx();
}

void FunctionInput::on_arcsinxbtn_clicked()
{
    parw->addArcsinx();
}

void FunctionInput::on_arccosxbtn_clicked()
{
    parw->addArccosx();
}

void FunctionInput::on_arctanxbtn_clicked()
{
    parw->addArctanx();
}

void FunctionInput::on_exbtn_clicked()
{
    parw->addEx();
}

void FunctionInput::on_lnxbtn_clicked()
{
    parw->addLnx();
}

void FunctionInput::on_sqrtbtn_clicked()
{
    parw->addSqrtx();
}
