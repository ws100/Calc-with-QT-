#include "reg.h"
#include "ui_reg.h"
#include "mainwindow.h"
#include <QMessageBox>
Reg::Reg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reg)
{
    ui->setupUi(this);
}

Reg::~Reg()
{
    delete ui;
}

void Reg::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    MainWindow *parW=(MainWindow*)parentWidget();
    if(name == "")
    {
        ui->label_3->setText("用户名不能为空");
        return;
    }
    if(password == "")
    {
        ui->label_3->setText("密码不能为空");
        return;
    }
    int regStatus = parW->userReg(name,password);
    if(regStatus == -2)ui->label_3->setText("网路连接失败");
    else if(regStatus == -1)ui->label_3->setText("用户已存在");
    else
    {
        QMessageBox::information(this,"提示","注册成功");
        delete this;
    }

}
