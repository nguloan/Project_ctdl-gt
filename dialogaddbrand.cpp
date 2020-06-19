#include "dialogaddbrand.h"
#include "ui_dialogaddbrand.h"

dialogAddBrand::dialogAddBrand(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddBrand)
{
    QWidget* background = new QWidget(this);
    background->setStyleSheet("background-color:#F4F6F7;");
    background->setGeometry(QRect(0,0,2000,1100));

    this->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));

    this->setModal(true);
    ui->setupUi(this);
     this->setWindowTitle("Thêm thương hiệu");
    connect(ui->pushButton,&QPushButton::clicked,this,&dialogAddBrand::add);
    init(DataBrand);
    QPixmap avt("E:/Project/MyProject/photo/yes24.png");
    ui->icon->setPixmap(avt);
    QPixmap icon("E:/Project/MyProject/photo/warning.png");
    ui->icon_2->setPixmap(icon);
    ui->icon_2->hide();
    ui->label_3->hide();
    newBrand = new QLineEdit(this);
    newBrand->setGeometry(QRect(200,90,250,30));
}

dialogAddBrand::~dialogAddBrand()
{
    delete ui;
}

void dialogAddBrand::add()
{
    QString s =  newBrand->text().toUpper();
    if(DataBrand.check(s.toStdString()))
    {
        ui->icon_2->show();
        ui->label_3->show();
        return;
    }
    DataBrand.add(newBrand->text().toUpper().toStdString());
    save(DataBrand);
    this->accept();

}
