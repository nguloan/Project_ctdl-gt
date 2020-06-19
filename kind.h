#pragma once

#include <string>
#include <fstream>

class kind
{
    struct node
    {
        std::string name;
        int idKind,idCate;
        node* next, * prev;
    };

private:
    node* head, * tail;
public:
    kind() { head = tail = NULL; }
    ~kind()
    {
        while (head!=NULL) {
             node* p = head;
             head=head->next;
             delete (p);
        }
    }
    node* getNewNode(std::string name,int idCate,int id)
    {
        node* newNode = new node();
        for(std::string::iterator it = name.begin(); it !=  name.end(); ++it) {
            if(*it==' ' ){
                ++it;
                *it = std::toupper(*it);
            }
            else
                if( it == name.begin())
                {
                     *it = std::toupper(*it);
                }

        }
        newNode->name = name;
        newNode->idCate= idCate;
        newNode->idKind=id;
        newNode->next = NULL;
        newNode->prev = NULL;
        return newNode;
    }
    bool checkName(std::string t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->name ==t) return true;
            p=p->next;
        }
        return false;
    }

    node* getHead() { return head; }
    node* getTail() { return tail; }
    void add(std::string name,int idCate,int id=0)
    {
        node* p = getNewNode(name,idCate,id);
        if (head == NULL)
        {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            p->prev = tail;
            tail = p;
            if(p->idKind==0)   tail->idKind = tail->prev == NULL ? 1 : tail->prev->idKind + 1;
        }
    }
    node* getPoiter(int  t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->idKind ==  t) return p;
            p=p->next;
        }
        return NULL;
    }


    void remove(node* p)
    {
        if (p == head)
        {
            head = head->next; return ;
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

    std::string getKind(std::string t);

    int getCode(std::string t)
    {
        node* p = head;
        while (p != NULL)
        {
            if (p->name == t) return p->idKind;
            p = p->next;
        }
        return 0;
    }

    bool checkCate(int t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->idCate == t) return true;
            p=p->next;
        }
        return false;
    }

};

void init(kind& list);
void save(kind& list);
