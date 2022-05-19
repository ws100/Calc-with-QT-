#include <QtSql/QSqlDatabase>
#include <Qtsql/qsqlquery.h>
#include <QInputDialog>
#include <QVector>
#include "consttable.h"
#include "ui_consttable.h"
#include "mainwindow.h"
#include <QMessageBox>
struct constNumber
{
    QString name;
    double value;
};
void ConstTable::init()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    query.prepare("select count(*) from userconst where userid = :sname");
    query.bindValue(":sname",parW->userId);
    query.exec();
    if(query.next())
    {
       userConstCount = query.value("count(*)").toInt();
       userPageCount = userConstCount/15+1;
       userCurPage = 1;
    }
    ui->label_3->setText("共 "+QString::number(userConstCount)+" 条数据 第 "+QString::number(userCurPage)+" 页 共 "+QString::number(userPageCount)+" 页");
    query.prepare("select count(*) from globalconst");
    query.exec();
    if(query.next())
    {
       globalConstCount = query.value("count(*)").toInt();
       globalPageCount = globalConstCount/15+1;
       globalCurPage = 1;
    }
    ui->label_4->setText("共 "+QString::number(globalConstCount)+" 条数据 第 "+QString::number(globalCurPage)+" 页 共 "+QString::number(globalPageCount)+" 页");
    QVector<constNumber> userNumberTemp;
    query.prepare("select * from userconst where userid = :sname LIMIT 0,15");
    query.bindValue(":sname",parW->userId);
    query.exec();
    while(query.next())
    {
        userNumberTemp.append({query.value("constname").toString(),query.value("number").toDouble()});
    }
    for(int i = 0;i<15;i++)
    {
        if(i<userNumberTemp.size())
        {
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1),1000);
            ui->tableWidget->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(userNumberTemp[i].name,1001);
            ui->tableWidget->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(QString::number(userNumberTemp[i].value),1002);
            ui->tableWidget->setItem(i,2,itemIdx3);
        }
        else
        {
            setUserEmpty(i);
        }
    }
    QVector<constNumber> globalNumberTemp;
    query.prepare("select * from globalconst LIMIT 0,15");
    query.exec();
    while(query.next())
    {
        globalNumberTemp.append({query.value("constname").toString(),query.value("number").toDouble()});
    }
    for(int i = 0;i<15;i++)
    {
        if(i<globalNumberTemp.size())
        {
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1),1000);
            ui->tableWidget_2->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(globalNumberTemp[i].name,1001);
            ui->tableWidget_2->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(QString::number(globalNumberTemp[i].value),1002);
            ui->tableWidget_2->setItem(i,2,itemIdx3);
        }
        else
        {
            setGlobalEmpty(i);
        }
    }
}
ConstTable::ConstTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConstTable)
{
    ui->setupUi(this);
    init();
}
void ConstTable::setUserEmpty(int i)
{
    QTableWidgetItem *itemIdx1 = new QTableWidgetItem("");
    ui->tableWidget->setItem(i,0,itemIdx1);
    QTableWidgetItem *itemIdx2 = new QTableWidgetItem("");
    ui->tableWidget->setItem(i,1,itemIdx2);
    QTableWidgetItem *itemIdx3 = new QTableWidgetItem("");
    ui->tableWidget->setItem(i,2,itemIdx3);
}
void ConstTable::setGlobalEmpty(int i)
{
    QTableWidgetItem *itemIdx1 = new QTableWidgetItem("");
    ui->tableWidget_2->setItem(i,0,itemIdx1);
    QTableWidgetItem *itemIdx2 = new QTableWidgetItem("");
    ui->tableWidget_2->setItem(i,1,itemIdx2);
    QTableWidgetItem *itemIdx3 = new QTableWidgetItem("");
    ui->tableWidget_2->setItem(i,2,itemIdx3);
}
ConstTable::~ConstTable()
{
    delete ui;
}
void ConstTable::on_userUp_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    if(userCurPage == 1)return;
    userCurPage--;
    QVector<constNumber> userNumberTemp;
    query.prepare("select * from userconst where userid = :sname LIMIT :sint,15");
    query.bindValue(":sname",parW->userId);
    query.bindValue(":sint",(userCurPage-1)*15);
    query.exec();
    while(query.next())
    {
        userNumberTemp.append({query.value("constname").toString(),query.value("number").toDouble()});
    }
    for(int i = 0;i<15;i++)
    {
        if(i<userNumberTemp.size())
        {
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1+(userCurPage-1)*15),1000);
            ui->tableWidget->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(userNumberTemp[i].name,1001);
            ui->tableWidget->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(QString::number(userNumberTemp[i].value),1002);
            ui->tableWidget->setItem(i,2,itemIdx3);
        }
        else
        {
            setUserEmpty(i);
        }
    }
    ui->label_3->setText("共 "+QString::number(userConstCount)+" 条数据 第 "+QString::number(userCurPage)+" 页 共 "+QString::number(userPageCount)+" 页");
}

