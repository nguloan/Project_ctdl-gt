#ifndef MANAGERWG_H
#define MANAGERWG_H
#include "report.h"
#include <QWidget>
#include <QString>
#include "payment.h"
#include "purchasehst.h"
#include "status.h"
#include "addstatus.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include "phselect.h"
#include "chartforph.h"
QT_BEGIN_NAMESPACE
namespace Ui { class managerwg; }
QT_END_NAMESPACE
class managerwg : public QWidget
{
    Q_OBJECT

public:
    managerwg(QWidget *parent = nullptr);
    ~managerwg();
    purchasehst phlist;
    void printTable();
    void tableItemClicked(int row);
    void renewtb();

private slots:
    void on_thongke_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_search_textChanged(const QString &arg1);

    void on_back_clicked();

private:
    QList<QTableWidgetItem*> ListItem;
    Ui::managerwg *ui;
};
#endif // MANAGERWG_H
