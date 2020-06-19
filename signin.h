#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QMessageBox>
#include "vs_user.h"
#include"program.h"


namespace Ui {
class signin;
}

class signin : public QDialog
{
    Q_OBJECT

public:
    explicit signin(QDialog *parent = nullptr);
    ~signin();
    USERS signin_er;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::signin *ui;
};

#endif // SIGNIN_H
