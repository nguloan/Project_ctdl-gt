#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include <QMessageBox>
#include "vs_user.h"
#include"signin.h"

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    ~regist();
    USERS regist_er;

private slots:
    void on_pushButton_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::regist *ui;
};

#endif // REGIST_H
