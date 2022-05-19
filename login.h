#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <Qtsql/qsqlquery.h>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    QSqlDatabase *db;
    ~login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