void ConstTable::on_userDown_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    if(userCurPage == userPageCount)return;
    userCurPage++;
    QVector<constNumber> userNumberTemp;
    query.prepare("select * from userconst where userid = :sname LIMIT :sint,15");
    query.bindValue(":sname",parW->userId);
    query.bindValue(":sint",(userCurPage-1)*15);
    query.exec();
    while(query.next())
    {
        userNumberTemp.append({query.value("constname").toString(),query.value("number").toDouble()});
    }
    for(int i = 0;i<15;i++)
    {
        if(i<userNumberTemp.size())
        {
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1+(userCurPage-1)*15),1000);
            ui->tableWidget->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(userNumberTemp[i].name,1001);
            ui->tableWidget->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(QString::number(userNumberTemp[i].value),1002);
            ui->tableWidget->setItem(i,2,itemIdx3);
        }
        else
        {
            setUserEmpty(i);
        }
    }
    ui->label_3->setText("共 "+QString::number(userConstCount)+" 条数据 第 "+QString::number(userCurPage)+" 页 共 "+QString::number(userPageCount)+" 页");
}


void ConstTable::on_globalUp_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    if(globalCurPage == 1)return;
    globalCurPage--;
    QVector<constNumber> globalNumberTemp;
    query.prepare("select * from globalconst LIMIT :sint,15");
    query.bindValue(":sint",(globalCurPage-1)*15);
    query.exec();
    while(query.next())
    {
        globalNumberTemp.append({query.value("constname").toString(),query.value("number").toDouble()});
    }
    for(int i = 0;i<15;i++)
    {
        if(i<globalNumberTemp.size())
        {
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1)+(globalCurPage-1)*15,1000);
            ui->tableWidget->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(globalNumberTemp[i].name,1001);
            ui->tableWidget->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(QString::number(globalNumberTemp[i].value),1002);
            ui->tableWidget->setItem(i,2,itemIdx3);
        }
        else
        {
            setGlobalEmpty(i);
        }
    }
    ui->label_4->setText("共 "+QString::number(globalConstCount)+" 条数据 第 "+QString::number(globalCurPage)+" 页 共 "+QString::number(globalPageCount)+" 页");
}

void ConstTable::on_globalDown_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    if(globalCurPage == globalPageCount)return;
    globalCurPage++;
    QVector<constNumber> globalNumberTemp;
    query.prepare("select * from globalconst LIMIT :sint,15");
    query.bindValue(":sint",(globalCurPage-1)*15);
    query.exec();
    while(query.next())
    {
        globalNumberTemp.append({query.value("constname").toString(),query.value("number").toDouble()});
    }
    for(int i = 0;i<15;i++)
    {
        if(i<globalNumberTemp.size())
        {
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1)+(globalCurPage-1)*15,1000);
            ui->tableWidget->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(globalNumberTemp[i].name,1001);
            ui->tableWidget->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(QString::number(globalNumberTemp[i].value),1002);
            ui->tableWidget->setItem(i,2,itemIdx3);
        }
        else
        {
            setGlobalEmpty(i);
        }
    }
    ui->label_4->setText("共 "+QString::number(globalConstCount)+" 条数据 第 "+QString::number(globalCurPage)+" 页 共 "+QString::number(globalPageCount)+" 页");
}

