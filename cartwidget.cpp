#include "cartwidget.h"
#include "ui_cartwidget.h"

cartWidget::cartWidget(QString usrname,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cartWidget)
{

    username = usrname;
    init(Data,username.toStdString());
    init(DataPd);
    ui->setupUi(this);
    this->resize(1920,1000);
    ui->cart->setGeometry(QRect(-10,30,1940,700));
    ui->cart->setStyleSheet("background-color:#D6DBDF; ");
    ui->gridLayoutWidget->setGeometry(QRect(20,0,1900,70));

    QLabel* product = new QLabel(this),
            *price = new QLabel(this),
            *quanity = new QLabel(this),
            *del = new QLabel(this),
            *amount = new QLabel(this);

    product->setText("SẢN PHẨM");
    product->setFont(QFont("Arial",11));
    product->setGeometry(QRect(400,0,180,30));

    price->setText("ĐƠN GIÁ");
    price->setFont(QFont("Arial",11));
    price->setGeometry(QRect(1120,0,180,30));

    quanity->setText("SỐ LƯỢNG");
    quanity->setFont(QFont("Arial",11));
    quanity->setGeometry(QRect(1320,0,180,30));

    del->setText("XÓA");
    del->setFont(QFont("Arial",11));
    del->setGeometry(QRect(1510,0,100,30));

    amount->setText("THÀNH TIỀN");
    amount->setFont(QFont("Arial",11));
    amount->setGeometry(QRect(1620,0,180,30));


    mapAddQuanity = new QSignalMapper(this);
    mapSubQuanity = new QSignalMapper(this);
    mapRemovePd = new QSignalMapper(this);
    connect(mapSubQuanity,&QSignalMapper::mappedWidget,this,&cartWidget::clickSub);
    connect (mapAddQuanity, &QSignalMapper::mappedWidget, this, &cartWidget::clickAdd);
    connect(mapRemovePd,&QSignalMapper::mappedWidget,this,&cartWidget::clickRm);

    QPushButton* removeAll = new QPushButton(QIcon("E:/Project/MyProject/photo/remove.png"),QString("Xóa toàn bộ giỏ hàng"), this);
    removeAll->setGeometry(QRect(20,750,250,50));
    removeAll->setIconSize(QSize(20,20));
    removeAll->setFont(QFont("Arial",12));
    removeAll->setStyleSheet("border:none;");
    removeAll->setCursor(Qt::PointingHandCursor);

    connect(removeAll,&QPushButton::clicked,[this]{
        if(QMessageBox::information(this,"Thông báo","Bạn có muốn xóa toàn bộ giỏ hàng?","Đồng ý","Không đồng ý") == 1)
        {
            return;
        }
        listProductBuy.clear();
        save(Data,username.toStdString(),true);
        Data.~cart();
        init(Data,username.toStdString());
        qDeleteAll(ui->cartContent->children());
        printCart();
        sum =0;
         Bill->setText(QLocale(QLocale::English).toString(0)+"đ");
    });

    QLabel* l2  = new QLabel(this);
    l2->setGeometry(QRect(1100,750,150,50));
    l2->setText("Tổng Cộng: ");
    l2->setFont(QFont("Arial",13));


    Bill = new QLabel(this);
    Bill->setGeometry(1100,750,500,60);
    Bill->setFont(QFont("Arial",20));
    Bill->setStyleSheet(" color:#F31D07;" );
    Bill->setAlignment(Qt::AlignRight);

    QPushButton* Continue = new QPushButton("TIẾP THEO",this);
    Continue->setFont(QFont("Arial",20));
    Continue->setGeometry(QRect(1620,750,250,60));
    Continue->setStyleSheet("background-color:#CB4335;color:white;border:none;");
    Continue->show();
    connect(Continue,&QPushButton::clicked,[this]{
        emit continuePay(listProductBuy);
        this->close();
    });
    printCart();
}

cartWidget::~cartWidget()
{
    delete ui;
}

