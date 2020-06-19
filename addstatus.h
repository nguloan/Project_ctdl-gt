#ifndef ADDSTATUS_H
#define ADDSTATUS_H
#include "status.h"
#include <QDialog>
#include "purchasehst.h"
#include <QLocale>
namespace Ui {
class Addstatus;
}

class Addstatus : public QDialog
{
    Q_OBJECT

public:
    explicit Addstatus(QWidget *parent = nullptr);
    ~Addstatus();
    status sttlist;
    purchasehst phlist;
    void printtablestt();
    void renewtbstt();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_deletebt_clicked();

private:
    Ui::Addstatus *ui;
};

#endif // ADDSTATUS_H
