#include"category.h"

std::string category::getCodeCate(std::string t)
{
	node* p = head;
	while (p != NULL)
	{
		if (p->name == t) return p->id < 10 ? ("0" + std::to_string(p->id)) : std::to_string(p->id);
		p = p->next;
	}
	return "";
}

std::string category::getCate(std::string t)
{
	node* p = head;
	while (p != NULL)
	{
		if (p->id == std::stoi(t)) return p->name;
		p = p->next;
	}

    return  "";
}

std::string category::getCate(int t)
{
    node* p = head;
    while (p != NULL)
    {
        if (p->id == t) return p->name;
        p = p->next;
    }

    return  "";
}

void init(category& list)
{

    std::ifstream f;
    f.open("E:\\project\\MyProject\\dataCate.txt");

	while (!f.eof())
	{
        std::string a;
		std::getline(f, a);
        if(a=="") return;
        int id;
        f>>id;
        f.ignore(1);
        list.add(a,id);
	}
	f.close();
}

void save(category& list)
{

    std::ofstream f;
    f.open("E:\\project\\MyProject\\dataCate.txt");
    auto p = list.getHead();
    while (p!=NULL)
    {
        f << p->name << std::endl<<p->id<<std::endl;
        p = p->next;
    }
    f.close();

}
