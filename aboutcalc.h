#ifndef ABOUTCALC_H
#define ABOUTCALC_H

#include <QMainWindow>

namespace Ui {
class AboutCalc;
}

class AboutCalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit AboutCalc(QWidget *parent = 0);
    ~AboutCalc();

private:
    Ui::AboutCalc *ui;
};

#endif // ABOUTCALC_H
