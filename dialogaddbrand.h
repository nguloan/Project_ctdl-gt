#ifndef DIALOGADDBRAND_H
#define DIALOGADDBRAND_H

#include <QDialog>
#include"brand.h"
#include<QMessageBox>
#include<QLineEdit>

namespace Ui {
class dialogAddBrand;
}

class dialogAddBrand : public QDialog
{
    Q_OBJECT
    brand DataBrand;

public:
    explicit dialogAddBrand(QWidget *parent = nullptr);
    ~dialogAddBrand();

private:
    Ui::dialogAddBrand *ui;
    QLineEdit* newBrand;
private slots:
    void add();
};

#endif // DIALOGADDBRAND_H
