#include "addstatus.h"
#include "ui_addstatus.h"
#include <QMessageBox>
#include <qdebug.h>
Addstatus::Addstatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addstatus)
{
    QWidget* background = new QWidget(this);
    background->setStyleSheet("background-color:#F4F6F7;");    background->setGeometry(QRect(0,0,2000,1100));

    this->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));

    initsttlist(sttlist);
    initphlist(phlist);
    ui->setupUi(this);
     this->setWindowTitle("Thêm trạng thái đơn hàng");
    printtablestt();
}

Addstatus::~Addstatus()
{
    delete ui;
}
void Addstatus::printtablestt(){
    ui->table->clear();
    ui->table->setColumnCount(1);
    ui->table->setRowCount(sttlist.countlist());
    QTableWidgetItem* col0 =new QTableWidgetItem(QString("TRẠNG THÁI"));
    ui->table->setHorizontalHeaderItem(0, col0);
    ui->table->setColumnWidth(0,400);
    int i=0;
    for(auto p=sttlist.gethead();p!=NULL;p=p->next){
        ui->table->setItem(i,0,new QTableWidgetItem(p->status));
        i++;
    }
}
void Addstatus::renewtbstt(){
    sttlist.~status();
    initsttlist(sttlist);
    printtablestt();
}
void Addstatus::on_pushButton_2_clicked()
{
    for(auto p=sttlist.gethead();p!=NULL;p=p->next){
        if(p->status == QString(ui->addstatus->text())){
            QMessageBox::warning(this,"Thông báo","Trạng thái đã tồn tại",QMessageBox::Ok);
            return;
        }
    }
    if(ui->addstatus->text().count()<=1)return;
    sttlist.addhead(ui->addstatus->text());
    outitsttlist(sttlist);
    this->renewtbstt();
    ui->addstatus->clear();
}

void Addstatus::on_pushButton_clicked()
{
    this->close();
}

void Addstatus::on_pushButton_3_clicked()
{
    for(auto p=sttlist.gethead();p!=NULL;p=p->next){
        if(p->status == ui->addstatus->text()){
            QMessageBox::warning(this,"Thông báo","Trạng thái đã tồn tại",QMessageBox::Ok);
            return;
        }
    }
    if(ui->addstatus->text().count()>1){
        sttlist.addhead(ui->addstatus->text());
        outitsttlist(sttlist);
        this->renewtbstt();
    }
    this->close();
}


void Addstatus::on_deletebt_clicked()
{
    for(auto p=phlist.gethead();p!=NULL;p=p->next){
       if(p->status.count() == ui->table->currentItem()->text().count()){
            QMessageBox::warning(this,"Thông báo","Trạng thái tồn tại trong danh sách đơn hàng",QMessageBox::Ok);
                    return;
        }
    }
    sttlist.deletestt(ui->table->currentItem()->text());
    outitsttlist(sttlist);
    this->renewtbstt();
}
