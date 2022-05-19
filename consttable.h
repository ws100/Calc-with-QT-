#ifndef CONSTTABLE_H
#define CONSTTABLE_H

#include <QMainWindow>

namespace Ui {
class ConstTable;
}

class ConstTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConstTable(QWidget *parent = 0);
    int userConstCount;
    int userPageCount;
    int userCurPage;
    int globalConstCount;
    int globalPageCount;
    int globalCurPage;
    void setUserEmpty(int i);
    void setGlobalEmpty(int i);
    ~ConstTable();

private slots:
    void on_userUp_clicked();
    void on_userDown_clicked();
    void on_globalUp_clicked();
    void on_globalDown_clicked();
    void on_updateUserConst_clicked();
    void on_deleteUserConst_clicked();
    void on_updateGlobalConst_clicked();
    void on_deleteGlobalConst_clicked();
    void init();
private:
    Ui::ConstTable *ui;
};

#endif // CONSTTABLE_H
