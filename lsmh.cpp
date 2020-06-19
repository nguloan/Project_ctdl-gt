#include "lsmh.h"
#include "ui_lsmh.h"
#include<QTabWidget>
#include <qdebug.h>
lsmh::lsmh(QString userid,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lsmh)
{
    username=userid;
    initphlist(phlist);
    ui->setupUi(this);
    this->resize(1820,650);

    ui->scrollArea->setGeometry(0,50,1200,660);
    ui->scrollArea->setStyleSheet("border:none;background-color:white;");
    tatca();

    this->setStyleSheet("QPushButton{border:none;}");

    ui->tatcabt->setFont(QFont("Arial",13));
    ui->dahuybt->setFont(QFont("Arial",13));
    ui->dagiaobt->setFont(QFont("Arial",13));
    ui->dangchobt->setGeometry(QRect(590,0,150,30));

    QWidget* hboxWidget = new QWidget(this);
    hboxWidget->setGeometry(QRect(0,0,1100,50));

    QHBoxLayout* hboxBtn = new QHBoxLayout(hboxWidget);

    hboxBtn->addWidget(ui->tatcabt);
    hboxBtn->addWidget(ui->dangchobt);
    hboxBtn->addWidget(ui->danggiaobt);
    hboxBtn->addWidget(ui->dagiaobt);
    hboxBtn->addWidget(ui->dahuybt);

    QLabel* line = new QLabel(this);
    line->setGeometry(QRect(0,55,1500,3));
    line->setStyleSheet("border-top: 1px solid black;");


}
void lsmh::tatca(){
    qDeleteAll(ui->scrollAreaWidgetContents->children());
    QGridLayout* layout = new QGridLayout(ui->scrollAreaWidgetContents);
    int count=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){
           if(p->username==username)count++;
        }
    if(count==0){
        QWidget* tatca = new QWidget(this);
        QLabel* thongbao =new QLabel(tatca);
        thongbao->setText("Không có thông tin sản phẩm để hiển thị");
        thongbao->setFont(QFont("Arial",15));
        thongbao->setGeometry(QRect(500,45,230,30));
        layout->addWidget(thongbao,0,0);
    }
     int dem=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){

        if(p->username==username){

            QString filePhoto = QString("E:/Project/MyProject/photoProducts/%1.png").arg(p->idProduct);

            if(QFile::exists(filePhoto) == false)
            {
                filePhoto = "E:/Project/MyProject/photo/productImage.png";
            }

            QPixmap photoPd(filePhoto);

               QWidget* sp= new QWidget(this);
               QLabel* pic=new QLabel(sp);
               QTextEdit* name = new QTextEdit(sp);
                sp->setStyleSheet("background-color:white;");
               QLabel* label1 = new QLabel(sp);
               label1->setText("Mã đơn hàng:");
               label1->setFont(QFont("Arial",10));
                label1->setGeometry(QRect(0,0,150,30));
               QLabel* money=new QLabel(sp);
               QLabel* codeOrder = new QLabel(sp);
               codeOrder->setText(p->code);
               codeOrder->setStyleSheet("color:#3498DB;");
               codeOrder->setFont(QFont("Arial",13));
               codeOrder->setGeometry(QRect(150,0,200,30));

               pic->setPixmap(photoPd.scaled(150,150,Qt::KeepAspectRatio));
               pic->setGeometry(QRect(0,40,150,150));

               QLabel* dateOrder = new QLabel(sp);
               dateOrder->setText(QDateTime(p->updatetime).toString("dd/MM/yyyy"));
               dateOrder->setGeometry(QRect(370,0,200,30));
               dateOrder->setFont(QFont("Arial",11));

               QLabel* stt = new QLabel(sp);
               stt->setText(p->status);
               stt->setFont(QFont("Arial",12));
               stt->setGeometry(QRect(590,0,150,30));

               QLabel* bill_lbl = new QLabel(sp);
               bill_lbl->setText("Tổng tiền: ");
               bill_lbl->setGeometry(QRect(800,0,150,30));
               bill_lbl->setFont(QFont("Arial",11));
               bill_lbl->setAlignment(Qt::AlignRight);

               QLabel* bill = new QLabel(sp);
               bill ->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               bill->setGeometry(QRect(960,0,240,30));
               bill->setFont(QFont("Arial",11));
               bill->setStyleSheet("color:#DB3452;");


               QLabel* line = new QLabel(sp);
               line->setGeometry(QRect(0,35,1300,3));
               line->setStyleSheet("border-bottom: 1px solid black;");
               // pic???
               //ten san pham
               name->setText(p->nameProduct);
               name->setFont(QFont("Arial",15));
               name->setGeometry(170,40,500,150);
               name->setStyleSheet("border:none;color:black; background-color:white; color:black;");
               name->setEnabled(false);


               //thanh tien
               money->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               money->setFont(QFont("Arial",15));
               money->setStyleSheet("color:#EC7063;");

               money->setGeometry(700,50,400,40);
               money->setAlignment(Qt::AlignRight);

               layout->addWidget(sp,dem,0);
               layout->setRowMinimumHeight(dem, 200);
               dem++;
           }
        }
}
void lsmh::dangcho(){
    qDeleteAll(ui->scrollAreaWidgetContents->children());
    QGridLayout* layout = new QGridLayout(ui->scrollAreaWidgetContents);
    int count=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){
           if((p->username==username)&&(p->status.contains("Đang chờ")))count++;
        }
    if(count==0){
        QWidget* dangcho = new QWidget(this);
        QLabel* thongbao =new QLabel(dangcho);
        thongbao->setText("Không có thông tin sản phẩm để hiển thị");
        thongbao->setFont(QFont("Arial",15));
        thongbao->setGeometry(QRect(550,40,230,30));
        layout->addWidget(thongbao,0,0);
    }
     int dem=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){

        if((p->username==username)&&p->status.contains("Đang chờ")){
            QString filePhoto = QString("E:/Project/MyProject/photoProducts/%1.png").arg(p->idProduct);

            if(QFile::exists(filePhoto) == false)
            {
                filePhoto = "E:/Project/MyProject/photo/productImage.png";
            }

            QPixmap photoPd(filePhoto);

               QWidget* sp= new QWidget(this);
               QLabel* pic=new QLabel(sp);
               QTextEdit* name = new QTextEdit(sp);
                sp->setStyleSheet("background-color:white;");
               QLabel* label1 = new QLabel(sp);
               label1->setText("Mã đơn hàng:");
               label1->setFont(QFont("Arial",10));
                label1->setGeometry(QRect(0,0,150,30));
               QLabel* money=new QLabel(sp);
               QLabel* codeOrder = new QLabel(sp);
               codeOrder->setText(p->code);
               codeOrder->setStyleSheet("color:#3498DB;");
               codeOrder->setFont(QFont("Arial",13));
               codeOrder->setGeometry(QRect(150,0,200,30));

               pic->setPixmap(photoPd.scaled(150,150,Qt::KeepAspectRatio));
               pic->setGeometry(QRect(0,40,150,150));

               QLabel* dateOrder = new QLabel(sp);
               dateOrder->setText(QDateTime(p->updatetime).toString("dd/MM/yyyy"));
               dateOrder->setGeometry(QRect(370,0,200,30));
               dateOrder->setFont(QFont("Arial",11));

               QLabel* stt = new QLabel(sp);
               stt->setText(p->status);
               stt->setFont(QFont("Arial",12));
               stt->setGeometry(QRect(590,0,150,30));

               QLabel* bill_lbl = new QLabel(sp);
               bill_lbl->setText("Tổng tiền: ");
               bill_lbl->setGeometry(QRect(800,0,150,30));
               bill_lbl->setFont(QFont("Arial",11));
               bill_lbl->setAlignment(Qt::AlignRight);

               QLabel* bill = new QLabel(sp);
               bill ->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               bill->setGeometry(QRect(960,0,240,30));
               bill->setFont(QFont("Arial",11));
               bill->setStyleSheet("color:#DB3452;");


               QLabel* line = new QLabel(sp);
               line->setGeometry(QRect(0,35,1300,3));
               line->setStyleSheet("border-bottom: 1px solid black;");
               // pic???
               //ten san pham
               name->setText(p->nameProduct);
               name->setFont(QFont("Arial",15));
               name->setGeometry(170,40,500,150);
               name->setStyleSheet("border:none;color:black; background-color:white; color:black;");
               name->setEnabled(false);



               //thanh tien
               money->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               money->setFont(QFont("Arial",15));
               money->setStyleSheet("color:#EC7063;");

               money->setGeometry(700,50,400,40);
               money->setAlignment(Qt::AlignRight);

               layout->addWidget(sp,dem,0);
               layout->setRowMinimumHeight(dem, 200);
               dem++;
           }
        }
}
void lsmh::danggiao(){
    qDeleteAll(ui->scrollAreaWidgetContents->children());
    QGridLayout* layout = new QGridLayout(ui->scrollAreaWidgetContents);
    int count=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){
           if(p->username==username&&p->status.contains("Đang giao"))count++;
        }
    if(count==0){
        QWidget* tatca = new QWidget(this);
        QLabel* thongbao =new QLabel(tatca);
        thongbao->setText("Không có thông tin sản phẩm để hiển thị");
        thongbao->setFont(QFont("Arial",15));
        thongbao->setGeometry(QRect(500,45,230,30));
        layout->addWidget(thongbao,0,0);
    }
     int dem=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){

        if(p->username==username&&p->status.contains("Đang giao")){
            QString filePhoto = QString("E:/Project/MyProject/photoProducts/%1.png").arg(p->idProduct);

            if(QFile::exists(filePhoto) == false)
            {
                filePhoto = "E:/Project/MyProject/photo/productImage.png";
            }

            QPixmap photoPd(filePhoto);

               QWidget* sp= new QWidget(this);
               QLabel* pic=new QLabel(sp);
               QTextEdit* name = new QTextEdit(sp);
                sp->setStyleSheet("background-color:white;");
               QLabel* label1 = new QLabel(sp);
               label1->setText("Mã đơn hàng:");
               label1->setFont(QFont("Arial",10));
                label1->setGeometry(QRect(0,0,150,30));
               QLabel* money=new QLabel(sp);
               QLabel* codeOrder = new QLabel(sp);
               codeOrder->setText(p->code);
               codeOrder->setStyleSheet("color:#3498DB;");
               codeOrder->setFont(QFont("Arial",13));
               codeOrder->setGeometry(QRect(150,0,200,30));

               pic->setPixmap(photoPd.scaled(150,150,Qt::KeepAspectRatio));
               pic->setGeometry(QRect(0,40,150,150));

               QLabel* dateOrder = new QLabel(sp);
               dateOrder->setText(QDateTime(p->updatetime).toString("dd/MM/yyyy"));
               dateOrder->setGeometry(QRect(370,0,200,30));
               dateOrder->setFont(QFont("Arial",11));

               QLabel* stt = new QLabel(sp);
               stt->setText(p->status);
               stt->setFont(QFont("Arial",12));
               stt->setGeometry(QRect(590,0,150,30));

               QLabel* bill_lbl = new QLabel(sp);
               bill_lbl->setText("Tổng tiền: ");
               bill_lbl->setGeometry(QRect(800,0,150,30));
               bill_lbl->setFont(QFont("Arial",11));
               bill_lbl->setAlignment(Qt::AlignRight);

               QLabel* bill = new QLabel(sp);
               bill ->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               bill->setGeometry(QRect(960,0,240,30));
               bill->setFont(QFont("Arial",11));
               bill->setStyleSheet("color:#DB3452;");


               QLabel* line = new QLabel(sp);
               line->setGeometry(QRect(0,35,1300,3));
               line->setStyleSheet("border-bottom: 1px solid black;");
               // pic???
               //ten san pham
               name->setText(p->nameProduct);
               name->setFont(QFont("Arial",15));
               name->setGeometry(170,40,500,150);
               name->setStyleSheet("border:none;color:black; background-color:white; color:black;");
               name->setEnabled(false);


               //thanh tien
               money->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               money->setFont(QFont("Arial",15));
               money->setStyleSheet("color:#EC7063;");

               money->setGeometry(700,50,400,40);
               money->setAlignment(Qt::AlignRight);

               layout->addWidget(sp,dem,0);
               layout->setRowMinimumHeight(dem, 200);
               dem++;
           }
        }
}
void lsmh::dagiao(){
    qDeleteAll(ui->scrollAreaWidgetContents->children());
    QGridLayout* layout = new QGridLayout(ui->scrollAreaWidgetContents);
    int count=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){
           if(p->username==username&&p->status.contains("Đã giao"))count++;
        }
    if(count==0){
        QWidget* tatca = new QWidget(this);
        QLabel* thongbao =new QLabel(tatca);
        thongbao->setText("Không có thông tin sản phẩm để hiển thị");
        thongbao->setFont(QFont("Arial",15));
        thongbao->setGeometry(QRect(500,45,400,30));
        layout->addWidget(thongbao,0,0);
    }
     int dem=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){

        if(p->username==username&&p->status.contains("Đã giao")){
            QString filePhoto = QString("E:/Project/MyProject/photoProducts/%1.png").arg(p->idProduct);

            if(QFile::exists(filePhoto) == false)
            {
                filePhoto = "E:/Project/MyProject/photo/productImage.png";
            }

            QPixmap photoPd(filePhoto);

               QWidget* sp= new QWidget(this);
               QLabel* pic=new QLabel(sp);
               QTextEdit* name = new QTextEdit(sp);
                sp->setStyleSheet("background-color:white;");
               QLabel* label1 = new QLabel(sp);
               label1->setText("Mã đơn hàng:");
               label1->setFont(QFont("Arial",10));
                label1->setGeometry(QRect(0,0,150,30));
               QLabel* money=new QLabel(sp);
               QLabel* codeOrder = new QLabel(sp);
               codeOrder->setText(p->code);
               codeOrder->setStyleSheet("color:#3498DB;");
               codeOrder->setFont(QFont("Arial",13));
               codeOrder->setGeometry(QRect(150,0,200,30));

               pic->setPixmap(photoPd.scaled(150,150,Qt::KeepAspectRatio));
               pic->setGeometry(QRect(0,40,150,150));

               QLabel* dateOrder = new QLabel(sp);
               dateOrder->setText(QDateTime(p->updatetime).toString("dd/MM/yyyy"));
               dateOrder->setGeometry(QRect(370,0,200,30));
               dateOrder->setFont(QFont("Arial",11));

               QLabel* stt = new QLabel(sp);
               stt->setText(p->status);
               stt->setFont(QFont("Arial",12));
               stt->setGeometry(QRect(590,0,150,30));

               QLabel* bill_lbl = new QLabel(sp);
               bill_lbl->setText("Tổng tiền: ");
               bill_lbl->setGeometry(QRect(800,0,150,30));
               bill_lbl->setFont(QFont("Arial",11));
               bill_lbl->setAlignment(Qt::AlignRight);

               QLabel* bill = new QLabel(sp);
               bill ->setText(QLocale(QLocale::English).toString( p->price.toULong())+"đ");
               bill->setGeometry(QRect(960,0,240,30));
               bill->setFont(QFont("Arial",11));
               bill->setStyleSheet("color:#DB3452;");


               QLabel* line = new QLabel(sp);
               line->setGeometry(QRect(0,35,1300,3));
               line->setStyleSheet("border-bottom: 1px solid black;");
               // pic???
               //ten san pham
               name->setText(p->nameProduct);
               name->setFont(QFont("Arial",15));
               name->setGeometry(170,40,500,150);
               name->setStyleSheet("border:none;color:black; background-color:white; color:black;");
               name->setEnabled(false);



               //thanh tien
               money->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               money->setFont(QFont("Arial",15));
               money->setStyleSheet("color:#EC7063;");

               money->setGeometry(700,50,400,40);
               money->setAlignment(Qt::AlignRight);

               layout->addWidget(sp,dem,0);
               layout->setRowMinimumHeight(dem, 200);
               dem++;
           }
        }
}
void lsmh::dahuy(){
    qDeleteAll(ui->scrollAreaWidgetContents->children());
    QGridLayout* layout = new QGridLayout(ui->scrollAreaWidgetContents);
    int count=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){
           if(p->username==username&&p->status.contains("Đã hủy"))count++;
        }
    if(count==0){
        QWidget* tatca = new QWidget(this);
        QLabel* thongbao =new QLabel(tatca);
        thongbao->setText("Không có thông tin sản phẩm để hiển thị");
        thongbao->setFont(QFont("Arial",15));
        thongbao->setGeometry(QRect(500,45,230,30));
        layout->addWidget(thongbao,0,0);
    }
     int dem=0;
    for(auto p=phlist.gettail();p!=NULL;p=p->prev){

        if(p->username==username&&p->status.contains("Đã hủy")){
            QString filePhoto = QString("E:/Project/MyProject/photoProducts/%1.png").arg(p->idProduct);

            if(QFile::exists(filePhoto) == false)
            {
                filePhoto = "E:/Project/MyProject/photo/productImage.png";
            }

            QPixmap photoPd(filePhoto);

               QWidget* sp= new QWidget(this);
               QLabel* pic=new QLabel(sp);
               QTextEdit* name = new QTextEdit(sp);
                sp->setStyleSheet("background-color:white;");
               QLabel* label1 = new QLabel(sp);
               label1->setText("Mã đơn hàng:");
               label1->setFont(QFont("Arial",10));
                label1->setGeometry(QRect(0,0,150,30));
               QLabel* money=new QLabel(sp);
               QLabel* codeOrder = new QLabel(sp);
               codeOrder->setText(p->code);
               codeOrder->setStyleSheet("color:#3498DB;");
               codeOrder->setFont(QFont("Arial",13));
               codeOrder->setGeometry(QRect(150,0,200,30));

               pic->setPixmap(photoPd.scaled(150,150,Qt::KeepAspectRatio));
               pic->setGeometry(QRect(0,40,150,150));

               QLabel* dateOrder = new QLabel(sp);
               dateOrder->setText(QDateTime(p->updatetime).toString("dd/MM/yyyy"));
               dateOrder->setGeometry(QRect(370,0,200,30));
               dateOrder->setFont(QFont("Arial",11));

               QLabel* stt = new QLabel(sp);
               stt->setText(p->status);
               stt->setFont(QFont("Arial",12));
               stt->setGeometry(QRect(590,0,150,30));

               QLabel* bill_lbl = new QLabel(sp);
               bill_lbl->setText("Tổng tiền: ");
               bill_lbl->setGeometry(QRect(800,0,150,30));
               bill_lbl->setFont(QFont("Arial",11));
               bill_lbl->setAlignment(Qt::AlignRight);

               QLabel* bill = new QLabel(sp);
               bill ->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               bill->setGeometry(QRect(960,0,240,30));
               bill->setFont(QFont("Arial",11));
               bill->setStyleSheet("color:#DB3452;");


               QLabel* line = new QLabel(sp);
               line->setGeometry(QRect(0,35,1300,3));
               line->setStyleSheet("border-bottom: 1px solid black;");
               // pic???
               //ten san pham
               name->setText(p->nameProduct);
               name->setFont(QFont("Arial",15));
               name->setGeometry(170,40,500,150);
               name->setStyleSheet("border:none;color:black; background-color:white; color:black;");
               name->setEnabled(false);



               //thanh tien
               money->setText(QLocale(QLocale::English).toString(p->price.toULong())+"đ");
               money->setFont(QFont("Arial",15));
               money->setStyleSheet("color:#EC7063;");

               money->setGeometry(700,50,400,40);
               money->setAlignment(Qt::AlignRight);

               layout->addWidget(sp,dem,0);
               layout->setRowMinimumHeight(dem, 200);
               dem++;
           }
        }
}

void lsmh::on_tatcabt_clicked()
{

    tatca();
}

void lsmh::on_dangchobt_clicked()
{

    dangcho();
}
void lsmh::on_danggiaobt_clicked()
{
    danggiao();
}
void lsmh::on_dagiaobt_clicked()
{
    dagiao();
}
void lsmh::on_dahuybt_clicked()
{
    dahuy();
}
lsmh::~lsmh()
{
    delete ui;
}
