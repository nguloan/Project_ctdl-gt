
#include <QApplication>
#include<QMessageBox>
#include<clickmenu.h>
#include"cartwidget.h"
#include"program.h"
#include"signin.h"
#include<QLineEdit>
#include"viewdetailproduct.h"
#include"paywidget.h"
#include"managerwg.h"
#include "qt_user.h"
#include"lsmh.h"
#include"managerwg.h"
#include<QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap("E:/Project/MyProject/photo/104300461_550297562313739_5865094408960004343_n.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    signin w;

 //  program  w("root",3);

    w.show();
    splash.finish(&w);

    return a.exec();
}
