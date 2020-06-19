#ifndef CART_H
#define CART_H

#include<string>
#include<fstream>

class cart
{
    struct node{
        std::string codePd; long quanity; int select;
        node* next,*prev;
    };

private:
    node* head,*tail;
public:
    cart();
    ~cart();
    node* getNewNode(std::string masp,long soluong,int select)
    {
        node* p = new node();
       p->codePd  = masp;
       p->quanity = soluong;
       p->select = select;
       p->next = NULL;
       p->prev = NULL;
       return p;
    }
    node* getNodeByCodepd(std::string masp)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->codePd==masp) return p;
            p=p->next;
        }
        return NULL;
    }

    void add(std::string masp,long soluong,int select = 1)
    {
        node* p = getNodeByCodepd(masp); // kiem tra ma san pham da ton tai trong csdl ko
        {
            if(p != NULL)
            {
                p->quanity += soluong;
                return;
            }
        }

        node* newNode = getNewNode(masp,soluong,select);
        if(head==NULL)
        {
            head = newNode;
            tail = newNode ;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void remove(node* p)
    {
        if (p == head)
        {
            head = head->next; return;
        }
        if (p->prev != NULL)
        {
            p->prev->next = p->next;
        }
        if (p->next != NULL)
        {
            p->next->prev = p->prev;
        }
        delete(p);
    }
    node* getHead()
    {
        return head;
    }
    node* getPoiter(std::string t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->codePd==t) return p;
            p=p->next;
        }
        return NULL;
    }

    int length()
    {
        node* p = head;
        int dem =0;
        while(p!=NULL)
        {
            dem++;
            p=p->next;
        }
        return dem;
    }
};

void save(cart& list,std::string username,bool check = false);
void init(cart &list,std::string username);



#endif // CART_H
