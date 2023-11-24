#include "database.hpp"
#include "interpreter.hpp"

int main()
{
    std::string key = std::string("secure_key");
    Database *database = new Database(key);
    Interpreter *interpreter = new Interpreter(database);

    if (database->Exists() == true) {
        database->Load();
    }
    database->Select("table_1");

    interpreter->Insert("2", "load");
    interpreter->Insert("3", "delete this");
    
    interpreter->Display();

    interpreter->Delete("3");

    interpreter->Display();

    interpreter->Save();

    return 0;
}
