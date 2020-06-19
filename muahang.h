#ifndef MUAHANG_H
#define MUAHANG_H
#include "payment.h"
#include <QWidget>
#include "purchasehst.h"
namespace Ui {
class muahang;
}

class muahang : public QWidget
{
    Q_OBJECT

public:
    explicit muahang(QWidget *parent = nullptr);
    payment pmlist;
    void populatepmbox();
    ~muahang();

private:
    Ui::muahang *ui;
};

#endif // MUAHANG_H
