#ifndef INFORMATIONUSER_H
#define INFORMATIONUSER_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QFormLayout>
#include<QLineEdit>
#include"vs_user.h"
#include<QRadioButton>
#include<lsmh.h>
#include<QDialog>
#include<QMessageBox>

namespace Ui {
class informationUser;
}

class informationUser : public QWidget
{
    Q_OBJECT

public:
    explicit informationUser(std::string username,QWidget *parent = nullptr);
    ~informationUser();
    std::string Username ;
    USERS DATAuser;
private:
    Ui::informationUser *ui;
    QWidget* alignContent;
     QPushButton *allInformationUser,*managerAccout, *purchaseHistory;
     QRadioButton* nam,*nu;
     QLineEdit  *name,      *numberPhone,    *email;

public slots:
  void clickAllInfo();
  void clickManageInfo();
  void clickHistoryPay();
  void clickEditPassword();
  void clickSave();
};

#endif // INFORMATIONUSER_H
