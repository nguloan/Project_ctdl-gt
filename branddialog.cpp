#include "branddialog.h"
#include "ui_branddialog.h"

brandDialog::~brandDialog()
{
    delete ui;
}

brandDialog::brandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::brandDialog)
{
    QWidget* background = new QWidget(this);
    background->setStyleSheet("background-color:#F4F6F7;");    background->setGeometry(QRect(0,0,2000,1100));

    this->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));
    init(DATA);
    ui->setupUi(this);
    this->setWindowTitle("Danh sách thương hiệu");
    print();
    connect(ui->add,&QPushButton::clicked,this,&brandDialog::add);
    connect(ui->remove,&QPushButton::clicked,this,&brandDialog::remove);
    connect(ui->table,&QListWidget::itemPressed,this,&brandDialog::select);
    connect(ui->edit,&QPushButton::clicked,this,&brandDialog::edit);
    itemSelect = new QListWidgetItem("");
    this->setModal(true);

}

void brandDialog::select(QListWidgetItem* temp)
{
    itemSelect = temp;
    strSelect = itemSelect->text();

    for(int i =0 ;i<strSelect.length();i++)
    {
        if(strSelect[i] == ' ')
        {
            strSelect.remove(0,i+1);
            break;
        }
    }
}

void brandDialog::edit()
{
    if(itemSelect->text()=="")
    {
        return;
    }
    if(QMessageBox::information(this,"Sửa đổi tên thương hiệu","Bạn có chắc chắn muốn sửa "+strSelect,"Có","Không")==1)
    {
        return;
    }

    editDialog = new QDialog(this);
    editDialog->show();
    editDialog->resize(600,350);

    QLabel* icon = new QLabel(editDialog);
    icon->setGeometry(0,0,500,200);
    QPixmap ICON("E:/Project/MyProject/photo/yes24.png");
    icon->setPixmap(ICON);
    icon->show();


    auto p = DATA.getPoiter(strSelect.toStdString());

    newEdit = new QLineEdit(strSelect,editDialog);
    newEdit->show();
    newEdit->setGeometry(200,200,200,30);
    QLabel* l1 = new QLabel(editDialog);
    l1->setGeometry(10,200,180,30);
    l1->setText("Tên thương hiệu mới: ");
    l1->show();
    l1->setFont(QFont("Arial",10));

    QPushButton * btnOk = new QPushButton("Đồng ý",editDialog),
            *btnCancel = new QPushButton("Hủy",editDialog);
    btnOk->setGeometry(QRect(300,250,100,30));
    btnOk->show();
    btnCancel->show();
    btnCancel->setGeometry(QRect(400,250,100,30));

    connect(btnCancel,&QPushButton::clicked,[this]{editDialog->reject();});
    connect(btnOk,&QPushButton::clicked,[this]{
       if(DATA.check(newEdit->text().toStdString()))
       {
           QMessageBox::warning(this,"Báo lỗi","Tên thương hiệu này đã tồn tại");
           return;
       }
       if(QMessageBox::information(this,"Thông báo","Bạn có chắc chắn chưa?" , "Có","Không") == 1)
       {
           return;
       }
       strSelect = newEdit->text();
       editDialog->accept();
    });
    if(editDialog->exec() == QDialog::Accepted)
    {
        p->name = strSelect.toStdString();
        save(DATA);
        this->accept();
    }
}

void brandDialog::remove()
{
    if(itemSelect->text() == " ")
    {
        return;
    }
    Products dataProduct;
    init(dataProduct);
    if(dataProduct.checkBrand(strSelect.toStdString()))
    {
        QMessageBox::warning(this,"Báo lỗi","Đã có sản phẩm đang sử dụng thương hiệu"+strSelect+", xóa thất bại");
        return;
    }

    auto p = DATA.getPoiter( strSelect.toStdString());
    DATA.remove(p);
    ui->table->removeItemWidget(itemSelect);
    save(DATA);

    QMessageBox::information(this,"Thông báo","Đã xóa thành công "+ strSelect);
    this->accept();
}

void brandDialog::print()
{
    ui->table->clear();
    int i =0;
    for (auto p = DATA.getHead();p!=NULL;p=p->next) {
        QListWidgetItem* Item0 = new QListWidgetItem(QString::number(p->id)+" "+QString::fromStdString(p->name));

        Item0->setFont(QFont("Arial",10));
        ui->table->insertItem(i,Item0);
        i++;
    }
}

void brandDialog::add()
{
    dialogAddBrand *w = new dialogAddBrand(NULL);
    w->show();

    if(w->exec()==dialogAddBrand::Accepted)
    {
        DATA.~brand();
        QMessageBox::information(this,"Thông báo","Đã thêm thành công","Đóng");

        this->accept();

    }

}


