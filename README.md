# ShalltearDB
🩸 No SQL database made for C++

Simple database management system implemented in C++. It includes classes for managing tables (**Table**), a database (**Database**), and an interpreter (**Interpreter**) that provides a command interface for interacting with the database.

- The entire database is stored in Hex and Binary
- No pre-encoding required
- No restriction

## Commands
```CPP
Insert(std::string, std::string);
Display();
Save();
Load();
Delete(std::string);
Create(std::string, std::string);
Update(std::string, std::string);

FindById(std::string);
FindAll(std::string);
FindFirst(std::string);
FindAllStartWith(std::string);

SelectByID(std::string);
SelectByName(std::string);
```

## Example
```CPP
#include "shalltearDB.hpp"

void test_findfirst(ShalltearDB *shalltearDB)
{
    std::string find = shalltearDB->interpreter->FindFirst("9");

    std::cout << find << std::endl;
}

void test_findall(ShalltearDB *shalltearDB)
{
    std::map<std::string, std::string> all = shalltearDB->interpreter->FindAll("9");

    for (auto &it: all) {
        std::cout << it.first << ":" << it.second << std::endl;
    }
}

int main(int argc, char **argv)
{
    ShalltearDB *shalltearDB = new ShalltearDB("key");

    if (shalltearDB->database->Exists() == true) {
        shalltearDB->database->Load();
        shalltearDB->database->SelectByName("table_1");
        shalltearDB->interpreter->Display();
        shalltearDB->database->SelectByName("table_2");
        shalltearDB->interpreter->Display();
    }
    shalltearDB->interpreter->Create("tbl_1", "table_1");
    shalltearDB->interpreter->Create("tbl_2", "table_2");
    shalltearDB->interpreter->SelectByID("tbl_1");
    shalltearDB->interpreter->Insert("100", "9");
    for (size_t i = 0; i < 10; i++) {
        shalltearDB->interpreter->Insert(std::to_string(i), std::to_string(i));
    }
    shalltearDB->database->SelectByName("table_2");
    for (size_t i = 10; i < 20; i++) {
        shalltearDB->interpreter->Insert(std::to_string(i), std::to_string(i));
    }
    shalltearDB->interpreter->Display();

    std::map<std::string, std::string> t = shalltearDB->interpreter->FindAllStartWith("1");
    for (auto &i : t) {
        std::cout << i.first << ": " << i.second << std::endl;
    }

    shalltearDB->interpreter->Save();
    int size = shalltearDB->interpreter->Count();

   test_findfirst(shalltearDB);
   test_findall(shalltearDB);

    return (0);
}

```
