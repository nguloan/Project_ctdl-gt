#ifndef LSMH_H
#define LSMH_H
#include "status.h"
#include <QWidget>
#include <purchasehst.h>
#include <QTabWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include<QTextEdit>
namespace Ui {
class lsmh;
}

class lsmh : public QWidget
{
    Q_OBJECT

public:
    explicit lsmh(QString userid,QWidget *parent = nullptr);
    ~lsmh();

private slots:
    void on_tatcabt_clicked();

    void on_dangchobt_clicked();

    void on_danggiaobt_clicked();

    void on_dagiaobt_clicked();

    void on_dahuybt_clicked();

private:
    QString username;
    Ui::lsmh *ui;
    purchasehst phlist;
    void print();
    void tatca();
    void dangcho();
    void danggiao();
    void dagiao();
    void dahuy();
};

#endif // LSMH_H
