#include "chartforph.h"
#include "ui_chartforph.h"
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QDateTime>
#include "statistics.h"
#include "category.h"
#include "purchasehst.h"
#include "monthhd.h"
#include <qdebug.h>
#include "fuctionchung.h"
#include<QMessageBox>


chartforph::chartforph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chartforph)
{


    this->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));

    inittimelist(timelist);
    initphlist(statistics.phlist);
    init(statistics.cllist);
    ui->setupUi(this);

     this->setWindowTitle("Thống kê doanh thu");
    populateThemeBox();
    populateAnimationBox();
    populateLegendBox();
    populateTimeBox();
    populateChartBox();
    QChartView *chartview = new QChartView(piechartbymonth("05/2020"));
    chartview->setRenderHint(QPainter::Antialiasing);
    QPalette pal = chartview->palette();
    m_charts << chartview;
    ui->antialiasCheckBox->setChecked(true);
    ui->gridLayout->addWidget(chartview,0,0);
    updateUI();

}
chartforph::~chartforph()
{
    delete ui;
}
void chartforph::populateThemeBox()
{
    // add items to theme combobox
    ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
    ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
}

void chartforph::populateAnimationBox()
{
    // add items to animation combobox
    ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);
    ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);

}

void chartforph::populateLegendBox()
{
    // add items to legend combobox
    ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
    ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
    ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    ui->legendComboBox->addItem("No Legend ", 0);
}
void chartforph::populateTimeBox()
{
    ui->timeComboBox->addItem("All time",0);
    for(auto p=timelist.gethead();p!=NULL;p=p->next){
            ui->timeComboBox->addItem(QString(p->monthyear),p->monthyear);
    }
}
void chartforph::populateChartBox()
{
    ui->chartComboBox->addItem("Pie Chart");
    ui->chartComboBox->addItem("Bar Chart");
}
QChart *chartforph::barchart(){
    QT_CHARTS_USE_NAMESPACE
    unsigned long long max_money=0;
    int n =statistics.cllist.getRows();
    QBarSet **set=new QBarSet*[n];
    int i=0;

    for(auto p=statistics.cllist.getHead();p!=NULL;p=p->next){



        set[i] = new QBarSet(QString::fromStdString(p->name));
        for(auto l=timelist.gettail();l!=NULL;l=l->prev){

            unsigned long long x;
            x= statistics.money_category(QString::fromStdString(p->name),l->monthyear);

            *set[i]<< x;
            if(x>max_money)max_money=x;
        }
         i++;
    }
    QBarSeries *series = new QBarSeries;
    int j=0;
    for(auto p=statistics.cllist.getHead();p!=NULL;p=p->next){
        series->append(set[j]);
        j++;
    }
    QChart *chart=new QChart;
    chart->addSeries(series);
    chart->setTitle("Biểu đố thống kê doanh thu theo mục lục");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    QStringList month;
    for(auto p=timelist.gettail();p!=NULL;p=p->prev){
        month<< p->monthyear;
    }
    QBarCategoryAxis *axisx= new QBarCategoryAxis();
    axisx->append(month);
    chart->addAxis(axisx,Qt::AlignBottom);
            series->attachAxis(axisx);
    QValueAxis *axisy =new QValueAxis();

    axisy->applyNiceNumbers();
    chart->addAxis(axisy,Qt::AlignLeft);
    series->attachAxis(axisy);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignTop);
    return chart;
    }
QChart *chartforph::barchartbymonth(QString month)
{
    QT_CHARTS_USE_NAMESPACE
    int n =statistics.cllist.getRows();
    QBarSet **set=new QBarSet*[n];
    int i=0;
    for(auto p=statistics.cllist.getHead();p!=NULL;p=p->next){
        set[i] = new QBarSet(QString::fromStdString(p->name));
        for(auto l=timelist.gettail();l!=NULL;l=l->prev){
            if(l->monthyear==month)
            *set[i]<< statistics.money_category(QString::fromStdString(p->name),l->monthyear);
        }
         i++;
    }
    QBarSeries *series = new QBarSeries;
    int j=0;
    for(auto p=statistics.cllist.getHead();p!=NULL;p=p->next){
        series->append(set[j]);
        j++;
    }
    QChart *chart=new QChart;
    chart->addSeries(series);
    chart->setTitle("Biểu đố thống kê doanh thu trong tháng "+ month);
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    QBarCategoryAxis *axisx= new QBarCategoryAxis();
    axisx->append(month);
    chart->addAxis(axisx,Qt::AlignBottom);
            series->attachAxis(axisx);
    QValueAxis *axisy =new QValueAxis();

    axisy->applyNiceNumbers();
    chart->addAxis(axisy,Qt::AlignLeft);
    series->attachAxis(axisy);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignTop);
    chart->legend()->maximumSize();
    return chart;
    }
