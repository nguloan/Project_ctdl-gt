#ifndef STATISTICS_H
#define STATISTICS_H

#include "purchasehst.h"
#include "category.h"
class statistics
{
public:
    statistics();
    purchasehst phlist;
    category cllist;
    unsigned long long money_month(QString month);
    unsigned long long money_category(QString catelogy,QString month);
    int number_product_month(QString month);
    int number_product_category(QString category,QString month);
    int countbymonth(QString);
    int sodonbihuy(QString);
};

#endif // STATISTICS_H
