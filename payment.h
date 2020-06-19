#ifndef PAYMENT_H
#define PAYMENT_H
#include<QFile>
#include<QTextStream>
#include<QString>
class payment
{
public:
    struct node{
        QString payment;
        node* next,*prev;
    };
private:
    node* head,*tail;
public:
    payment();
    node* getnewnode(QString x){
        node* newnode= new node;
        newnode->payment=x;
        newnode->next=NULL;
        newnode->prev=NULL;
        return newnode;
    }
    node* gethead(){
        return head;
    }
    void addhead(QString x);
    friend void initpmlist(payment &list);
    friend void outitpmlist(payment &list);

};


#endif // PAYMENT_H
