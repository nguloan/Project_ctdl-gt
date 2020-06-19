#ifndef PAYWIDGET_H
#define PAYWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include"purchasehst.h"
#include<QSignalMapper>
#include<QVBoxLayout>
#include<QRadioButton>
#include"cart.h"
#include "purchasehst.h"
#include<QPushButton>
#include<Products.h>
#include<QMessageBox>


namespace Ui {
class payWidget;
}

class payWidget : public QWidget
{
    Q_OBJECT

public:
    explicit payWidget(std::string username ,QList<QString> idProduct,QWidget *parent = nullptr);
    ~payWidget();
    QLineEdit* name,*address,*numberphone;
    std::string Username;
    purchasehst DATAph;
    cart DATAcart;
    Products DATAproduct;
    QString paymentSelect = "";
    QList<QString> listProduct;
    QList<qlonglong> listBill;
private:
    Ui::payWidget *ui;

signals:
    void payComplete();

private slots:
    void clickSelectPayment(QString text);
    void clickDone();
};

#endif // PAYWIDGET_H
