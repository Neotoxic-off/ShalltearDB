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
#include "database.hpp"
#include "interpreter.hpp"

int main()
{
    std::string key = std::string("secure_key");
    Database *database = new Database(key);
    Interpreter *interpreter = new Interpreter(database);

    if (database->Exists() == true) {
        database->Load();
        database->SelectByName("table_1");
        interpreter->Display();
        database->SelectByName("table_2");
        interpreter->Display();
    }
    database->Create("tbl_1", "table_1");
    database->Create("tbl_2", "table_2");

    database->SelectByName("table_1");

    for (size_t i = 0; i < 10; i++) {
        interpreter->Insert(std::to_string(i), std::to_string(i));
    }

    database->SelectByName("table_2");

    for (size_t i = 10; i < 20; i++) {
        interpreter->Insert(std::to_string(i), std::to_string(i));
    }

    interpreter->Display();

    interpreter->Save();

    return (0);
}
```