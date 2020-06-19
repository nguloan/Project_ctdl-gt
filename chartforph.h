#ifndef CHARTFORPH_H
#define CHARTFORPH_H

#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDateTime>
#include "statistics.h"
#include "category.h"
#include "purchasehst.h"
#include "monthhd.h"
#include "drilldownchart.h"
#include "drilldownslice.h"
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class chartforph;
}

class chartforph : public QWidget
{
    Q_OBJECT

public:
    explicit chartforph(QWidget *parent = nullptr);
    ~chartforph();
private:
    void updateUI();
private slots:
    void on_themeComboBox_currentIndexChanged(int index);

    void on_animatedComboBox_currentIndexChanged(int index);

    void on_legendComboBox_currentIndexChanged(int index);

    void on_antialiasCheckBox_stateChanged(int arg1);

    void on_chartComboBox_currentIndexChanged(const QString &arg1);

    void on_timeComboBox_currentIndexChanged(const QString &arg1);

private:
    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();
    void populateChartBox();
    void populateTimeBox();
    void connectSignals();
    category category;
    statistics statistics;
    monthhd timelist;
    QChart *barchart();
    QChart *piechart();
    QChart *barchartbymonth(QString);
    QChart *piechartbymonth(QString);
   QList<QChartView *> m_charts;
    Ui::chartforph *ui;
};

#endif // CHARTFORPH_H