void cartWidget::printCart()
{
    qDeleteAll(ui->cartContent->children());
    if(Data.length()==0)
    {
        QPixmap avt("E:/Project/MyProject/photo/cartNULL.png");
        QLabel* photo = new QLabel(ui->cartContent);
        photo->setPixmap(avt);
        photo->show();

        return;
    }

    QGridLayout* listPd = new QGridLayout(ui->cartContent);
    listPd->setSpacing(30);

    int dem = 0;
    QSignalMapper* selectProduct = new QSignalMapper(this);
    QSignalMapper* mapEditQuanity = new QSignalMapper(this);

    sum=0;
    for (auto i = Data.getHead() ; i != NULL ;i=i->next) {

        auto p = DataPd.getPoiter(i->codePd);

        if(p != NULL)
        {
            QGridLayout* formpd = new QGridLayout(ui->cartContent);

            QWidget* contentPd = new QWidget(this);
            contentPd->setStyleSheet("background-color:white;");
            contentPd->setObjectName(QString::fromStdString(i->codePd));

            QCheckBox* select = new QCheckBox(contentPd);
            select->setGeometry(QRect(50,90,90,30));
            select->setObjectName(QString::fromStdString( i->codePd));
            select->setChecked(i->select);
            connect(select,SIGNAL(clicked()),selectProduct,SLOT(map()));
            selectProduct->setMapping(select,contentPd);

            QLabel* photoPd  = new QLabel(contentPd);
            QPixmap photo(QString("E:\\Project\\MyProject\\photoProducts\\%1.png").arg(QString::fromStdString(p->id)));
            photoPd->setPixmap(photo.scaled(150,150,Qt::KeepAspectRatio));
            photoPd->setGeometry(QRect(270,50,150,150));

            QTextEdit* namePd = new QTextEdit(contentPd);
            namePd->setText(QString::fromStdString(p->name));
            namePd->setGeometry(QRect(420,90,500,90));
            namePd->setStyleSheet("border:white;");
            namePd->setFont(QFont("Arial",11));

            QLabel* pricePd = new QLabel(contentPd);
            pricePd->setText(QLocale(QLocale::English).toString(QString::fromStdString(p->price).toInt())+"đ");
            pricePd->setGeometry(QRect(1100,90,150,40));
            pricePd->setFont(QFont("Arial",15));

            QLineEdit* quanityPd = new QLineEdit(contentPd);
            quanityPd->setGeometry(QRect(1330,90,70,27));
            quanityPd->setText(QString::number(i->quanity));
            quanityPd->setTextMargins(0,0,0,0);
            quanityPd->setFont(QFont("Arial",10));
            quanityPd->setObjectName(QString::fromStdString(i->codePd));

            connect(quanityPd,SIGNAL(editingFinished()),mapEditQuanity,SLOT(map()));
            mapEditQuanity ->setMapping(quanityPd,contentPd);

            QPushButton* addPd  =  new QPushButton(contentPd);
            addPd->setGeometry(QRect(1400,90,30,20));
            addPd->setIcon(QIcon("E:\\Project\\MyProject\\photo\\add.png"));
            addPd->setStyleSheet("border:none");
            addPd->setObjectName(QString::fromStdString(i->codePd));

            connect (addPd, SIGNAL(clicked()), mapAddQuanity, SLOT(map())) ;
            mapAddQuanity -> setMapping (addPd, contentPd);

            QPushButton* subPd = new QPushButton(contentPd);
            subPd->setGeometry(QRect(1300,90,30,20));
            subPd->setIcon(QIcon("E:\\Project\\MyProject\\photo\\sub.png"));
            subPd->setStyleSheet("border:none");
            subPd->setObjectName(QString::fromStdString(i->codePd));

            connect(subPd,SIGNAL(clicked()),mapSubQuanity,SLOT(map()));
            mapSubQuanity->setMapping(subPd,contentPd);

            QPushButton* removePd = new QPushButton(contentPd);
            removePd->setGeometry(QRect(1500,80,50,50));
            removePd->setStyleSheet("border:none;");
            removePd->setIcon(QIcon("E:\\Project\\MyProject\\photo\\remove.png"));
            removePd->setObjectName(QString::fromStdString(i->codePd));

            connect(removePd,SIGNAL(clicked()),mapRemovePd,SLOT(map()));
            mapRemovePd->setMapping(removePd,contentPd);

            QLabel* amountPd = new QLabel(contentPd);
            if(i->select)
            {
                 sum += std::stoi(p->price)* quanityPd->text().toULongLong();
                 listProductBuy.append(QString::fromStdString(i->codePd));
            }
            amountPd->setText(QLocale(QLocale::English).toString(std::stoi(p->price) * quanityPd->text().toULongLong()) + "đ");
            amountPd->setFont(QFont("Arial",18));
            amountPd->setGeometry(1600,90,300,40);
            amountPd->setStyleSheet("color:red;");
            amountPd->setObjectName(QString::fromStdString(i->codePd));

            formpd->addWidget(contentPd,0,0,2,20);
            listPd->setRowMinimumHeight(dem,200);
            listPd->addLayout(formpd,dem,0);
            dem++;
        }
    }
    Bill->setText(QLocale(QLocale::English).toString(sum)+"đ");

    connect(selectProduct,&QSignalMapper::mappedWidget,this,&cartWidget::clickSelect);
    connect(mapEditQuanity,&QSignalMapper::mappedWidget,this,&cartWidget::clickEditQuanity);
}

