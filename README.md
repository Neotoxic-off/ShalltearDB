# ShalltearDB
🩸 No SQL database made for C++

Simple database management system implemented in C++. It includes classes for managing tables (**Table**), a database (**Database**), and an interpreter (**Interpreter**) that provides a command interface for interacting with the database.

- The entire database is stored in Hex and Binary
- No pre-encoding required
- No restriction

## Commands
```CPP
Exists()
Load()
Save()

SelectByName("table name")
SelectByID("table id")

Display()

Insert("key", "value")
Delete("key")
Update("key", "new value")
Retrieve("key")
```

## Example
```CPP
#include "shalltearDB.hpp"

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
    for (size_t i = 0; i < 10; i++) {
        shalltearDB->interpreter->Insert(std::to_string(i), std::to_string(i));
    }
    shalltearDB->database->SelectByName("table_2");
    for (size_t i = 10; i < 20; i++) {
        shalltearDB->interpreter->Insert(std::to_string(i), std::to_string(i));
    }
    shalltearDB->interpreter->Display();
    shalltearDB->interpreter->Save();

    return (0);
}

```