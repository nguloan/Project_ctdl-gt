#ifndef PHSELECT_H
#define PHSELECT_H
#include "managerwg.h"
#include "purchasehst.h"
#include "status.h"
#include <QDialog>
#include <QString>
namespace Ui {
class phselect;
}

class phselect : public QDialog
{
    Q_OBJECT

public:
    explicit phselect(QString x,QWidget *parent = nullptr);
    ~phselect();
    purchasehst phlist;
    status sttlist;
private slots:

    void on_close_clicked();

    void on_apply_clicked();

private:
    Ui::phselect *ui;
    QString ph;//biến toàn cục lưu code sản phẩm cần thay đổi
};

#endif // PHSELECT_H
