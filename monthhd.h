#ifndef MONTHHD_H
#define MONTHHD_H
#include<QString>
#include <QFile>
#include <QTextStream>
class monthhd
{
public:
    struct node{
        QString monthyear;
        node* next,*prev;
    };
private:
    node* head,*tail;
public:
    monthhd();
    node* getnewnode(QString x){
        node* newnode= new node;
        newnode->monthyear=x;
        newnode->next=NULL;
        newnode->prev=NULL;
        return newnode;
    }
    node* gethead(){
        return head;
    }
    node* gettail(){
        return tail;
    }
    void addhead(QString x);
    int monthcount();

};
 void inittimelist(monthhd &list);
 void outittimelist(monthhd &list);
#endif // MONTHHD_H
