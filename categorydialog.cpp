#include "categorydialog.h"
#include"ui_categorydialog.h"

categoryDialog::categoryDialog(QWidget *parent) : QDialog(parent),    ui(new Ui::categoryDialog)
{

    QWidget* background = new QWidget(this);
    background->setStyleSheet("background-color:#F4F6F7;");    background->setGeometry(QRect(0,0,2000,1100));

    this->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));

    init(DATAcate);
    init(DATAkind);
    ui->setupUi(this);

    this->setModal(true);
     this->setWindowTitle("Danh mục và phẩn loại sản phẩm");

    connect(ui->add,&QPushButton::clicked,this,&categoryDialog::add);
    ui->add->setIcon(QIcon("E:/Project/MyProject/photo/them.png"));
    ui->add1->setIcon(QIcon("E:/Project/MyProject/photo/them.png"));
    ui->remove->setIcon(QIcon("E:/Project/MyProject/photo/sub.png"));
    ui->remove1->setIcon(QIcon("E:/Project/MyProject/photo/sub.png"));
    ui->edit->setIcon(QIcon("E:/Project/MyProject/photo/chinhsua.png"));
    ui->edit1->setIcon(QIcon("E:/Project/MyProject/photo/chinhsua.png"));

    connect(ui->table,&QListWidget::itemPressed,this,&categoryDialog::select);
    connect(ui->remove,&QPushButton::clicked,this,&categoryDialog::remove);
    connect(ui->edit,&QPushButton::clicked,this,&categoryDialog::edit);

    connect(ui->table1,&QListWidget::itemPressed,this,&categoryDialog::selectKind);
    connect(ui->add1,&QPushButton::clicked,this,&categoryDialog::addKind);
    connect(ui->remove1,&QPushButton::clicked,this,&categoryDialog::removeKind);
    connect(ui->edit1,&QPushButton::clicked,this,&categoryDialog::editKind);
    selectItem = new QListWidgetItem("");
    selectItemKind = new QListWidgetItem("");
    print();

}

void categoryDialog::selectKind(QListWidgetItem* temp)
{
    selectItemKind = temp;
}

void categoryDialog::editKind()
{
    QString str = selectItemKind->text();
    if(str=="")
    {
        return;
    }

    for (int i =0;i<str.length();++i) {
        if(str[i]==' ')
        {
            str.remove(0,i+1);
            break;
        }
    }

   if( QMessageBox::information(this,"Thông báo","Bạn có chắc chắn muốn sửa tên "+str,"Có","Không" ) == 1)
   {
       return;
   }

   QDialog* editCate = new QDialog(this);
   editCate->setModal(true);
   editCate->show();
   editCate->resize(700,350);
   editCate->setGeometry(QRect(500,300,800,400));

   QWidget* background = new QWidget(editCate);
   background->setStyleSheet("background-color:#F4F6F7;");    background->setGeometry(QRect(0,0,2000,1100));
    background->show();
   editCate->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));
   editCate->setWindowTitle("Sửa tên phân loại "+str);

   QPixmap icon("E:/Project/MyProject/photo/yes24.png");

   QLabel* l1 = new QLabel(editCate);
   l1->show();
   l1->setPixmap(icon);
   l1->setGeometry(QRect(0,0,600,250));

   QLabel* l2 = new QLabel(editCate);
   l2->setGeometry(QRect(30,260,210,30));
   l2->show();
   l2->setText("Nhập tên danh mục mới");
   l2->setFont(QFont("Arial",11));

   QLineEdit* editLineEdit = new QLineEdit(str,editCate);
   editLineEdit->setGeometry(QRect(240,260,300,30));
   editLineEdit->show();

   QPushButton* btnOk = new QPushButton("Đồng ý",editCate);
   btnOk->setGeometry(QRect(550,260,100,30));
   btnOk->show();
   btnOk->setDefault(true);
   connect(btnOk,&QPushButton::clicked,[editCate]{
     if(  QMessageBox::information(editCate,"Thông báo","Bạn có chắc chắn muốn sửa ?", "Có","Không") == 1) return;
       editCate->accept();
   });

   QPushButton* btnCancel = new QPushButton("Hủy",editCate);
   btnCancel->setGeometry(QRect(660,260,100,30));
   btnCancel->show();
   connect(btnCancel,&QPushButton::clicked,[editCate]{
      editCate->reject();
   });

   if(editCate->exec() == QDialog::Accepted)
   {
       QString str = editLineEdit->text().toUpper();
       if(DATAkind.checkName(str.toStdString()))
       {
           QMessageBox::information(this,"Thông báo","Đã tồn tên phân này","Tôi đã hiểu");
           return;
       }

       QString s = selectItemKind->text();
       for (int i = 0;i<s.length();++i) {
           if(s[i] == ' ')
           {
               s.remove(i,s.length());
               break;
           }
       }

       auto p = DATAkind.getPoiter(s.toInt());
       p->name = editLineEdit->text().toUpper().toStdString();
       save(DATAkind);
      QMessageBox::information(this,"Thông báo","Sửa thành công","Đóng");
      this->accept();

   }
}

