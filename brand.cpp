#include"brand.h"


void save( brand &list)
{
    std::ofstream f("E:\\Project\\MyProject\\dataBrand.txt");
    auto p = list.getHead();
    while (p != NULL)
    {
        f << p->name << std::endl << p->id << std::endl;
        p = p->next;
    }
    f.close();
}

void init(brand& t)
{
    std::ifstream f("E:\\Project\\MyProject\\dataBrand.txt");
    while (!f.eof())
    {
        std::string a;
        std::getline(f, a);
        int id;
        f>>id;
        f.ignore(1);
        if (a == "") return;
        t.add(a,id);
    }
    f.close();
}


