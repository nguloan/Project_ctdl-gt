#include"kind.h"

std::string kind::getKind(std::string t)
{
    node* p = head;
    while (p != NULL)
    {
        if (p->idKind == std::stoi(t)) return p->name;
        p = p->next;
    }

    return  "";
}

void init(kind& list)
{
    std::ifstream f;
    f.open("E:\\project\\MyProject\\dataKind.txt");
    while (!f.eof())
    {
        std::string a;
        std::getline(f, a);
        if(a=="") return;
        int b,c; // id cate va id kind
        f>>b;
        f>>c;
        f.ignore(1);
        list.add(a,b,c);
    }
    f.close();
}

void save(kind& list)
{
    std::ofstream f;
    f.open("E:\\project\\MyProject\\dataKind.txt");
    auto p = list.getHead();
    while (p!=NULL)
    {
        f << p->name << std::endl<<p->idCate<<std::endl<<p->idKind<<std::endl;
        p = p->next;
    }
    f.close();

}
