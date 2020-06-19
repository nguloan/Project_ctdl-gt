#ifndef BAOCAO_H
#define BAOCAO_H
#include<QLocale>
#include <QWidget>
#include "monthhd.h"
#include "statistics.h"
#include "purchasehst.h"
#include "category.h"
namespace Ui {
class baocao;
}

class baocao : public QWidget
{
    Q_OBJECT

public:
    QString time;
    explicit baocao(QWidget *parent = nullptr);
    ~baocao();
    void populatetimebox();
    monthhd months;
    statistics thongke;
    void printtablebc();
private:
    Ui::baocao *ui;
};

#endif // BAOCAO_H
