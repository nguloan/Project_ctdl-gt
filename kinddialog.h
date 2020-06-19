#ifndef KINDDIALOG_H
#define KINDDIALOG_H

#include "category.h"
#include"kind.h"
#include <QDialog>
#include<QMessageBox>
#include<QTableWidget>
#include<QPixmap>

namespace Ui {
class kindDialog;
}


class kindDialog : public QDialog
{
    Q_OBJECT
public:
    explicit kindDialog(QWidget *parent = nullptr);
~kindDialog();
    category DATAcate;
    kind DATAkind;
    void print();
private:
  Ui::kindDialog *ui;
  QList<QTableWidgetItem*>  LTempTable;
private slots:
  void add();
  void on_lineFind_textChanged(const QString &arg1);
  void category();
};

#endif // KINDDIALOG_H
