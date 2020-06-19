#ifndef MANAGERPD_H
#define MANAGERPD_H

#include <QWidget>
#include"Products.h"
#include<QMessageBox>
#include"branddialog.h"
#include"madeindialog.h"
#include"categorydialog.h"
#include<QPixmap>
#include"addpd.h"
#include<QTableWidget>
#include"editproduct.h"

namespace Ui {
class managerPd;
}

class managerPd : public QWidget
{
    Q_OBJECT

public:
    explicit managerPd(QWidget *parent = nullptr);
    ~managerPd();
    Products DATA;

private:
    Ui::managerPd *ui;
    void printTable();
    void refesh();
    QList<QTableWidgetItem*> ListItem;
private slots:
    void clickBrand();
    void clickMadein();
    void clickCategory();

    void on_addPd_clicked();
    void cellSelected(int nRow,int nCol);
    void on_find_textChanged(const QString &arg1);
};

#endif // MANAGERPD_H
