#ifndef BRANDDIALOG_H
#define BRANDDIALOG_H
#include "brand.h"
#include <QDialog>
#include<QMessageBox>
#include<QTableWidget>
#include<QPixmap>
#include<QLineEdit>
#include"dialogaddbrand.h"
#include<QListWidget>
#include<Products.h>


namespace Ui {
class brandDialog;
}

class brandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit brandDialog(QWidget *parent = nullptr);
    ~brandDialog();
    brand DATA;
    void print();
private:
    Ui::brandDialog *ui;
    QListWidgetItem * itemSelect;
    QString strSelect;
    QLineEdit* newEdit;
    QDialog* editDialog;
private slots:
    void add();
    void remove();
    void edit();
    void select(QListWidgetItem* temp);

};

#endif // BRANDDIALOG_H
