#ifndef USERDETAIL_H
#define USERDETAIL_H

#include <QDialog>
#include <QMessageBox>
#include "vs_user.h"

namespace Ui {
class userdetail;
}

class userdetail : public QDialog
{
    Q_OBJECT

public:
    explicit userdetail(std::string id, QWidget *parent = nullptr);
    ~userdetail();
    USERS data;
    usr* p;

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::userdetail *ui;
};

#endif // USERDETAIL_H
