#include "editproduct.h"
#include "ui_editproduct.h"

EditProduct::EditProduct(std::string str,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProduct)
{


    QWidget* background = new QWidget(this);
    background->setStyleSheet("background-color:#F4F6F7;");
    background->setGeometry(QRect(0,0,2000,1100));

    this->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));
    init(dataPd);
    strId = str;

    this->setModal(true);


    initphlist(dataOrders);
    node* ptr = dataPd.getPoiter(str);
    ui->setupUi(this);
    ui->id->setText(QString::fromStdString(ptr->id)); // setText
    ui->id->setEnabled(false);
    this->setWindowTitle("Chi tiết sản phẩm về "+ QString::fromStdString(ptr->id));
    ui->name->setText(QString::fromStdString(ptr->name));
    ui->price->setText(QString::fromStdString(ptr->price));
    ui->quanity->setText(QString::number(ptr->quanity));
    file = QString("E:/Project/MyProject/photoProducts/%1.png").arg(QString::fromStdString(ptr->id));

    if(QFile::exists(file)==false)
    {
        file = "E:/Project/MyProject/photo/imageNotFound.png";
    }

    fileTemp = file;

    QPixmap photoPd(file);
    ui->photo->setPixmap(photoPd.scaled(350,350,Qt::KeepAspectRatio));

    for (auto p = dataPd.listCate.getHead();p!=NULL;p=p->next) {
        ui->category->addItem(QString::fromStdString(p->name));
    }

    for (auto p = dataPd.listBrand.getHead();p!=NULL;p=p->next) {
        ui->brand->addItem(QString::fromStdString(p->name));
    }

    for (auto p = dataPd.listMadein.getHead();p!=NULL;p=p->next) {
        ui->madein->addItem(QString::fromStdString(p->name));
    }


    for (auto p = dataPd.listKind.getHead();p!=NULL;p=p->next) {
        if(p->idCate==ui->category->currentIndex())  ui->kind->addItem(QString::fromStdString(p->name));
    }

    if(ptr->disable==1) ui->disable->setChecked(true);
    else ui->enable->setChecked(true);

    connect(ui->category,&QComboBox::currentTextChanged,this,&EditProduct::Category);
    connect(ui->kind,&QComboBox::currentTextChanged,this,&EditProduct::Kind);
    connect(ui->brand,&QComboBox::currentTextChanged,this,&EditProduct::Brand);
    connect(ui->madein,&QComboBox::currentTextChanged,this,&EditProduct::Madein);

//     Category();

    ui->category->setCurrentText(QString::fromStdString(ptr->category));
    ui->kind->setCurrentText(QString::fromStdString(ptr->kind));
    ui->brand->setCurrentText(QString::fromStdString(ptr->brand));
    ui->madein->setCurrentText(QString::fromStdString(ptr->madein));

    connect(ui->editPhoto,&QPushButton::clicked,this,&EditProduct::EditPhoto);
}

void EditProduct::Category()
{
    QString id = ui->id->text();


        ui->kind->clear();

        for (auto p = dataPd.listKind.getHead();p!=NULL;p=p->next) {
            if(p->idCate==ui->category->currentIndex())  ui->kind->addItem(QString::fromStdString(p->name));
        }


        ui->kind->setCurrentIndex(0);
        if(ui->kind->currentText() == "")
        {
            QMessageBox::information(this,"Thông báo lỗi", "Danh mục chưa có phân loại, vui lòng thêm phân loại cho "+ui->category->currentText());
            ui->category->setCurrentIndex(id.left(2).toInt());
            return;
        }


       id = (ui->category->currentIndex() < 10 ? "0":"" ) +  QString::number(ui->category->currentIndex())  + id.mid(2,id.length()-2);
        ui->id->setText(id);
}

void EditProduct::Brand()
{
    std::string id = ui->id->text().toStdString();

      id = id.substr(0,4) + (ui->brand->currentIndex() < 10 ? "0":"" ) +  std::to_string(ui->brand->currentIndex())  +  id.substr(6,id.length()-6);
      ui->id->setText(QString::fromStdString(id));
}

void EditProduct::Madein()
{
    std::string id = ui->id->text().toStdString();

       id = id.substr(0,6) + (ui->madein->currentIndex() < 10 ? "0":"" ) +  std::to_string(ui->madein->currentIndex())  +  id.substr(8,id.length()-8);
       ui->id->setText(QString::fromStdString(id));
}

void EditProduct::Kind()
{

    QString id = ui->id->text();

    int t = dataPd.listKind.getCode(ui->kind->currentText().toStdString());


    id = id.left(2) + (t < 10 ? "0":"" ) + QString::number(t)   +  id.mid(4,id.length()-4);
    ui->id->setText(id);
}

EditProduct::~EditProduct()
{
    delete ui;
}

void EditProduct::EditPhoto()
{

    QString check  = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));

    if(check == "") return;

    file = check;

    QPixmap photoPd(file);
    ui->photo->setPixmap(photoPd.scaled(300,300,Qt::KeepAspectRatio));
}

void EditProduct::on_apply_clicked()
{
    if (QMessageBox::information(this,"","Bạn có chắc chắn?",QMessageBox::Yes|QMessageBox::No) == QMessageBox::No) return;
       if(ui->name->text()==""){
           QMessageBox::warning(this,"","Tên sản phẩm không được để trống");
           return;
       }

         if(ui->price->text()=="")
       {
           QMessageBox::warning(this,"","Giá sản phẩm không được để trống");
           return;
       }
         std::string price = ui->price->text().toStdString();
         for (std::string::iterator it = price.begin(); it != price.end(); ++it) {
           if  ( isdigit(*it)==false)
           {
               QMessageBox::warning(this,"","Giá sản phẩm không được có ký tự anphabe");
               return;
           }
       }
         fileNew = QString("E:/Project/MyProject/photoProducts/%1.png").arg(ui->id->text());


         if(file !="" ) {
                QFile::copy(file,fileNew);
          }
         auto p = dataPd.getPoiter(strId);
         p->id = ui->id->text().toStdString();
         p->name = ui->name->text().toStdString();
         p->price = ui->price->text().toStdString();
         p->quanity = ui->quanity->text().toInt();
         p->disable = ui->disable->isChecked() ? 1 : 0;
      save(dataPd);
      this->accept();
      return;
}



void EditProduct::on_deletePd_clicked()
{
    if (QMessageBox::information(this,"Thông báo","Bạn có chắc chắn?","Có","Không") == 1) return;

    if(dataOrders.checkIdProduct(QString::fromStdString(strId)))
    {
        QMessageBox::warning(this,"Thông báo","Sản phẩm không thể xóa");
        return;
    }
    auto p  = dataPd.getPoiter(strId);
    dataPd.remove(p);
    save(dataPd);
    this->accept();
}


