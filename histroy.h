#ifndef HISTROY_H
#define HISTROY_H

#include <QMainWindow>
#include <QDateTime>
namespace Ui {
class Histroy;
}

class Histroy : public QMainWindow
{
    Q_OBJECT

public:
    int numberCount;
    int curPage;
    int pageCount;
    struct historyItem
    {
        QDateTime utime;
        QString input;
        QString output;
        int id;
    };
    QVector<historyItem> inShow;
    explicit Histroy(QWidget *parent = 0);
    ~Histroy();

private slots:
    void on_pageUp_clicked();
    void on_pageDown_clicked();
    void on_clearOne_clicked();
    void on_clearAll_clicked();
    void init();

private:
    Ui::Histroy *ui;
    void setEmpty(int i);
};

#endif // HISTROY_H
