#ifndef REG_H
#define REG_H

#include <QMainWindow>

namespace Ui {
class Reg;
}

class Reg : public QMainWindow
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = 0);
    ~Reg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Reg *ui;
};

#endif // REG_H
