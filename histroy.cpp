#include <QtSql/QSqlDatabase>
#include <Qtsql/qsqlquery.h>
#include <QVector>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include "histroy.h"
#include "ui_histroy.h"
#include "mainwindow.h"

void Histroy::init()
{
    inShow.clear();
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    query.prepare("select count(*) from history where userid = :sname");
    query.bindValue(":sname",parW->userId);
    query.exec();
    if(query.next())
    {
        numberCount = query.value("count(*)").toInt();
        pageCount = numberCount/15+1;
        curPage = 1;
    }
    ui->status->setText("共 "+QString::number(numberCount)+" 条数据 第 "+QString::number(curPage)+" 页 共 "+QString::number(pageCount)+" 页");
    QVector<historyItem> histroyItems;
    query.prepare("select * from history where userid = :sname LIMIT 0,15");
    query.bindValue(":sname",parW->userId);
    query.exec();
    while(query.next())
    {
        histroyItems.append({query.value("time").toDateTime(),query.value("input").toString(),query.value("output").toString(),query.value("id").toInt()});
    }
    qDebug()<<histroyItems.size();
    for(int i = 0;i<15;i++)
    {
        if(i<histroyItems.size())
        {
            inShow.append(histroyItems[i]);
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1),1000);
            ui->tableWidget->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(histroyItems[i].utime.toString("yyyy-MM-dd hh:mm:ss"),1001);
            ui->tableWidget->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(histroyItems[i].input,1002);
            ui->tableWidget->setItem(i,2,itemIdx3);
            QTableWidgetItem *itemIdx4 = new QTableWidgetItem(histroyItems[i].output,1003);
            ui->tableWidget->setItem(i,3,itemIdx4);
        }
        else
        {
            setEmpty(i);
        }
    }
}

void Histroy::setEmpty(int i)
{
    QTableWidgetItem *itemIdx1 = new QTableWidgetItem("");
    ui->tableWidget->setItem(i,0,itemIdx1);
    QTableWidgetItem *itemIdx2 = new QTableWidgetItem("");
    ui->tableWidget->setItem(i,1,itemIdx2);
    QTableWidgetItem *itemIdx3 = new QTableWidgetItem("");
    ui->tableWidget->setItem(i,2,itemIdx3);
    QTableWidgetItem *itemIdx4 = new QTableWidgetItem("");
    ui->tableWidget->setItem(i,3,itemIdx4);
}

Histroy::Histroy(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Histroy)
{
    ui->setupUi(this);
    init();
}

Histroy::~Histroy()
{
    delete ui;
}



void Histroy::on_pageUp_clicked()
{
    inShow.clear();
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    if(curPage == 1)return;
    curPage--;
    QVector<historyItem> historyTemp;
    query.prepare("select * from history where userid = :sname LIMIT :sint,15");
    query.bindValue(":sname",parW->userId);
    query.bindValue(":sint",(curPage-1)*15);
    query.exec();
    while(query.next())
    {
        historyTemp.append({query.value("time").toDateTime(),query.value("input").toString(),query.value("output").toString(),query.value("id").toInt()});
    }
    for(int i = 0;i<15;i++)
    {
        if(i<historyTemp.size())
        {
            inShow.append(historyTemp[i]);
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1+(curPage-1)*15),1000);
            ui->tableWidget->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(historyTemp[i].utime.toString("yyyy-MM-dd hh:mm:ss"),1001);
            ui->tableWidget->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(historyTemp[i].input,1002);
            ui->tableWidget->setItem(i,2,itemIdx3);
            QTableWidgetItem *itemIdx4 = new QTableWidgetItem(historyTemp[i].output,1003);
            ui->tableWidget->setItem(i,3,itemIdx4);
        }
        else
        {
            setEmpty(i);
        }
    }
    ui->status->setText("共 "+QString::number(numberCount)+" 条数据 第 "+QString::number(curPage)+" 页 共 "+QString::number(pageCount)+" 页");
}

void Histroy::on_pageDown_clicked()
{
    inShow.clear();
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    if(curPage == pageCount)return;
    curPage++;
    QVector<historyItem> historyTemp;
    query.prepare("select * from history where userid = :sname LIMIT :sint,15");
    query.bindValue(":sname",parW->userId);
    query.bindValue(":sint",(curPage-1)*15);
    query.exec();
    while(query.next())
    {
        historyTemp.append({query.value("time").toDateTime(),query.value("input").toString(),query.value("output").toString(),query.value("id").toInt()});
    }
    for(int i = 0;i<15;i++)
    {
        if(i<historyTemp.size())
        {
            inShow.append(historyTemp[i]);
            QTableWidgetItem *itemIdx1 = new QTableWidgetItem(QString::number(i+1+(curPage-1)*15),1000);
            ui->tableWidget->setItem(i,0,itemIdx1);
            QTableWidgetItem *itemIdx2 = new QTableWidgetItem(historyTemp[i].utime.toString("yyyy-MM-dd hh:mm:ss"),1001);
            ui->tableWidget->setItem(i,1,itemIdx2);
            QTableWidgetItem *itemIdx3 = new QTableWidgetItem(historyTemp[i].input,1002);
            ui->tableWidget->setItem(i,2,itemIdx3);
            QTableWidgetItem *itemIdx4 = new QTableWidgetItem(historyTemp[i].output,1003);
            ui->tableWidget->setItem(i,3,itemIdx4);
        }
        else
        {
            setEmpty(i);
        }
    }
    ui->status->setText("共 "+QString::number(numberCount)+" 条数据 第 "+QString::number(curPage)+" 页 共 "+QString::number(pageCount)+" 页");
}


void Histroy::on_clearOne_clicked()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    bool st[16] = {false};
    qDebug()<<"共"<<items.size();
    int count = 0;
    for(auto i:items)
    {
        int m = i->row();
        if(st[m] == false&&m<inShow.size())
        {
            st[m] = true;
            count++;
        }
    }
    if(count == 0)
    {
        QMessageBox::information(this,"删除记录","没有选择记录");
        return;
    }
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    QMessageBox::StandardButton res;
    res = QMessageBox::question(this,"删除记录","是否删除这"+QString::number(count)+"条记录",QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        for(int i = 0;i<15;i++)
        {
            if(!st[i])continue;
            int idx = inShow[i].id;
            query.prepare("delete from history where id = :sid");
            query.bindValue(":sid",idx);
            query.exec();
        }
    }
    init();
}

void Histroy::on_clearAll_clicked()
{
    MainWindow *parW=(MainWindow*)parentWidget();
    QSqlQuery query=QSqlQuery(parW->db);
    QMessageBox::StandardButton res;
    res = QMessageBox::question(this,"删除记录","是否删除全部记录",QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        query.prepare("delete from history where userid = :sid");
        query.bindValue(":sid",parW->userId);
        query.exec();
    }
    init();
}