void categoryDialog::removeKind()
{
    if(selectItemKind->text() == "")
    {
        return;
    }
    if(QMessageBox::information(this,"Thông báo","Bạn có chắc chắn muốn xóa ?", "Có","Không") == 1) return;
    QString s = selectItemKind->text(), x = selectItemKind->text();
    for (int i = 0;i<s.length();++i) {
        if(s[i] == ' ')
        {
            s.remove(i,s.length());
            x.remove(i+1,x.length());
            break;
        }
    }
    Products dataB;
    init(dataB);

    if(dataB.checkKind(s.toInt()))
    {
        QMessageBox::warning(this,"Báo lỗi","Danh mục "+x+" xóa thất bại");
        return;
    }

    auto p = DATAkind.getPoiter(s.toInt());
    if(p==NULL)
    {
        QMessageBox::warning(this,"Báo lỗi","Không tìm thấy danh mục, liên hệ admin");
        return;
    }
    DATAkind.remove(p);
    save(DATAkind);
     QMessageBox::information(this,"Thông báo","Đã xóa thành công danh mục "+x);

    this->accept();



}

void categoryDialog::addKind()
{
    QDialog* addCate = new QDialog(this);
    addCate->show();
    addCate->resize(700,350);
    addCate->setGeometry(QRect(500,300,800,400));
    addCate->setModal(true);

    QWidget* background = new QWidget(addCate);
    background->setStyleSheet("background-color:#F4F6F7;");    background->setGeometry(QRect(0,0,2000,1100));
    background->show();
    addCate->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));
    addCate->setWindowTitle("Thêm phân loại");

    QPixmap icon("E:/Project/MyProject/photo/yes24.png");

    QLabel* l1 = new QLabel(addCate);
    l1->show();
    l1->setPixmap(icon);
    l1->setGeometry(QRect(0,0,600,250));

    QLabel* l2 = new QLabel(addCate);
    l2->setGeometry(QRect(30,260,210,30));
    l2->show();
    l2->setText("Nhập mới");
    l2->setFont(QFont("Arial",11));

    QLineEdit* addLineEdit = new QLineEdit(addCate);
    addLineEdit->setGeometry(QRect(240,260,300,30));
    addLineEdit->show();

    QPushButton* btnOk = new QPushButton("Đồng ý",addCate);
    btnOk->setGeometry(QRect(550,260,100,30));
    btnOk->show();
    btnOk->setDefault(true);
    connect(btnOk,&QPushButton::clicked,[addCate]{
      if(  QMessageBox::information(addCate,"Thông báo","Bạn có chắc chắn muốn thêm mới ?", "Có","Không") == 1) return;
        addCate->accept();
    });

    QPushButton* btnCancel = new QPushButton("Hủy",addCate);
    btnCancel->setGeometry(QRect(660,260,100,30));
    btnCancel->show();
    connect(btnCancel,&QPushButton::clicked,[addCate]{
       addCate->reject();
    });
    if(addCate->exec() == QDialog::Accepted)
    {
        if(DATAkind.checkName(addLineEdit->text().toUpper().toStdString()))
        {
            QMessageBox::information(this,"Thông báo","tên phân loại đã tồn tại","tôi đã hiểu");
            return;
        }

        QString idCate = selectItem->text();
        for (int i = 0;i<idCate.length();++i) {
            if(idCate[i] == ' ')
            {
                idCate.remove(i,idCate.length());
                break;
            }
        }
        DATAkind.add(addLineEdit->text().toUpper().toStdString(),idCate.toInt());
        save(DATAkind);

        QMessageBox::information(this,"Thông báo"," Đã thêm thành công","Đóng");
        this->accept();

    }
}

