#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
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
    MainWindow *parW=(MainWindow*)parentWidget();
    int loginStatus = parW->userlogin(name,password);
    if(loginStatus == 0)ui->label_3->setText("用户不存在");
    else if(loginStatus == -1)ui->label_3->setText("密码错误");
    else if(loginStatus == -2)ui->label_3->setText("网路连接失败");
    else
    {
        QMessageBox::information(this,"提示","登录成功");
        delete this;
    }
}