void cartWidget::clickEditQuanity(QWidget* contentPd)
{
    QLineEdit* quanityPdChange = contentPd->findChild<QLineEdit*>(contentPd->objectName());

    for (int i = 0;i  < quanityPdChange->text().length();++i) {
        if((quanityPdChange->text()[i] >= '0' && quanityPdChange->text()[i] <= '9')==false)
        {
            QMessageBox::information(this,"Thông báo","Lỗi nhập số lượng.");
            quanityPdChange->setText("1");
            break;
        }
    }

    QLabel* amountPdChange = contentPd->findChild<QLabel*>(contentPd->objectName());
    QString str  = amountPdChange->text();
    str.remove(str.length()-1,1);
    qlonglong x = str.split(",").join("").toLongLong();

     qlonglong PRICE = std::stoi(DataPd.getPoiter(contentPd->objectName().toStdString())->price);

    amountPdChange->setText(QLocale(QLocale::English).toString(PRICE* quanityPdChange->text().toInt())+"đ");

    QCheckBox* select = contentPd->findChild<QCheckBox*>(contentPd->objectName());

   if(select->isChecked())
   {

       sum -= x;
        sum += PRICE*quanityPdChange->text().toUInt();
       Bill->setText(QLocale(QLocale::English).toString(sum)+"đ");
   }

    auto p = Data.getPoiter(contentPd->objectName().toStdString());

    p->quanity=quanityPdChange->text().toLongLong();
    save(Data,username.toStdString());
}

void cartWidget::clickSelect(QWidget* contentPd)
{
    QCheckBox* select = contentPd->findChild<QCheckBox*>(contentPd->objectName());

    auto p = Data.getPoiter(contentPd->objectName().toStdString());
//    qlonglong s = p->quanity * std::stoi(DataPd.getPoiter(contentPd->objectName().toStdString())->price);


    QLabel* amountPdChange = contentPd->findChild<QLabel*>(contentPd->objectName());
    QString str  = amountPdChange->text();
    str.remove(str.length()-1,1);
    qlonglong x = str.split(",").join("").toLongLong();


    if(select->isChecked())
    {
        sum += x;
        listProductBuy.append(QString::fromStdString(p->codePd));
    }
    else
    {
        sum -= x;
        listProductBuy.removeOne(QString::fromStdString(p->codePd));
    }
    Bill->setText(QLocale(QLocale::English).toString(sum)+"đ");
    p->select = select->isChecked() ? 1 : 0 ;
    save(Data,username.toStdString());
}

void cartWidget::clickRm(QWidget* contentPd)
{

    if(QMessageBox::information(this,"","Bạn có chắc xóa sản phẩm này ra khỏi giỏ hàng", "Đồng ý","Không đồng ý")==1) return;

     QCheckBox* select = contentPd->findChild<QCheckBox*>(contentPd->objectName());
     auto  p = Data.getPoiter(contentPd->objectName().toStdString());
      if(select->isChecked())
      {
           listProductBuy.append(QString::fromStdString(p->codePd));
      }


    Data.remove(p);
    save(Data,username.toStdString());


    Data.~cart();
    init(Data,username.toStdString());
    printCart();
}
void cartWidget::clickSub(QWidget* contentPd)
{
    QLineEdit* quanityPdChange = contentPd->findChild<QLineEdit*>(contentPd->objectName());

    quanityPdChange->setText(QString::number(quanityPdChange->text().toUInt()-1));
    if(quanityPdChange->text().toInt()==0)
    {
        if( QMessageBox::warning(this,"","Bạn muốn xóa ra khỏi giỏ hàng",QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
        {
            auto p = Data.getPoiter(contentPd->objectName().toStdString());
            Data.remove(p);
            save(Data,username.toStdString());
            qDeleteAll(ui->cartContent->children());
            printCart();
            return;
        }
        quanityPdChange->setText(QString::number(1));
    }

    QLabel* amountPdChange = contentPd->findChild<QLabel*>(contentPd->objectName());

    qlonglong PRICE = std::stoi(DataPd.getPoiter(contentPd->objectName().toStdString())->price);

    amountPdChange->setText(QLocale(QLocale::English).toString(PRICE* quanityPdChange->text().toInt())+"đ");

    QCheckBox* select = contentPd->findChild<QCheckBox*>(contentPd->objectName());

    if(select->isChecked())
    {
        sum -= PRICE;
        Bill->setText(QLocale(QLocale::English).toString(sum)+"đ");
    }

    auto p = Data.getPoiter(contentPd->objectName().toStdString());
    p->quanity = quanityPdChange->text().toLongLong();
    save(Data,username.toStdString());


}

void cartWidget::clickAdd(QWidget* contentPd)
{
    QLineEdit* quanityPdChange = contentPd->findChild<QLineEdit*>(contentPd->objectName());

    quanityPdChange->setText(QString::number(quanityPdChange->text().toUInt()+1));

    QLabel* amountPdChange = contentPd->findChild<QLabel*>(contentPd->objectName());

     qlonglong PRICE = std::stoi(DataPd.getPoiter(contentPd->objectName().toStdString())->price);

    amountPdChange->setText(QLocale(QLocale::English).toString(PRICE* quanityPdChange->text().toInt())+"đ");

    QCheckBox* select = contentPd->findChild<QCheckBox*>(contentPd->objectName());

   if(select->isChecked())
   {
       sum += PRICE;
       Bill->setText(QLocale(QLocale::English).toString(sum)+"đ");
   }

    auto p = Data.getPoiter(contentPd->objectName().toStdString());

    p->quanity=quanityPdChange->text().toLongLong();
    save(Data,username.toStdString());

}
