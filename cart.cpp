#include "cart.h"

cart::cart()
{
    head = tail = NULL;
}

cart::~cart()
{
    while (head) {
        node* p = head;
        head = head->next;
        delete (p);
    }
}

void save(cart& list,std::string username,bool check)
{
    std::ofstream file("E:\\Project\\MyProject\\cart\\"+username+".txt");
    if(check)
    {
        file.close();
        return;
    }
    auto p =list.getHead();
    while( p!= NULL)
    {
        file<<p->codePd<<std::endl<<p->quanity<<std::endl<<p->select<<std::endl;
        p=p->next;
    }
    file.close();
}

void init(cart& list, std::string username)
{

    std::ifstream file("E:\\Project\\MyProject\\cart\\"+username+".txt");


    while(!file.eof())
    {
        std::string masp; long soluong; int select;
        file>>masp>>soluong>>select;
        if(masp=="") return;
        list.add(masp,soluong,select);
    }
    file.close();
}


