#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QtSql/QSqlDatabase>
#include <Qtsql/qsqlquery.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    enum status{blank,result,help};
    int userlogin(QString name,QString password);
    int userReg(QString name,QString password);
    int userId = 1;
    double resultRes;
    void updataConstDict();
    void addSinx();
    void addCosx();
    void addTanx();
    void addArcsinx();
    void addArccosx();
    void addArctanx();
    void addEx();
    void addLnx();
    void addSqrtx();
    status stu = blank;
    QMap<QString,double> constNumbers;
    QMap<QString,int> functionMap;
    QMap<QChar,int> pr;
    QString helpText;
    QString userName;
    QSqlDatabase db;
    ~MainWindow();

private slots:
    void on_num0_clicked();
    void on_num1_clicked();
    void on_num2_clicked();
    void on_num3_clicked();
    void on_num4_clicked();
    void on_num5_clicked();
    void on_num6_clicked();
    void on_num7_clicked();
    void on_num8_clicked();
    void on_num9_clicked();
    void on_dot_clicked();
    void on_add_clicked();
    void on_sub_clicked();
    void on_multiply_clicked();
    void on_div_clicked();
    void on_equal_clicked();
    void on_backSpace_clicked();
    void on_roundLeft_clicked();
    void on_roundRight_clicked();
    void on_pushButton_clicked();
    void on_actionsize_triggered();
    void on_actioncolar_triggered();
    void on_actiondenglu_triggered();
    void on_actionzhuce_triggered();
    void on_actionuser_triggered();
    void on_saveConst_clicked();
    void on_constList_clicked();
    void on_addConst_clicked();
    void on_actionyhxx_triggered();
    void on_actionauth_triggered();
    void on_function_clicked();

    void on_longCalc_clicked();

private:
    Ui::MainWindow *ui;
    double calc(QString str);
    bool eval(QStack<double> &num,QStack<QChar> &op);
    void record(QString input,QString output);
    void initFunctionMap();
    bool zeroErr = false;
};

#endif // MAINWINDOW_H