void ConstTable::on_updateUserConst_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    if(parW->userId == -1)
    {
        QMessageBox::information(this,"用户信息","未登录");
        return;
    }
    bool ok;
    QString text = QInputDialog::getText(this,"修改常数","输入常数的名称",QLineEdit::Normal,"",&ok);
    if(ok&!text.isEmpty())
    {
        QSqlQuery query=QSqlQuery(parW->db);
        query.prepare("select * from userconst where constname = :sname and userid = :sid");
        query.bindValue(":sname",text);
        query.bindValue(":sid",parW->userId);
        query.exec();
        if(!query.next())
        {
            QMessageBox::information(this,"常数存储","常数不存在");
            return;
        }
        double res = QInputDialog::getDouble(this,"修改常数","修改后的值",0.0,-2147483647,2147483647,5,&ok);
        if(ok)
        {
            QString sql = "update userconst set number = :sdouble where constname = '"+text+"' and userid = :sid";
            query.prepare(sql);
            query.bindValue(":sid",parW->userId);
            query.bindValue(":sdouble",res);
            query.exec();
            parW->constNumbers[text] = res;
            QMessageBox::information(this,"修改存储","修改成功");
            init();
        }
    }
    else
    {
        QMessageBox::information(this,"常数存储","无效输入");
    }
}

void ConstTable::on_deleteUserConst_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    if(parW->userId == -1)
    {
        QMessageBox::information(this,"用户信息","未登录");
        return;
    }
    bool ok;
    QString text = QInputDialog::getText(this,"删除常数","输入常数的名称",QLineEdit::Normal,"",&ok);
    if(ok&!text.isEmpty())
    {
        QSqlQuery query=QSqlQuery(parW->db);
        query.prepare("select * from userconst where constname = :sname and userid = :sid");
        query.bindValue(":sname",text);
        query.bindValue(":sid",parW->userId);
        query.exec();
        if(!query.next())
        {
            QMessageBox::information(this,"删除常数","常数不存在");
            return;
        }
        QString sql = "delete from userconst where constname = '"+text+"' and userid = :sid";
        query.prepare(sql);
        query.bindValue(":sid",parW->userId);
        query.exec();
        QMessageBox::information(this,"删除常数","删除成功");
        parW->constNumbers.remove(text);
        parW->updataConstDict();
        init();
    }
    else
    {
        QMessageBox::information(this,"删除常数","无效输入");
    }
}

void ConstTable::on_updateGlobalConst_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    if(parW->userId == -1)
    {
        QMessageBox::information(this,"用户信息","未登录");
        return;
    }
    if(parW->userId != 1)
    {
        QMessageBox::information(this,"用户信息","非root用户不能修改全局常数");
        return;
    }

    bool ok;
    double tres;
    QString text = QInputDialog::getText(this,"修改常数","输入常数的名称",QLineEdit::Normal,"",&ok);
    if(ok&!text.isEmpty())
    {
        QSqlQuery query=QSqlQuery(parW->db);
        query.prepare("select * from globalconst where constname = :sname");
        query.bindValue(":sname",text);
        query.exec();
        if(query.next())
        {
            tres = query.value("number").toDouble();

        }
        else
        {
            QMessageBox::information(this,"常数存储","常数不存在");
            return;
        }
        double res = QInputDialog::getDouble(this,"修改常数","修改后的值",0.0,-2147483647,2147483647,5,&ok);
        if(ok)
        {
            QString sql = "update globalconst set number = :sdouble where constname = '"+text+"'";
            query.prepare(sql);
            query.bindValue(":sdouble",res);
            query.exec();
            if(parW->constNumbers[text] == tres)parW->constNumbers[text] = res;
            QMessageBox::information(this,"修改存储","修改成功");
            init();
        }
    }
    else
    {
        QMessageBox::information(this,"常数存储","无效输入");
    }
}

void ConstTable::on_deleteGlobalConst_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    if(parW->userId == -1)
    {
        QMessageBox::information(this,"用户信息","未登录");
        return;
    }
    if(parW->userId != 1)
    {
        QMessageBox::information(this,"用户信息","非root用户不能修改全局常数");
        return;
    }
    bool ok;
    double tres;
    QString text = QInputDialog::getText(this,"删除常数","输入常数的名称",QLineEdit::Normal,"",&ok);
    if(ok&!text.isEmpty())
    {
        QSqlQuery query=QSqlQuery(parW->db);
        query.prepare("select * from globalconst where constname = :sname");
        query.bindValue(":sname",text);
        query.exec();
        if(query.next())
        {
            tres = query.value("number").toDouble();
        }
        else
        {
            QMessageBox::information(this,"删除常数","常数不存在");
            return;
        }
        QString sql = "delete from globalconst where constname = '"+text+"'";
        query.prepare(sql);
        query.exec();
        QMessageBox::information(this,"删除常数","删除成功");
        if(parW->constNumbers[text] == tres)parW->constNumbers.remove(text);
        init();
    }
    else
    {
        QMessageBox::information(this,"删除常数","无效输入");
    }
}
