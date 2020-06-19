#include "managerPd.h"
#include "ui_managerPd.h"
#include"categorydialog.h"

managerPd::managerPd(QWidget *parent) :    QWidget(parent),   ui(new Ui::managerPd)
{
    init(DATA);
    ui->setupUi(this);
    ui->table->setGeometry(0,50,1470,700);
    printTable();
    ui->brand->setGeometry(QRect(1480,100,150,30));
    ui->madein->setGeometry(QRect(1480,140,150,30));
    ui->category->setGeometry(QRect(1480,180,150,30));
    ui->addPd->setGeometry(QRect(1480,60,150,30));
    ui->iconFind->setStyleSheet("background-color:none;");

    connect(ui->brand,&QPushButton::clicked,this,&managerPd::clickBrand);
    connect(ui->madein,&QPushButton::clicked,this,&managerPd::clickMadein);
    connect(ui->category,&QPushButton::clicked,this,&managerPd::clickCategory);
    connect(ui->table,&QTableWidget::cellDoubleClicked,this, &managerPd::cellSelected);
    ListItem = {};
}

void managerPd::printTable()
{
    ui->table->clear();
    ui->table->setRowCount(DATA.length());
    ui->table->setColumnCount(9);
    ui->table->setColumnWidth(0,100);
    QTableWidgetItem* col0 = new QTableWidgetItem("Hình ảnh"),
            *col1 = new QTableWidgetItem("Mã sản phẩm"),
            *col2 = new QTableWidgetItem("Tên sản phẩm"),
            *col3 = new QTableWidgetItem("Danh mục"),
            *col4 = new QTableWidgetItem("Phân loại"),
            *col5 = new QTableWidgetItem("Thương hiệu / Xuất xứ"),
            *col6 = new QTableWidgetItem("Sản xuất"),
            *col7 = new QTableWidgetItem("Đơn giá"),
            *col8 = new QTableWidgetItem("Số lượng tồn kho"),
            *col9 = new QTableWidgetItem("Kinh doanh");

    ui->table->setHorizontalHeaderItem(0,col0);
    ui->table->setHorizontalHeaderItem(1,col1);
    ui->table->setHorizontalHeaderItem(2,col2);
    ui->table->setHorizontalHeaderItem(3,col3);
    ui->table->setHorizontalHeaderItem(4,col4);
    ui->table->setHorizontalHeaderItem(5,col5);
    ui->table->setHorizontalHeaderItem(6,col6);
    ui->table->setHorizontalHeaderItem(7,col7);
    ui->table->setHorizontalHeaderItem(8,col8);
    ui->table->setHorizontalHeaderItem(9,col9);
    int row = 0;
    ui->table->setColumnWidth(2,315);
    ui->table->setColumnWidth(4,150);
    ui->table->setColumnWidth(5,200);
    for (auto p = DATA.getHead();p!=NULL;p=p->next)
    {

        QString  photoFile = QString::fromStdString("E:\\Project\\MyProject\\photoProducts\\"+p->id+".png");
      if(!QFile::exists(photoFile)) photoFile = "E:\\Project\\MyProject\\photo\\imageNotFound.png";
                QTableWidgetItem *item0 = new QTableWidgetItem(QIcon(photoFile),QString()),
                                *item1 = new QTableWidgetItem(QString::fromStdString(p->id)),
                                *item2 = new QTableWidgetItem(QString::fromStdString(p->name)),
                                *item3 = new QTableWidgetItem(QString::fromStdString(p->category)),
                                *item4 = new QTableWidgetItem(QString::fromStdString(p->kind)),
                                *item5 = new QTableWidgetItem(QString::fromStdString(p->brand)),
                                *item6 = new QTableWidgetItem(QString::fromStdString(p->madein)),
                                *item7 = new QTableWidgetItem(QLocale(QLocale::English).toString(std::stoi(p->price))+" VND"),
                                *item8 = new QTableWidgetItem(QString::number(p->quanity)),
                                *item9 = new QTableWidgetItem(QString(p->disable?"không":"tiếp tục"));



                if(p->disable)
                {
                    item1->setBackgroundColor("#DD1444");
                    item2->setBackgroundColor("#DD1444");
                    item3->setBackgroundColor("#DD1444");
                    item4->setBackgroundColor("#DD1444");
                    item5->setBackgroundColor("#DD1444");
                    item6->setBackgroundColor("#DD1444");
                    item7->setBackgroundColor("#DD1444");
                    item8->setBackgroundColor("#DD1444");
                    item9->setBackgroundColor("#DD1444");
                }
                else if(p->quanity==0)
                {
                     item1->setBackgroundColor("#14DDDD");
                     item2->setBackgroundColor("#14DDDD");
                     item3->setBackgroundColor("#14DDDD");
                     item4->setBackgroundColor("#14DDDD");
                     item5->setBackgroundColor("#14DDDD");
                     item6->setBackgroundColor("#14DDDD");
                     item7->setBackgroundColor("blblueue");
                     item8->setBackgroundColor("#14DDDD");
                     item9->setBackgroundColor("#14DDDD");
                }
          //      ui->table->setRowHeight(row,80);

                        ui->table->setItem(row,0,item0);
                        ui->table->setItem(row,1,item1);
                        ui->table->setItem(row,2,item2);
                        ui->table->setItem(row,3,item3);
                        ui->table->setItem(row,4,item4);
                        ui->table->setItem(row,6,item6);
                        ui->table->setItem(row,7,item7);
                        ui->table->setItem(row,8,item8);
                        ui->table->setItem(row,5,item5);
                        ui->table->setItem(row,9,item9);     row++;
    }
}

managerPd::~managerPd()
{
    delete ui;
}

void managerPd::refesh()
{
    ListItem.clear();
    DATA.~Products();
    init(DATA);
    printTable();
}

void managerPd::clickBrand()
{

    brandDialog* newDialog = new brandDialog(NULL);
    if(newDialog->exec()  == brandDialog::Accepted)
    {
         refesh();
    }
}

void managerPd::clickMadein()
{

    madeinDialog* newDialog = new madeinDialog(NULL);
    if(newDialog->exec()  ==brandDialog::Accepted)
    {
        refesh();
    }
}


void managerPd::clickCategory()
{
    categoryDialog* newDialog = new categoryDialog(NULL);

    int ret = newDialog->exec();

    if(ret == categoryDialog::Accepted)
    {
        refesh();
    }

}

void managerPd::on_addPd_clicked()
{
        addPd* newDialog = new addPd(NULL);
        int ret = newDialog->exec();
        if(ret ==addPd::Accepted) {
            refesh();
        }
}

void managerPd::cellSelected(int nRow,int nCol)
{
    std::string str = ui->table->item(nRow,1)->text().toStdString();

    EditProduct* newDialog = new EditProduct(str,NULL);

    if(newDialog->exec() == EditProduct::Accepted) refesh();
}

void managerPd::on_find_textChanged(const QString &arg1)
{
    printTable();
    ListItem= {};
    if (arg1 == "") return;
     ListItem = ui->table->findItems(arg1, Qt::MatchEndsWith);

    foreach(QTableWidgetItem* rowptr,ListItem)
    {
        rowptr->setBackgroundColor(QColor("yellow"));
    }
}
