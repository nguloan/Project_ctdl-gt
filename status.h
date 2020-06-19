#ifndef STATUS_H
#define STATUS_H

#include<QFile>
#include<QTextStream>
#include<QString>
class status
{
public:
    struct node{
        QString status;
        node* next,*prev;
    };
private:
    node* head,*tail;
public:
    status();
    ~status(){
        while(head){
            node* p=head;
            head=head->next;
            delete (p);
        }
    }
    node* getnewnode(QString x){
        node* newnode= new node;
        newnode->status=x;
        newnode->next=NULL;
        newnode->prev=NULL;
        return newnode;
    }
    int countlist();
    node* gethead(){
        return head;
    }
    node* gettail(){
        return tail;
    }
    void addhead(QString x);
    void deletemid(QString x){
        auto p=head;
        while(p->status!=x){
           p=p->next;
        }
        p->prev->next=p->next;
        p->next->prev=p->prev;
        delete p;
        return;
    }
    void deletehead(){
        auto p= head;
        head= p->next;
        head->prev= NULL;
        delete p;
        return;
    }
    void deletetail(){
        auto p=tail;
        tail=p->prev;
        tail->next=NULL;
        delete p;
        return;
    }
    void deletestt(QString x){
        if(head->status==x){
            deletehead();
        }else if(tail->status==x){
            deletetail();
        }else deletemid(x);
        return;
    }
};
 void initsttlist(status &list);
 void outitsttlist(status &list);

#endif // STATUS_H
