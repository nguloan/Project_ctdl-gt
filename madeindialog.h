#ifndef MADEINDIALOG_H
#define MADEINDIALOG_H

#include <QWidget>
#include<QDialog>
#include"madein.h"
#include<QMessageBox>
#include<QLineEdit>
#include<QPixmap>
#include<QListWidget>
#include<Products.h>


namespace Ui {
class madeinDialog;
}


class madeinDialog : public QDialog
{
    Q_OBJECT
public:
    explicit madeinDialog(QWidget *parent = nullptr);
    ~madeinDialog();
    madein DATA;

private:
    Ui::madeinDialog *ui;
    QListWidgetItem * itemSelect;
    QString strSelect;
    QLineEdit* newEdit;
    QDialog* editDialog,*addDialog;
    void print();
private slots:
    void add();
    void remove();
    void edit();
    void select(QListWidgetItem* temp);

};

#endif // MADEINDIALOG_H
