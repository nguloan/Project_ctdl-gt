#pragma once
#include<string>
#include<fstream>
#include<iostream>



class brand
{
    struct node
    {
        std::string  name;
        int id;
        node* next, * prev;
    };

private:
    node* head, * tail;
public:
    node* getNewNode(std::string name,int id)
    {
        node* newNode = new node();
        for  (int i = 0;  i < name.length(); ++i)
        {
            if (name[i] >= 'a' && name[i] <= 'z')
            {
                name[i] -= 32;
            }
        }
        newNode->name = name;
        newNode->id = id;
        newNode->next = NULL;
        newNode->prev = NULL; return newNode;
    }

    brand(){ head = tail = NULL; }
   ~brand()
    {
        while (head!=NULL) {
             node* p = head;
             head=head->next;
             delete (p);
        }

    }


    void add(std::string name,int id = 0) {
        node* p = getNewNode(name,id);
        if (head == NULL)
        {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            p->prev = tail;
            tail = p;
            if(p->id == 0)    tail->id = tail->prev == NULL ? 1 : tail->prev->id + 1;
        }
    }
    node* getHead()	{	return head;}
    node* getTail() { return tail; }

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

    std::string getCodeBrand(std::string t)
    {
        node* p = head;
        while (p != NULL)
        {
            if (p->name == t) return p->id < 10 ? ("0" + std::to_string(p->id)) : std::to_string(p->id);
            p = p->next;
        }
        return "";
    }
    node* getPoiter(std::string t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->name==t) return p;
            p=p->next;
        }
        return NULL;
    }
    std::string getBrand(std::string t)
    {
        node* p = head;
        while (p != NULL)
        {
            if (p->id == std::stoi(t)) return p->name;
            p = p->next;
        }

        return  "";
    }
    bool check(std::string t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->name==t) return true;
            p=p->next;
        }
        return false;
    }
    int getRows()
    {
        node* p = head;
        int dem =0;
        while (p!=NULL) {
           dem++;
            p=p->next;
        }
        return dem;
    }
};

void save(brand &list);

void init(brand& t);

