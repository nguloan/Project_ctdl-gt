#include "informationuser.h"
#include "ui_informationuser.h"

informationUser::informationUser(std::string username,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::informationUser)
{
    ui->setupUi(this);
    Init(DATAuser);
    Username=username;
    alignContent = new QWidget(this);
    alignContent->setGeometry(QRect(330,0,1200,700));
    alignContent->setStyleSheet("background-color:white;");

    QWidget* leftWidget = new QWidget(this);

    leftWidget->setGeometry(0,0,300,300);

    allInformationUser = new QPushButton("Thông tin chung",leftWidget);
    managerAccout = new QPushButton("Quản lý tài khoản",leftWidget);
    purchaseHistory = new QPushButton("Lịch sử mua hàng",leftWidget);

    connect(allInformationUser,&QPushButton::clicked,this,&informationUser::clickAllInfo);
    connect(managerAccout,&QPushButton::clicked,this,&informationUser::clickManageInfo);
    connect(purchaseHistory,&QPushButton::clicked,this,&informationUser::clickHistoryPay);
    this->setStyleSheet("QPushButton:hover{border: 2px solid black; background-color:white; color:black; font: bold 14px;}");

    allInformationUser->setFont(QFont("Arial",10));
    managerAccout->setFont(QFont("Arial",10));
    purchaseHistory->setFont(QFont("Arial",10));

    QLabel* label1 = new QLabel(leftWidget);
    label1->setText("TRANG CÁ NHÂN");
    label1->setFont(QFont("Arial",20));

    QVBoxLayout* leftcontent = new QVBoxLayout(leftWidget);

    leftcontent->addWidget(label1);
    leftcontent->addWidget(allInformationUser);
    leftcontent->addWidget(managerAccout);
    leftcontent->addWidget(purchaseHistory);
    clickAllInfo();

}

void informationUser::clickManageInfo()
{
    qDeleteAll(alignContent->children());

    allInformationUser->setStyleSheet("background-color:#c8d6e5;");
    managerAccout->setStyleSheet("background-color: #2e86de;");
    purchaseHistory->setStyleSheet("background-color:#c8d6e5;");

    auto poiterNode = DATAuser.getpointer(Username);

    QLabel *l1 = new QLabel(alignContent),
            *l2 = new QLabel(alignContent),
            *l3 = new QLabel(alignContent),
            *l4 = new QLabel(alignContent),
            *avt= new QLabel(alignContent),
            *l5 = new QLabel(alignContent),
            *l6 = new QLabel(alignContent),
            *l7 = new QLabel(alignContent);

    QPixmap avatar("E:/Project/MyProject/photo/avatar.png");

    avt->setPixmap(avatar.scaled(200,200,Qt::KeepAspectRatio));
    l1->setText("Tên đăng nhập: ");

    l1->show();
    l2->setText("Hình ảnh: ");
    l2->show();
    l3->setText("Họ tên: ");
    l3->show();
    l4->setText("Mật khẩu");
    l4->show();
    l5->setText("Giới tính: ");
    l5->show();
    l6->setText("Số điện thoại: ");
    l6->show();
    l7->setText("Email: ");
    l7->show();

    QLineEdit *username = new QLineEdit(alignContent),*password = new QLineEdit(alignContent);
    name = new QLineEdit(alignContent);

    numberPhone = new QLineEdit(QString::fromStdString(poiterNode->phonenumber),alignContent);
    email = new QLineEdit(QString::fromStdString(poiterNode->email),alignContent);

     nam = new QRadioButton("Nam",alignContent); nu = new QRadioButton("Nữ",alignContent);

    username->setText(QString::fromStdString(poiterNode->username));
    username->show();
    username->setEnabled(false);
    name->setText(QString::fromStdString(poiterNode->name));
    name->show();
    password->setText(QString::fromStdString(poiterNode->password));
    password->show();
    password->setEchoMode(QLineEdit::Password);
    password->setEnabled(false);
    numberPhone->show();
    email->show();
    nam->show();
    nu->show();

    l1->setGeometry(QRect(100,100,100,30));
    username->setGeometry(QRect(210,100,350,30));
    username->setFont(QFont("Arial",10));
    l2->setGeometry(QRect(100,140,100,30));
    avt->setGeometry(QRect(210,140,250,200));
    avt->show();

    l3->setGeometry(QRect(100,340,100,30));
    name->setGeometry(QRect(200,340,350,30));

    l4->setGeometry(QRect(100,380,100,30));
    password->setGeometry(QRect(200,380,350,30));
    l5->setGeometry(QRect(100,420,100,30));
    nam->setGeometry(QRect(200,420,50,30));
    nu->setGeometry(QRect(270,420,50,30));

    QPushButton* editPsswd = new QPushButton(QIcon("E:/Project/MyProject/photo/chinhsua.png"),"Đổi mật khẩu",alignContent);
    editPsswd->setGeometry(QRect(560,380,150,30));
    editPsswd->setStyleSheet("background-color: #EC2345; color:white;");
    editPsswd->show();
    editPsswd->setFont(QFont("Arial",11));
    connect(editPsswd,&QPushButton::clicked,this,&informationUser::clickEditPassword);

    poiterNode->gender?nam->setChecked(true):nu->setChecked(true);
    l6->setGeometry(QRect(100,450,100,30));
    numberPhone->setGeometry(QRect(200,450,350,30));
    l7->setGeometry(QRect(100,490,100,30));
    email->setGeometry(QRect(200,490,350,30));

    QPushButton* save = new QPushButton("Lưu",alignContent);
    save->setGeometry(QRect(200,530,100,30));
    save->setStyleSheet("background-color: #EC2345; color:white;");
    save->show();
    save->setFont(QFont("Arial",11));
    connect(save,&QPushButton::clicked, this,&informationUser::clickSave);
}