QChart *chartforph::piechart()
{
    DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QPieSeries *yearSeries = new QPieSeries();
    yearSeries->setName("Thống kê toàn bộ các tháng");

    QStringList months;
    for(auto l=timelist.gettail();l!=NULL;l=l->prev){
        months   << l->monthyear;
    }
    QStringList names;
    for(auto p=statistics.cllist.getHead();p!=NULL;p=p->next){
        names << QString::fromStdString(p->name);
    }

    for (auto p=statistics.cllist.getHead();p!=NULL;p=p->next) {
        QPieSeries *series = new QPieSeries();
        series->setName("Doanh thu của danh mục :" + QString::fromStdString(p->name));

        for (auto l=timelist.gettail();l!=NULL;l=l->prev)
            *series << new DrilldownSlice(statistics.money_category(QString::fromStdString(p->name),l->monthyear),l->monthyear, yearSeries);

        QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

        *yearSeries << new DrilldownSlice(series->sum(),QString::fromStdString(p->name), series);
    }

    QObject::connect(yearSeries, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

    chart->changeSeries(yearSeries);
    return chart;
}
QChart *chartforph::piechartbymonth(QString month)
{
    DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QPieSeries *monthSeries = new QPieSeries();
    monthSeries->setName("Thống kê doanh thu trong tháng "+ month);

    QStringList names;
    for(auto p=statistics.cllist.getHead();p!=NULL;p=p->next){
        names << QString::fromStdString(p->name);
    }

    for (auto p=statistics.cllist.getHead();p!=NULL;p=p->next) {
        QPieSeries *series = new QPieSeries();
        series->setName("Doanh thu của danh mục :" + QString::fromStdString(p->name));

        for (auto l=timelist.gettail();l!=NULL;l=l->prev){
            if(l->monthyear==month)
            *series << new DrilldownSlice(statistics.money_category(QString::fromStdString(p->name),l->monthyear),l->monthyear, monthSeries);
            }
        QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

        *monthSeries << new DrilldownSlice(series->sum(),QString::fromStdString(p->name), series);
    }

    QObject::connect(monthSeries, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

    chart->changeSeries(monthSeries);
    return chart;
}
void chartforph::updateUI()
{
    if(ui->timeComboBox->currentText()=="All time"){
    if(ui->chartComboBox->currentText()=="Pie Chart"){
        QChartView *chartview = new QChartView(piechart());
        chartview->setRenderHint(QPainter::Antialiasing);
        m_charts.clear();
        m_charts << chartview;
        ui->gridLayout->addWidget(chartview,0,0);
    }
    if(ui->chartComboBox->currentText()=="Bar Chart"){
        QChartView *chartview = new QChartView(barchart());
        chartview->setRenderHint(QPainter::Antialiasing);
        m_charts.clear();
        m_charts << chartview;
        ui->gridLayout->addWidget(chartview,0,0);
    }
    }else{
        if(ui->chartComboBox->currentText()=="Pie Chart"){
            QChartView *chartview = new QChartView(piechartbymonth(ui->timeComboBox->currentText()));
            chartview->setRenderHint(QPainter::Antialiasing);
            m_charts.clear();
            m_charts << chartview;
            ui->gridLayout->addWidget(chartview,0,0);
        }
        if(ui->chartComboBox->currentText()=="Bar Chart"){
            QChartView *chartview = new QChartView(barchartbymonth(ui->timeComboBox->currentText()));
            chartview->setRenderHint(QPainter::Antialiasing);
            m_charts.clear();
            m_charts << chartview;
            ui->gridLayout->addWidget(chartview,0,0);
        }
    }
    QChart::ChartTheme theme = static_cast <QChart::ChartTheme>(
                ui->themeComboBox->itemData(ui->themeComboBox->currentIndex()).toInt());

    const auto charts = m_charts;
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->theme() != theme) {
        for (QChartView *chartView : charts) {
            chartView->chart()->setTheme(theme);
        }
        QPalette pal = ui->layoutWidget->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        ui->layoutWidget->setPalette(pal);
        this->setPalette(pal);
    }
    bool checked = ui->antialiasCheckBox->isChecked();
    for (QChartView *chart : m_charts)
        chart->setRenderHint(QPainter::Antialiasing, checked);
    //![11]

    // Update animation options
    //![9]
    QChart::AnimationOptions options(
                ui->animatedComboBox->itemData(ui->animatedComboBox->currentIndex()).toInt());
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView : charts)
            chartView->chart()->setAnimationOptions(options);
    }
    //![9]

    // Update legend alignment
    //![10]
    Qt::Alignment alignment(
                ui->legendComboBox->itemData(ui->legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        for (QChartView *chartView : charts)
            chartView->chart()->legend()->hide();
    } else {
        for (QChartView *chartView : charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }

    //![10]

}


void chartforph::on_themeComboBox_currentIndexChanged(int index)
{
    chartforph::updateUI();
}

void chartforph::on_animatedComboBox_currentIndexChanged(int index)
{
    chartforph::updateUI();
}

void chartforph::on_legendComboBox_currentIndexChanged(int index)
{
    chartforph::updateUI();
}

void chartforph::on_antialiasCheckBox_stateChanged(int arg1)
{
   chartforph::updateUI();
}

void chartforph::on_chartComboBox_currentIndexChanged(const QString &arg1)
{
    chartforph::updateUI();
}

void chartforph::on_timeComboBox_currentIndexChanged(const QString &arg1)
{
    chartforph::updateUI();
}
