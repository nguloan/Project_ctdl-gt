#include "addpd.h"
#include "ui_addpd.h"

addPd::addPd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPd)
{
    init(dataPd);
    QWidget* background = new QWidget(this);
    background->setStyleSheet("background-color:#F4F6F7;");    background->setGeometry(QRect(0,0,2000,1100));

    this->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));

    ui->setupUi(this);
    connect(ui->addPhoto,&QPushButton::clicked,this,&addPd::clickAddPhoto);
    this->setWindowTitle("Thêm sản phẩm");
    QPixmap photoPd("E:/Project/MyProject/photo/productImage.png");
    ui->photoPd->setPixmap(photoPd.scaled(400,400));

    this->setModal(true);

    ui->id1->setText("00000000"+QString::fromStdString(std::to_string( dataPd.length())));

    ui->id1->setEnabled(false);
    for (auto p = dataPd.listBrand.getHead();p!=NULL;p=p->next) {
        ui->brand1->addItem(QString::fromStdString(p->name));
    }

    for (auto p = dataPd.listMadein.getHead();p!=NULL;p= p->next) {
        ui->madein1->addItem(QString::fromStdString(p->name));
    }

    for(auto p = dataPd.listCate.getHead();p!=NULL;p= p->next)
    {
        ui->category1->addItem(QString::fromStdString(p->name));
    }

    connect(ui->category1,&QComboBox::currentTextChanged,this,&addPd::updateCate);
    connect(ui->kind1,&QComboBox::currentTextChanged,this,&addPd::updateKind);
    connect(ui->madein1,&QComboBox::currentTextChanged,this,&addPd::updateMadein);
    connect(ui->brand1,&QComboBox::currentTextChanged,this,&addPd::updateBrand);
    updateCate();
}

addPd::~addPd()
{
    delete ui;
}

void addPd::updateKind(){
    QString id = ui->id1->text();

    int ret =  dataPd.listKind.getCode(ui->kind1->currentText().toStdString()) ;

    id = id.left(2) + (ret < 10 ? "0":"" ) + QString::number(ret)  +  id.mid(4,id.length()-4);
    ui->id1->setText(id);
}

void addPd::updateBrand()
{
    std::string id = ui->id1->text().toStdString();

    id = id.substr(0,4) + (ui->brand1->currentIndex() < 10 ? "0":"" ) +  std::to_string(ui->brand1->currentIndex())  +  id.substr(6,id.length()-6);
    ui->id1->setText(QString::fromStdString(id));
}


void addPd::updateMadein()
{
    std::string id = ui->id1->text().toStdString();

    id = id.substr(0,6) + (ui->madein1->currentIndex() < 10 ? "0":"" ) +  std::to_string(ui->madein1->currentIndex())  +  id.substr(8,id.length()-8);
    ui->id1->setText(QString::fromStdString(id));
}


void addPd::updateCate()
{
    std::string id = ui->id1->text().toStdString();

    id = (ui->category1->currentIndex() < 10 ? "0":"" ) +  std::to_string(ui->category1->currentIndex())  + id.substr(2,id.length()-2);
    ui->kind1->clear();
    ui->id1->setText(QString::fromStdString(id));
    for (auto p = dataPd.listKind.getHead();p!=NULL;p=p->next) {
        if(p->idCate==ui->category1->currentIndex())  ui->kind1->addItem(QString::fromStdString(p->name));
    }
    ui->kind1->setCurrentIndex(0);
}

void addPd::clickAddPhoto()
{
    file  = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    if(file=="") return;
    QPixmap photoPd(file);
    ui->photoPd->setPixmap(photoPd.scaled(400,400,Qt::KeepAspectRatio));
}

void addPd::on_Apply_clicked()
{
    if (QMessageBox::information(this,"","Bạn có chắc chắn?","Có","Không") == 1) return;

    if(ui->name1->text()==""){
        QMessageBox::warning(this,"","Tên sản phẩm không được để trống");
        return;
    }

    if(ui->price1->text()=="")
    {
        QMessageBox::warning(this,"","Giá sản phẩm không được để trống");
        return;
    }

    std::string check = ui->price1->text().toStdString();
    for (std::string::iterator it = check.begin(); it != check.end(); ++it) {
         if  ( isdigit(*it)==false)
         {
             QMessageBox::warning(this,"","Giá sản phẩm không được có ký tự anphabe");
             return;
         }
    }

    check = ui->quanity->text().toStdString();
    for (std::string::iterator it = check.begin(); it != check.end(); ++it) {
         if  ( isdigit(*it)==false)
         {
             QMessageBox::warning(this,"","Số lượng sản phẩm không được có ký tự anphabe");
             return;
         }
    }
    dataPd.insert(ui->id1->text().toStdString(),ui->name1->text().toStdString(),ui->price1->text().toStdString(),ui->quanity->text().toInt());

      fileNew = QString("E:/Project/MyProject/photoProducts/%1.png").arg(ui->id1->text()) ;


      if(file!="") {
          if(QFile::exists(fileNew))
          {
              QFile::remove(fileNew);
          }

          if( QFile::copy(file,fileNew)==false )
          {
              QMessageBox::warning(this,"","Thêm hình ảnh sản phẩm thất bại");
          }
      }
      ui->name1->setText("");
      ui->price1->setText("");
      ui->brand1->setCurrentIndex(0);
      ui->madein1->setCurrentIndex(0);
      ui->category1->setCurrentIndex(0);
      ui->quanity->setText("");
      file="";
      save(dataPd);
      this->accept();
}


void addPd::on_pushButton_clicked()
{
    this->reject();
}