void categoryDialog::printKind()
{
    if(selectItem->text()=="") return;
    ui->table1->clear();

    QString s =  selectItem->text();
    for (int i = 0;i<s.length();++i) {
        if(s[i] == ' ')
        {
            s.remove(i,s.length());
            break;
        }
    }
    int i =0;
    for (auto p = DATAkind.getHead();p!=NULL;p=p->next) {
       if(p->idCate == s.toInt())
       {
           QListWidgetItem* Item0 = new QListWidgetItem(QString::number(p->idKind)+" "+QString::fromStdString(p->name));

           Item0->setFont(QFont("Arial",10));
           ui->table1->insertItem(i,Item0);
           i++;
       }
    }

}
// sửa danh mục
void categoryDialog::edit()
{
    if(strSelect == "") return;
    if(QMessageBox::information(this,"Thông báo","Bạn có chắc chắn muốn sửa ?", "Có","Không") == 1) return;


    QDialog* editKind = new QDialog(this);
    editKind->setModal(true);
    QWidget* background = new QWidget(editKind);
    background->setStyleSheet("background-color:#F4F6F7;");    background->setGeometry(QRect(0,0,2000,1100));

    editKind->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));
    editKind->setWindowTitle("Sửa tên danh mục "+strSelect);
    editKind->show();
    editKind->resize(700,350);
    editKind->setGeometry(QRect(500,300,800,400));

    QPixmap icon("E:/Project/MyProject/photo/yes24.png");

    QLabel* l1 = new QLabel(editKind);
    l1->show();
    l1->setPixmap(icon);
    l1->setGeometry(QRect(0,0,600,250));

    QLabel* l2 = new QLabel(editKind);
    l2->setGeometry(QRect(30,260,210,30));
    l2->show();
    l2->setText("Nhập sửa đổi mới mới");
    l2->setFont(QFont("Arial",11));

    QLineEdit* editLineEdit = new QLineEdit(strSelect,editKind);
    editLineEdit->setGeometry(QRect(240,260,300,30));
    editLineEdit->show();

    QPushButton* btnOk = new QPushButton("Đồng ý",editKind);
    btnOk->setGeometry(QRect(550,260,100,30));
    btnOk->show();
    btnOk->setDefault(true);
    connect(btnOk,&QPushButton::clicked,[editKind]{
      if(  QMessageBox::information(editKind,"Thông báo","Bạn có chắc chắn muốn sửa ?", "Có","Không") == 1) return;
        editKind->accept();
    });

    QPushButton* btnCancel = new QPushButton("Hủy",editKind);
    btnCancel->setGeometry(QRect(660,260,100,30));
    btnCancel->show();
    connect(btnCancel,&QPushButton::clicked,[editKind]{
       editKind->reject();
    });
     int ret = editKind->exec();
    if(ret == QDialog::Accepted)
    {
        if(editLineEdit->text() == "")
        {
            QMessageBox::information(this,"Thông báo","Tên danh mục trống","Đóng");
            return;
        }

        if(DATAcate.checkName(editLineEdit->text().toUpper().toStdString()))
        {
            QMessageBox::information(this,"Thông báo","Tên danh mục đã tồn tại","Đóng");
            return;
        }

        QString s = selectItem->text();
        for (int i = 0;i<s.length();++i) {
            if(s[i] == ' ')
            {
                s.remove(i,s.length());
                break;
            }
        }
        auto p = DATAcate.getPoiter(s.toInt());
        if(p==NULL)
        {
            QMessageBox::warning(this," báo lỗi ","lỗi không thể sửa mới được, liên hệ admin", "Đóng");
            return;
        }
        p->name = editLineEdit->text().toUpper().toStdString();
        save(DATAcate);

        QMessageBox::information(this,"Thông báo","Đã sửa thành công","Đóng");
        this->accept();

    }


}

