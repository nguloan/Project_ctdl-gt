#pragma once

#include <string>
#include <fstream>

class category
{
	struct node
	{
        std::string name;
        int id;
		node* next, * prev;
	};

private:
	node* head, * tail;
public:
	category() { head = tail = NULL; }
    ~category()
    {
        while (head!=NULL) {
             node* p = head;
             head=head->next;
             delete (p);
        }
    }
    node* getNewNode(std::string name,int id)
	{
        node* newNode = new node();
        for(std::string::iterator it = name.begin(); it !=  name.end(); ++it) {
            if(*it==' ' ){
                ++it;
                *it = std::toupper(*it);
            }
            else  if( it == name.begin())    *it = std::toupper(*it);
        }
		newNode->name = name;
        newNode->id = id;
		newNode->next = NULL;
		newNode->prev = NULL;
		return newNode;
	}
    bool checkName(std::string t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->name == t) return true;
            p=p->next;
        }
        return false;
    }
	node* getHead() { return head; }
	node* getTail() { return tail; }
    void add(std::string name,int id = 0)
    {
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
          if(p->id == 0)  tail->id = tail->prev == NULL ? 1 : tail->prev->id + 1;
        }
    }

    std::string getCodeCate(std::string t);
    int getCode(std::string t)
    {
        node* p = head;
        while (p != NULL)
        {
            if (p->name == t) return p->id;
            p = p->next;
        }
        return 0;
    }
    std::string getCate(std::string t);
    std::string getCate(int t);
    node* getPoiter(int t)
    {
        node* p = head;
        while (p != NULL)
        {
            if (p->id == t) return p;
            p = p->next;
        }
        return NULL;
    }
    void remove(node* p)
    {
        if (p == head)
        {
            head = head->next;
            p=NULL;
            return ;
        }
        if (p->prev != NULL)
        {
            p->prev->next = p->next;
        }
        if (p->next != NULL)
        {
            p->next->prev = p->prev;
        }
        p=NULL;
    }

    int getRows()
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

void init(category& list);
void save(category& list);
