#pragma once
#include <string>
#include <fstream>

struct usr
{
    std::string name, username, password, phonenumber, email;
    int gender, rights, enable;
    usr* left;
    usr* right;
};

class USERS
{
    usr* uhead;
    usr* utail;
public:
    USERS();
    ~USERS();
    void insert(usr* u);
    void sort();

    usr* gethead();
    usr* gettail();
    usr* getpointer(std::string id);
    int getRows();
    int checksignin(std::string id, std::string mk);
    int checkID(std::string id);
    std::string convertPass(std::string mk);
    int checkPass(std::string mk);
    int checkConfPass(std::string mk, std::string conf);
    int checkNum(std::string sdt);
    int checkMail(std::string mail);
};

usr* newone(std::string ten, std::string id, std::string mk, int gt, std::string sdt, std::string mail, int quyen, int stt);

std::string getname(usr* u);

void Init(USERS &dataUser);

void save(USERS u);