void categoryDialog::select(QListWidgetItem *temp)
{
    selectItem = temp;
    strSelect = temp->text();
    for (int i = 0;i<strSelect.length();++i) {
        if(strSelect[i] == ' ')
        {
            strSelect.remove(0,i+1);
            break;
        }
    }
    printKind();
}

categoryDialog::~categoryDialog()
{
    delete ui;
}

void categoryDialog::print()
{
    ui->table->clear();

    int i =0;
    for (auto p = DATAcate.getHead();p!=NULL;p=p->next) {
        QListWidgetItem* Item0 = new QListWidgetItem(QString::number(p->id)+" "+QString::fromStdString(p->name));

        Item0->setFont(QFont("Arial",10));
        ui->table->insertItem(i,Item0);
        i++;
    }
}

void categoryDialog::add()
{

    QDialog* addCate = new QDialog(this);
    addCate->setModal(true);
    addCate->show();
    addCate->resize(700,350);
    addCate->setGeometry(QRect(500,300,800,400));

    QWidget* background = new QWidget(addCate);
    background->setStyleSheet("background-color:#F4F6F7;");    background->setGeometry(QRect(0,0,2000,1100));
    background->show();
    addCate->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));
    addCate->setWindowTitle("Thêm danh mục");

    QPixmap icon("E:/Project/MyProject/photo/yes24.png");

    QLabel* l1 = new QLabel(addCate);
    l1->show();
    l1->setPixmap(icon);
    l1->setGeometry(QRect(0,0,600,250));

    QLabel* l2 = new QLabel(addCate);
    l2->setGeometry(QRect(30,260,210,30));
    l2->show();
    l2->setText("Nhập tên danh mục mới");
    l2->setFont(QFont("Arial",11));

    QLineEdit* addLineEdit = new QLineEdit(addCate);
    addLineEdit->setGeometry(QRect(240,260,300,30));
    addLineEdit->show();

    QPushButton* btnOk = new QPushButton("Đồng ý",addCate);
    btnOk->setGeometry(QRect(550,260,100,30));
    btnOk->show();
    btnOk->setDefault(true);

    connect(btnOk,&QPushButton::clicked,[addCate]{

      if(  QMessageBox::information(addCate,"Thông báo","Bạn có chắc chắn muốn thêm danh mục mới ?","Có","Không") == 1) return;
        addCate->accept();
    });

    QPushButton* btnCancel = new QPushButton("Hủy",addCate);
    btnCancel->setGeometry(QRect(660,260,100,30));
    btnCancel->show();

    connect(btnCancel,&QPushButton::clicked,[addCate]{
       addCate->reject();
    });
     if(addLineEdit->text() == "")
     {
         QMessageBox::information(this,"Thông báo","Tên danh mục trống","Đóng");
         return;
     }

    if(addCate->exec() == QDialog::Accepted)
    {
        if(DATAcate.checkName(addLineEdit->text().toUpper().toStdString()))
        {
            QMessageBox::information(this,"Thông báo","Tên danh mục đã tồn tại","Đóng");
            return;
        }
        DATAcate.add(addLineEdit->text().toUpper().toStdString());
        save(DATAcate);

        QMessageBox::information(this,"Thông báo","Đã thêm thành công","Đóng");
        this->accept();
    }
  }

void categoryDialog::remove()
{
    if(selectItem->text() == "")
    {
        return;
    }
    if(QMessageBox::information(this,"Thông báo","Bạn có chắc chắn muốn xóa ?", "Có"  ,"Không") == 1) return;
    QString s = selectItem->text();
    for (int i = 0;i<s.length();++i) {
        if(s[i] == ' ')
        {
            s.remove(i,s.length());
            break;
        }
    }
    if(DATAkind.checkCate(s.toInt()))
    {
        QMessageBox::warning(this,"Báo lỗi","Danh mục "+strSelect+" xóa thất bại","Đóng");
        return;
    }


    auto p = DATAcate.getPoiter(s.toInt());
    if(p==NULL)
    {
       QMessageBox::warning(this,"Báo lỗi","Không tìm thấy danh mục, liên hệ admin");
       return;
    }

    ui->table->removeItemWidget(selectItem);
    DATAcate.remove(p);
    save(DATAcate);

    QMessageBox::information(this,"Thông báo","Đã xóa thành công danh mục "+ strSelect);
    this->accept();
}

