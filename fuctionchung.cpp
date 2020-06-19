#include "fuctionchung.h"

fuctionchung::fuctionchung()
{
}
QString vnd(unsigned long long money){
    QString vnd=QString::number(money);
    vnd.append("vnd");
    if(vnd.count()>=7)vnd.insert((vnd.count()-6),".");
    if(vnd.count()>=11)vnd.insert((vnd.count()-10),".");
    if(vnd.count()>=15)vnd.insert((vnd.count()-14),".");
    if(vnd.count()>=19)vnd.insert((vnd.count()-18),".");
    if(vnd.count()>=23)vnd.insert((vnd.count()-22),".");
    return vnd;
}
unsigned long long doiso(unsigned long long x){
    unsigned long long z=10;
    while(z<=x){
        z*=10;
    }
    return z;
}
