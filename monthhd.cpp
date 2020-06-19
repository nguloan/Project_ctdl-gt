#include "monthhd.h"
#include <QString>
#include <QFile>
monthhd::monthhd()
{
    head=tail=NULL;
}
void monthhd::addhead(QString x){
    node* newnode=monthhd::getnewnode(x);
    if(head==NULL){
        head=newnode;
        tail=newnode;
        return;
    }
    newnode->next=head;
    head->prev=newnode;
    head=newnode;
    return;
}
int monthhd::monthcount(){
    int count=0;
    for(auto p=gethead();p!=NULL;p=p->next){
        count++;
    }
    return count;
}

void inittimelist(monthhd &list){
    QFile file("E:/Project/MyProject/time.txt");
    if(!file.open((QIODevice::ReadOnly))){
        qWarning("Cannot open file time.txt for reading");
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
        while(!in.atEnd()){
            QString status;
            status=in.readLine();
            list.addhead(status);
        }
        file.close();
}


void outittimelist(monthhd &list){
    QFile file("E:/Project/MyProject/time.txt");
    QTextStream out(&file);
    out.setCodec("UTF-8");
    if(file.open(QIODevice::WriteOnly)){
        for(auto p=list.gethead();p!=NULL;p=p->next){
            out<< p->monthyear << Qt::endl;
        }
    }else{
        qWarning("Could not open time list.txt");
    }
    file.close();
}
