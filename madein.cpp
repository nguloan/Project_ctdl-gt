#include"madein.h"


void init(madein& list)
{
    std::ifstream f("E:\\Project\\MyProject\\dataMadein.txt",std::ios::in);
    while (!f.eof())
    {
        std::string a;
        std::getline(f, a);
        if (a == "") return;
        int b;
        f>>b;
        f.ignore(1);
        list.add(a,b);
    }
    f.close();
}

void save(madein &list)
{
    std::ofstream f("E:\\Project\\MyProject\\dataMadein.txt",std::ios::trunc|std::ios::out);
    auto p = list.getHead();
    while (p != NULL)
    {
        f << p->name << std::endl<<p->id<<std::endl;
        p = p->next;
    }
    f.close();
}