void informationUser::clickSave()
{
    for(int i = 0 ; i <numberPhone->text().length();i++)
    {
        if(!(numberPhone->text()[i]>='0' && numberPhone->text()[i]<='9'))
        {
            QMessageBox::information(this,"Thông báo","Số điện thoại không có ký tự anpha","Đóng");
            return;
        }
    }
    auto p = DATAuser.getpointer(Username);
    p->name = name->text().toUpper().toStdString();
    p->phonenumber = numberPhone->text().toStdString();
    p->gender = nam->isChecked()? 1 : 0;
    p->email = email->text().toStdString();
    save(DATAuser);
    QMessageBox::information(this,"Thông báo","Lưu thông tin thành công");
}


void informationUser::clickEditPassword()
{

    QDialog* editPassword = new QDialog(this);
   editPassword->setGeometry(QRect(800,400,500,300));
   editPassword->setModal(true);
   editPassword->show();
   editPassword->setWindowIcon(QIcon("E:/Project/MyProject/photo/iconTilte.png"));
   editPassword->setWindowTitle("Đổi mật khẩu");

   QWidget* background = new QWidget(editPassword);
   background->setStyleSheet("background-color:#F4F6F7;");
   background->setGeometry(QRect(0,0,2000,1100));
   background->show();

   QLabel* thongbao = new QLabel(editPassword);
   thongbao->setText("Quý khách vui lòng sử dụng mật khẩu có độ dài từ 6 trở lên");
   thongbao->setGeometry(QRect(10,5,490,30));
   thongbao->setFont(QFont("Arial",11));
   thongbao->show();

   QLabel* pssOld_lbl = new QLabel(editPassword);
   pssOld_lbl->setText("Mật khẩu đang sử dụng");
   pssOld_lbl->show();
   pssOld_lbl->setFont(QFont("Arial",10));
   pssOld_lbl->setGeometry(QRect(10,50,250,20));


   QLineEdit* pssOld = new QLineEdit(editPassword);
   pssOld->setEchoMode(QLineEdit::Password);
   pssOld->setGeometry(QRect(10,70,490,30));
   pssOld->show();
   pssOld->setObjectName("pssold");

   QLabel* pssNew_lbl = new QLabel(editPassword);
   pssNew_lbl->setText("Mật khẩu mới:");
   pssNew_lbl->setFont(QFont("Arial",10));
   pssNew_lbl->setGeometry(QRect(10,110,250,20));
   pssNew_lbl->show();


   QLineEdit* pssNew = new QLineEdit(editPassword);
   pssNew->setEchoMode(QLineEdit::Password);
   pssNew->setGeometry(QRect(10,130,490,30));
   pssNew->show();
   pssNew->setObjectName("pssnew");

   QLabel* rePssNew_lbl = new QLabel(editPassword);
   rePssNew_lbl->setText("Xác nhận mật khẩu mới");
   rePssNew_lbl->setGeometry(QRect(10,170,250,20));
   rePssNew_lbl->setFont(QFont("Arial",10));
   rePssNew_lbl->show();

   QLineEdit* rePssNew = new QLineEdit(editPassword);
   rePssNew->setEchoMode(QLineEdit::Password);
   rePssNew->setGeometry(QRect(10,190,490,30));
   rePssNew->show();
   rePssNew->setObjectName("repssnew");


   QPushButton* cancel = new QPushButton("Hủy",editPassword);
   cancel->setGeometry(QRect(200,250,100,30));
   cancel->show();
   cancel->setStyleSheet("border:none; color:black; background-color: white;");
   cancel->setFont(QFont("Arial",11));
   QPushButton* ok = new QPushButton("Xác Nhận",editPassword);
   ok->setGeometry(QRect(310,250,100,30));
   ok->setFont(QFont("Arial",11));
   ok->setStyleSheet("border: none; color:white; background-color:#EC2345;");
   ok->show();

   connect(cancel,&QPushButton::clicked,[editPassword]{
      editPassword->close();
   });

   connect(ok,&QPushButton::clicked,[editPassword]{


     if( editPassword->findChild<QLineEdit*>("pssold")->text() =="")
     {
         QMessageBox::information(editPassword,"Thông báo","Vui lòng nhập mật khẩu cũ","Đóng");
         return;
     }
          QString s = editPassword->findChild<QLineEdit*>("pssnew")->text();

     if(s  =="")
     {
         QMessageBox::information(editPassword,"Thông báo","Vui lòng nhập mật  khẩu mới","Đóng");
         return;
     }

     QString x = editPassword->findChild<QLineEdit*>("repssnew")->text();

     if( x=="")
     {
         QMessageBox::information(editPassword,"Thông báo","Vui lòng nhập mật khẩu xác nhận","Đóng");
         return;
     }

     if(s != x)
     {
         QMessageBox::information(editPassword,"Thông báo","Mật khẩu mới và mật khẩu xác nhận không trùng nhau","Đóng");
         return;
     }



    editPassword->accept();
   });


    if(editPassword->exec()== QDialog::Accepted)
    {
        auto p = DATAuser.getpointer(Username);
        if(p->password != DATAuser.convertPass(pssOld->text().toStdString()))
        {
            QMessageBox::information(this,"Thông báo","Mật khẩu cũ không đúng", "Đóng");
            return;
        }
        p->password = DATAuser.convertPass(pssNew->text().toStdString());
        save(DATAuser);
        QMessageBox::information(this,"Thông báo","Đổi mật khẩu thành công","Đóng");
    }
}


