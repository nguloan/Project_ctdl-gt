#pragma once

#include <string>
#include <fstream>
#include"brand.h"
#include"madein.h"
#include"category.h"
#include"kind.h"


struct node
{
    std::string id, price,brand,madein,category,kind, name; int quanity,disable=1;
    node* next, * prev;
};
class Products
{

private:
    node* head, * tail;

public:

    brand listBrand;
    madein listMadein;
    category listCate;
    kind listKind;

	Products()
	{
        head = tail = NULL;
	}
	~Products()
	{
        while (head)
		{
            node* p = head;
            head = head->next;
            delete (p);
		}
        listCate.~category();
        listKind.~kind();
        listBrand.~brand();
        listMadein.~madein();
    }

    bool checkBrand(std::string t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(p->brand == t) return true;
            p=p->next;
        }
               return false;
    }

    node* newNode(std::string ma, std::string ten, std::string gia,int soluong,int tontai)
	{
		node* p = new node();
        std::string::iterator it = ten.end();
        --it;
        if(*it == '\n')
            ten = ten.substr(0,ten.length()-1);

        p->next = NULL;
        p->prev = NULL;
		p->id = ma;
		p->name = ten;
		p->price = gia;
        p->category = listCate.getCate(p->id.substr(0,2));
        p->kind = listKind.getKind(p->id.substr(2,2));
        p->brand = listBrand.getBrand(p->id.substr(4,2));
        p->madein = listMadein.getMadein(p->id.substr(6,2));
        p->quanity = soluong;
        p->disable = tontai;
		return p;
	}
    void insert(std::string ma, std::string ten, std::string gia, int soluong,int tontai = 0)  // hàm này để chèn khóa p vào dslk đôi nhá
    {
        node* p = newNode(ma, ten, gia,soluong,tontai);
        if (head == NULL)
        {
            head = p;
            tail = p;
        }
        else
        {
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
    }
	std::string getCodeProduct() //hàm này để set mã phẩm mới
	{
		return this->length() < 10 ? ("0" + std::to_string(this->length())) : std::to_string(this->length());
	}
    std::string getNameProduct(std::string t) // hàm này trả về tên sản phẩm thông qua mã sản phẩm
	{
        node* p = head;
		while (p != NULL)
		{
			if (p->id == t) return p->name;
            p = p->next;
		}
        return "";
	}
	node* getHead()
	{
        return head;
	}
	int length(); // tính xem có bao nhiêu khóa 
	node* getTail()
	{
        return tail;
	}
	node* getPoiter(std::string t) // trả về địa chỉ thông qua mã sản phẩm
	{
        node* p = head;
		while (p != NULL)
		{
			if (p->id == t) return p;
            p = p->next;
		}
		return NULL;
	}
	void remove(node* p); // hàm xóa  khóa p
	long long getPrice(std::string t)  // hàm này để lấy giá tiền sản phẩm thông qua mã sản phẩm
	{
        node* p = head;
		while (p != NULL)
		{
			if (p->id == t) return std::stoi(p->price);
            p = p->next;
		}
		return 0;
	}  
    bool checkMadein(int t)
    {
        node* p = head;
        while(p!=NULL)
        {
            if(std::stoi(p->id.substr(6,2)) == t) return true;
            p=p->next;
        }
        return false;
    }

    bool checkKind(int t)
    {
        node* p = head;
        while(p != NULL)
        {
            if(std::stoi(p->id.substr(2,2)) == t) return true;
            p=p->next;
        }
        return false;
    }


};

void init(Products& list);
void save(Products list);
