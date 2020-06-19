#ifndef CLICKMENU_H
#define CLICKMENU_H

#include <QWidget>
#include<QMessageBox>
#include"kind.h"
#include<QPushButton>

namespace Ui {
class clickMenu;
}

class clickMenu : public QWidget
{
    Q_OBJECT

public:
    explicit clickMenu(std::string textCate,QWidget *parent = nullptr);
    ~clickMenu();
    QList<QString> listKind;

private:
    Ui::clickMenu *ui;
private slots:

};

#endif // CLICKMENU_H
