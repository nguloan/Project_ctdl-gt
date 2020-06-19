#include "madeindialog.h"
#include"ui_madeindialog.h"

madeinDialog::madeinDialog(QWidget *parent) : QDialog(parent), ui(new Ui::madeinDialog)
{
    QWidget* background = new QWidget(this);
    background->setStyleSheet("background-color:#F4F6F7;");
    background->setGeometry(QRect(0,0,2000,1100));

    this->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));

    init(DATA);
    ui->setupUi(this);
        this->setWindowTitle("Danh sách nơi xuất xứ");
    this->setModal(true);
    print();
    connect(ui->add,&QPushButton::clicked,this,&madeinDialog::add);
    connect(ui->remove,&QPushButton::clicked,this,&madeinDialog::remove);
    connect(ui->table,&QListWidget::itemPressed,this,&madeinDialog::select);
    connect(ui->edit,&QPushButton::clicked,this,&madeinDialog::edit);
    itemSelect = new QListWidgetItem("");
}

madeinDialog::~madeinDialog()
{
    delete ui;
}

void madeinDialog::edit()
{
    if(itemSelect->text()=="")
    {
        return;
    }
    if(QMessageBox::information(this,"Thông báo","Bạn có chắc chắn muốn sửa "+strSelect,"Có","Không")==1)
    {
        return;
    }

    editDialog = new QDialog(this);
    editDialog->show();
    editDialog->resize(600,350);

    editDialog->setModal(true);

    QWidget* background = new QWidget(editDialog);
    background->setStyleSheet("background-color:#F4F6F7;");
    background->setGeometry(QRect(0,0,2000,1100));
    editDialog->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));
    editDialog->setWindowTitle("Sửa tên nơi xuất xứ "+strSelect);

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
    l1->setGeometry(30,200,200,30);
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
           QMessageBox::warning(this,"Báo lỗi","Tên của nơi sản xuất này đã tồn tại","Đóng");
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
        if(DATA.checkName(strSelect.toStdString()))
        {
            QMessageBox::information(this,"Thông báo","Nơi xuất xứ này đã tồn tại","Đóng");
            return;
        }

        p->name = strSelect.toStdString();
        save(DATA);

        QMessageBox::information(this,"Thông báo"," sửa thành công","Đóng");
        this->accept();
    }
}

void madeinDialog::print()
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

void madeinDialog::select(QListWidgetItem* temp)
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

void madeinDialog::remove()
{
    if(itemSelect->text() == " ")
    {
        return;
    }
    Products dataProduct;
    init(dataProduct);
    QString s = itemSelect->text();
    for(int i = 0 ;i<s.length();++i)
    {
        if(s[i] == ' ')
        {
            s.remove(0,i+1);
            break;
        }
    }

    if(dataProduct.checkMadein(s.toInt()))
    {
        QMessageBox::warning(this,"Báo lỗi","Đã có sản phẩm đang sử dụng mã xuất xứ "+strSelect+", xóa thất bại","Tôi đã hiểu");
        return;
    }

    auto p = DATA.getPoiter(strSelect.toStdString());
    DATA.remove(p);
    ui->table->removeItemWidget(itemSelect);
    save(DATA);

    QMessageBox::information(this,"Thông báo","Đã xóa thành công "+ strSelect);
    this->accept();
}

void madeinDialog::add()
{

    addDialog = new QDialog(this);

    addDialog->show();
    addDialog->resize(600,350);
    addDialog->setModal(true);
    QWidget* background = new QWidget(addDialog);
    background->setGeometry(QRect(0,0,2000,1100));
    background->setStyleSheet("background-color:#F4F6F7;");
    addDialog->setWindowTitle("Thêm nơi xuất xứ");
    addDialog->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));


    QLabel* icon = new QLabel(addDialog);
    icon->setGeometry(0,0,500,200);
    QPixmap ICON("E:/Project/MyProject/photo/yes24.png");
    icon->setPixmap(ICON);
    icon->show();

    QLineEdit* addMadein = new QLineEdit(addDialog);
    addMadein->show();
    addMadein->setGeometry(200,200,200,30);
    QLabel* l1 = new QLabel(addDialog);
    l1->setGeometry(30,200,200,30);
    l1->setText("Tên sản xuất mới: ");
    l1->show();
    l1->setFont(QFont("Arial",10));

    QPushButton * btnOk = new QPushButton("Đồng ý",addDialog),
            *btnCancel = new QPushButton("Hủy",addDialog);
    btnOk->setGeometry(QRect(300,250,100,30));
    btnOk->show();
    btnCancel->show();
    btnCancel->setGeometry(QRect(400,250,100,30));

    connect(btnCancel,&QPushButton::clicked,[this]{addDialog->reject();});
    connect(btnOk,&QPushButton::clicked,[this]{

       if(QMessageBox::information(this,"Thông báo","Bạn có chắc chắn chưa?" , "Có","Không") == 1)
       {
           return;
       }
       addDialog->accept();
    });
    if(addDialog->exec() == QDialog::Accepted)
    {
        if(DATA.checkName(addMadein->text().toStdString()))
        {
            QMessageBox::information(this,"Thông báo","Đã tồn tại nơi xuất xứ này","Đóng");
            return;
        }
        DATA.add(addMadein->text().toStdString());
        save(DATA);
        QMessageBox::information(this,"Thông báo","Đã thêm thành công","Đóng");
        this->accept();
    }
}



