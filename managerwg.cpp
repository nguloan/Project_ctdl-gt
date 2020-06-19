#include "managerwg.h"
#include"purchasehst.h"
#include "ui_managerwg.h"
#include "addstatus.h"
#include <QIcon>
managerwg::managerwg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::managerwg)
{
    initphlist(phlist);
    ui->setupUi(this);
 //   QPalette pal = qApp->palette();
  //  pal.setColor(QPalette::Window, QRgb(0xcee7f0));
   // pal.setColor(QPalette::WindowText, QRgb(0x404044));

   // qApp->setPalette(pal);
    ui->back->setIcon(QIcon("E:/Project/MyProject/Icon/back.png"));
//    ui->table->setGeometry(200,100,1500,7000);
    ui->table->setColumnCount(10);
    printTable();
    connect(ui->table,&QTableWidget::cellDoubleClicked,this,&managerwg::tableItemClicked);
    ListItem = {};

}
managerwg::~managerwg()
{
    delete ui;
}
void managerwg::printTable(){
      ui->table->clear();
      ui->table->resize(1485,700);
      ui->table->setRowCount(phlist.countlist());
      QTableWidgetItem* col0=new QTableWidgetItem(QString("Đơn hàng"));
      QTableWidgetItem* col1 =new QTableWidgetItem(QString("Tên sản phẩm"));
      QTableWidgetItem* col2 =new QTableWidgetItem(QString("Tên khách hàng"));
      QTableWidgetItem* col3 = new QTableWidgetItem(QString("Địa chỉ"));
      QTableWidgetItem* col4 = new QTableWidgetItem(QString("Số điện thoại"));
      QTableWidgetItem* col5 =new QTableWidgetItem(QString("Giá tiền"));
      QTableWidgetItem* col6 =new QTableWidgetItem(QString("Ngày đặt hàng"));
      QTableWidgetItem* col7 =new QTableWidgetItem(QString("Hình thức thanh toán"));
      QTableWidgetItem* col8 =new QTableWidgetItem(QString("Trạng thái"));
      QTableWidgetItem* col9 =new QTableWidgetItem(QString("Ngày cập nhật "));
      ui->table->setHorizontalHeaderItem(0, col0);
      ui->table->setHorizontalHeaderItem(1, col1);
      ui->table->setHorizontalHeaderItem(2, col2);
      ui->table->setHorizontalHeaderItem(3, col3);
      ui->table->setHorizontalHeaderItem(4, col4);
      ui->table->setHorizontalHeaderItem(5, col5);
      ui->table->setHorizontalHeaderItem(6, col6);
      ui->table->setHorizontalHeaderItem(7, col7);
      ui->table->setHorizontalHeaderItem(8, col8);
      ui->table->setHorizontalHeaderItem(9, col9);

      ui->table->setColumnWidth(1,300);
      ui->table->setColumnWidth(2,150);

      int i=0;
      for(auto p=phlist.gethead();p!=NULL;p=p->next){
          ui->table->setItem(i,0,new QTableWidgetItem(p->code));
          ui->table->setItem(i,1,new QTableWidgetItem(p->nameProduct));
          ui->table->setItem(i,2,new QTableWidgetItem(p->namerecipient));
          ui->table->setItem(i,3,new QTableWidgetItem(p->address));
          ui->table->setItem(i,4,new QTableWidgetItem(p->numberphoneRecipient));
           ui->table->setItem(i,5,new QTableWidgetItem(QLocale(QLocale::English).toString(p->price.toUInt())+" VND"));
          ui->table->setItem(i,6,new QTableWidgetItem(p->datetime.toString("dd/MM/yyyy")));
          ui->table->setItem(i,7,new QTableWidgetItem(p->payments));
          ui->table->setItem(i,8,new QTableWidgetItem(p->status));
          ui->table->setItem(i,9,new QTableWidgetItem(p->updatetime.toString("dd/MM/yyyy")));
          ui->table->item(i,5)->setTextAlignment(Qt::AlignCenter);
          i++;
      }
}
void managerwg::renewtb(){
    ListItem.clear();
    phlist.~purchasehst();
    initphlist(phlist);
    printTable();
}
void managerwg::tableItemClicked(int row)
{
   QString x=ui->table->item(row,0)->text();
   phselect* phselect1 = new phselect(x,NULL);
   phselect1->setModal(true);

   if(phselect1->exec()==phselect::Accepted)renewtb();
}

void managerwg::on_thongke_clicked()
{
    chartforph *chartwg= new chartforph;

    chartwg->setFocus();
    chartwg->show();
}

void managerwg::on_pushButton_clicked()
{
    Addstatus *themstt = new Addstatus;
    themstt->setModal(true);
    themstt->show();
}

void managerwg::on_pushButton_2_clicked()
{
    report *reportx=new report;
    reportx->show();
}


void managerwg::on_search_textChanged(const QString &arg1)
{
    foreach(QTableWidgetItem *row, ListItem){
        row->setBackground(QColor("white"));
    }
    if(arg1== "")return;
    ListItem = ui->table->findItems(arg1,Qt:: MatchContains);

    foreach(QTableWidgetItem* row, ListItem){
        row->setBackground(QColor("blue"));
    }
}


void managerwg::on_back_clicked()
{
    renewtb();
}
