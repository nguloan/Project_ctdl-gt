#ifndef VIEWDETAILPRODUCT_H
#define VIEWDETAILPRODUCT_H

#include <QWidget>
#include"Products.h"
#include<QFile>
#include"cart.h"
#include<QMessageBox>

namespace Ui {
class viewDetailProduct;
}

class viewDetailProduct : public QWidget
{
    Q_OBJECT

public:
    explicit viewDetailProduct(std::string userName,std::string id,QWidget *parent = nullptr);
    ~viewDetailProduct();

private:
    Ui::viewDetailProduct *ui;
    Products DATA;
    std::string Username;
    cart DATAcart;
    QString strCate,strKind;

signals:

    void clickedAddCart();
    void clickedBack(QString str);

private slots:
    void clickAddCart();
    void clickPayNow();
    void clickBack();

};

#endif // VIEWDETAILPRODUCT_H
