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
