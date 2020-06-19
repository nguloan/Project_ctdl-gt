#ifndef CARTWIDGET_H
#define CARTWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QMessageBox>
#include<QPushButton>
#include<QCheckBox>
#include<cart.h>
#include<QTextEdit>
#include"Products.h"
#include<QLineEdit>
#include<QSignalMapper>
#include<QLocale>

namespace Ui {
class cartWidget;
}

class cartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit cartWidget(QString usrname,QWidget *parent = nullptr);
    ~cartWidget();
    QString username;
private:
    Ui::cartWidget *ui;
    cart Data;
   Products DataPd ;
   void printCart();
    qlonglong sum = 0;
    QLabel* Bill;
   QSignalMapper*  mapAddQuanity, * mapSubQuanity, *mapRemovePd;
   QList<QString> listProductBuy;


signals:
   void continuePay(QList<QString> listProduct);

private slots:
   void clickAdd(QWidget* contentPd);
   void clickSub(QWidget* contentPd);
   void clickRm(QWidget* contentPd);
   void clickSelect(QWidget* contentPd);
   void clickEditQuanity(QWidget* contentPd);

};

#endif // CARTWIDGET_H
