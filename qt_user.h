#ifndef QT_USER_H
#define QT_USER_H

#include <QWidget>
#include "vs_user.h"
#include <QMessageBox>
#include "userdetail.h"
#include <QLineEdit>
#include<QLabel>
#include<QTableWidget>

namespace Ui {
class qt_user;
}

class qt_user : public QWidget
{
    Q_OBJECT

public:
    explicit qt_user(QWidget *parent = nullptr);
    ~qt_user();
    USERS dataUser;
    void print();
  QList<QTableWidgetItem*> ListItem;
    QLineEdit* find;

private slots:
    void on_table_cellDoubleClicked(int row, int column);
    void on_find_textChanged(const QString &arg1);

private:
    Ui::qt_user *ui;
    void refresh();
};

#endif // QT_USER_H
