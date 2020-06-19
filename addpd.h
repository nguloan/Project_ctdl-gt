#ifndef ADDPD_H
#define ADDPD_H

#include <QDialog>
#include<QFileDialog>
#include<QPixmap>
#include"Products.h"
#include<QMessageBox>

namespace Ui {
class addPd;
}

class addPd : public QDialog
{
    Q_OBJECT

public:
    explicit addPd(QWidget *parent = nullptr);
    ~addPd();
    Products dataPd;
     QString file,fileNew;

private:
    Ui::addPd *ui;
private slots:
    void clickAddPhoto();
    void updateCate();
    void updateKind();
    void updateBrand();
    void updateMadein();
    void on_Apply_clicked();
    void on_pushButton_clicked();
};

#endif // ADDPD_H