void informationUser::clickAllInfo()
{
    qDeleteAll(alignContent->children());

    managerAccout->setStyleSheet("background-color:#c8d6e5;");
    allInformationUser->setStyleSheet("background-color: #2e86de;");
    purchaseHistory->setStyleSheet("background-color:#c8d6e5;");

    auto poiterNode = DATAuser.getpointer(Username);
    QPixmap avatar("E:/Project/MyProject/photo/avatar.png");
    QLabel* photoAvatar = new QLabel(alignContent);
    photoAvatar->setPixmap(avatar.scaled(200,200,Qt::KeepAspectRatio));
    photoAvatar->show();
    photoAvatar->setGeometry(30,70,200,200);
    photoAvatar->setStyleSheet("border: 1px solid black; border-right:none;");
    QWidget* formWidget = new QWidget(alignContent);
    formWidget->setGeometry(230,70,400,200);
    formWidget->setStyleSheet("border: 1px solid black; border-left:none;");

    QLabel*name1 = new QLabel(this),
            *email1 = new QLabel(this),
            *dt = new QLabel(this),
            *gener1 = new QLabel(this);

    name1->setText(QString::fromStdString(poiterNode->name));
    name1->setFont(QFont("Arial",17));
    name1->setStyleSheet("border:none;");


    email1->setText("Email: "+QString::fromStdString(poiterNode->email));
    email1->setFont(QFont("Arial",10));
    email1->setStyleSheet("border:none;");
    email1->setFont(QFont("Arial",10));

    dt->setText("Số điện thoại: "+QString::fromStdString(poiterNode->phonenumber));
    dt->setFont(QFont("Arial",10));
    dt->setStyleSheet("border:none;");
    dt->setFont(QFont("Arial",10));

    gener1->setText("Giới tính: "+ QString( poiterNode->gender?"Nam":"Nữ"));
    gener1->setStyleSheet("border:none;");
    gener1->setFont(QFont("Arial",10));

    QFormLayout* formLayout = new QFormLayout(formWidget);
    formLayout->addRow(name1);
    formLayout->addRow(email1);
    formLayout->addRow(dt);
    formLayout->addRow(gener1);
    formWidget->show();
    QPushButton* clickBtnEdit = new QPushButton("Chỉnh sửa",alignContent);
    clickBtnEdit->setGeometry(QRect(250,200,100,30));

    clickBtnEdit->setStyleSheet("background-color:#B2BABB;color:white;");
    clickBtnEdit->setFont(QFont("Arial",10));
    clickBtnEdit->show();

    connect(clickBtnEdit,&QPushButton::clicked,this,&informationUser::clickManageInfo);
}

void informationUser::clickHistoryPay()
{
     qDeleteAll(alignContent->children());
    managerAccout->setStyleSheet("background-color:#c8d6e5;");
    allInformationUser->setStyleSheet("background-color:#c8d6e5;");
    purchaseHistory->setStyleSheet("background-color:#2e86de;");

    lsmh *w = new lsmh(QString::fromStdString(Username),alignContent);
    w->show();

}

informationUser::~informationUser()
{
    delete ui;
}
