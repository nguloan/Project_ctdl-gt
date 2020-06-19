#ifndef CATEGORYDIALOG_H
#define CATEGORYDIALOG_H

#include "category.h"
#include <QDialog>
#include<QMessageBox>
#include<QTableWidget>
#include<QPixmap>
#include"kind.h"
#include<QLineEdit>
#include<QMessageBox>
#include<QListWidget>
#include"Products.h"

namespace Ui {
class categoryDialog;
}


class categoryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit categoryDialog(QWidget *parent = nullptr);
    ~categoryDialog();

private:
    Ui::categoryDialog *ui;
    QListWidgetItem* selectItem, *selectItemKind;

    category DATAcate;
    kind DATAkind;
    void print();
    QString strSelect = "";
    void printKind();


private slots:
    void add();
    void remove();
    void select(QListWidgetItem *temp);
    void edit();

    void addKind();
    void removeKind();
    void selectKind(QListWidgetItem* temp);
    void editKind();
};

#endif // CATEGORYDIALOG_H
