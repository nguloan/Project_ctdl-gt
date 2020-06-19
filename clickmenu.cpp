#include "clickmenu.h"
#include "ui_clickmenu.h"



clickMenu::clickMenu(std::string textCate,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clickMenu)
{
    kind dataKind;
    init(dataKind);
    this->resize(1920,1000);
    ui->setupUi(this);
    for (auto p = dataKind.getHead();p!=NULL;p=p->next) {
       if(p->idCate == 0 ) {
            listKind.append(QString::fromStdString(p->name));
       }
    }

    int dem = 1,row =1;
    for (int i=0;i<listKind.size();i++) {
        dem += 2;
        if(dem >= 17) { // 1920 - 200 = 1720 ; 1720 / 200 = 8 ; 17 - (dem * 2) , dem += 2
            dem = 1;
            row+=5;
        }
        QPushButton* btnCategory = new QPushButton(listKind[i],this);
        btnCategory->setGeometry(QRect(100*dem,50*row,190,190));
    }
}



clickMenu::~clickMenu()
{
    delete ui;
}
