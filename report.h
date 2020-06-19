#ifndef REPORT_H
#define REPORT_H
#include<QLocale>
#include <QWidget>
#include "monthhd.h"
#include "statistics.h"
#include "purchasehst.h"
#include "category.h"
#include<QComboBox>
namespace Ui {
class report;
}

class report : public QWidget
{
    Q_OBJECT

public:
    explicit report(QWidget *parent = nullptr);
    ~report();
    void populateyearbox();
    void populatemonthbox();
    void populateclbox();
    statistics thongke;
    monthhd thanghd;
    void printtablerp();
private slots:

    void on_okbutton_clicked();

private:
    Ui::report *ui;
};

#endif // REPORT_H
